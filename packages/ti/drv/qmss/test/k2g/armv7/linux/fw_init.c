/**  
 *  (C) Copyright 2012-2013, Texas Instruments, Inc.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
#include <errno.h>
#include <string.h>

#include "fw_test.h"
#include "fw_mem_allocator.h"

#include <ti/drv/qmss/qmss_qm.h>
#include <ti/drv/qmss/device/k2e/src/qmss_device.c>
#include <ti/drv/cppi/device/k2e/src/cppi_device.c>

/* Socket Includes */
#include "sockutils.h"
#include "sockrmmsg.h"

/* RM Includes */
#include <ti/drv/rm/rm.h>
#include <ti/drv/rm/rm_transport.h>
#include <ti/drv/rm/rm_services.h>

/* Socket timeout */
#define CLIENT_SOCK_TIMEOUT_USEC     (500)

/* Application's registered RM transport indices */
#define SERVER_TO_CLIENT_MAP_ENTRY   0
/* Maximum number of registered RM transports */
#define MAX_MAPPING_ENTRIES          1

/* Error checking macro */
#define RM_ERROR_CHECK(checkVal, resultVal, rmInstName, printMsg)                 \
    if (resultVal != checkVal) {                                                  \
        char errorMsgToPrint[] = printMsg;                                        \
        printf("RM Inst : %s : ", rmInstName);                                    \
        printf("%s with error code : %d, exiting\n", errorMsgToPrint, resultVal); \
        return(-1);                                                               \
    }

/* RM registered transport mapping structure */
typedef struct trans_map_entry_s {
    /* Registered RM transport handle */
    Rm_TransportHandle        transportHandle;
    /* Remote socket tied to the transport handle */
    sock_name_t              *remote_sock;
} Transport_MapEntry;

/************************ GLOBAL VARIABLES ********************/
/* linking RAM */
uint64_t *linkingRAM0;

/* RM Client Vars */
Rm_Handle           rmClientHandle = NULL;
Rm_ServiceHandle   *rmClientServiceHandle = NULL;
sock_h              rmClientSocket;

/* Client instance name (must match with RM Global Resource List (GRL) and policies */
char                rmClientName[RM_NAME_MAX_CHARS] = "RM_Client0";

/* Client socket name */
char                rmClientSockName[] = "/tmp/var/run/rm/rm_client";

/* Transport map stores the RM transport handle to IPC MessageQ queue mapping */
Transport_MapEntry  rmTransportMap[MAX_MAPPING_ENTRIES];

/******************************************************************************
* Macro to convert to IP Register Virtual Address from a mapped base Virtual Address
* Input: virtBaseAddr: Virtual base address mapped using mmap for IP
*        phyBaseAddr: Physical base address for the IP
*        phyRegAddr:  Physical register address
******************************************************************************/
static inline void* FW_GET_REG_VADDR (void * virtBaseAddr, uint32_t phyBaseAddr, uint32_t phyRegAddr)
{
    return((void *)((uint8_t *)virtBaseAddr + (phyRegAddr - phyBaseAddr)));
}

Rm_Packet *transportAlloc(Rm_AppTransportHandle appTransport, uint32_t pktSize, Rm_PacketHandle *pktHandle)
{
    Rm_Packet *rm_pkt = NULL;

    rm_pkt = calloc(1, sizeof(*rm_pkt));
    if (!rm_pkt) {
        printf("can't malloc for RM send message (err: %s)\n", strerror(errno));
        return (NULL);
    }
    rm_pkt->pktLenBytes = pktSize;
    *pktHandle = rm_pkt;

    return(rm_pkt);
}

void transportFree (Rm_Packet *rm_pkt)
{
    if (rm_pkt) {
        free (rm_pkt);
    }         
}

void transportReceive (void)
{
    int32_t             rm_result;
    int                 retval;
    int                 length = 0;
    sock_name_t         server_sock_addr;
    Rm_Packet          *rm_pkt = NULL;
    struct sockaddr_un  server_addr;    
    
    retval = sock_wait(rmClientSocket, &length, NULL, -1);
    if (retval == -2) {
        /* Timeout */
        printf("Error socket timeout\n");
        return;
    }
    else if (retval < 0) {
        printf("Error in reading from socket, error %d\n", retval);
        return;
    }
    
    if (length < sizeof(*rm_pkt)) {
        printf("invalid RM message length %d\n", length);
        return;
    }
    rm_pkt = calloc(1, length);
    if (!rm_pkt) {
        printf("can't malloc for recv'd RM message (err: %s)\n",
               strerror(errno));
        return;
    }
    
    server_sock_addr.type = sock_addr_e;
    server_sock_addr.s.addr = &server_addr;
    retval = sock_recv(rmClientSocket, (char *)rm_pkt, length, &server_sock_addr);
    if (retval != length) {
        printf("recv RM pkt failed from socket, received = %d, expected = %d\n",
               retval, length);
        return;
    }
    
    //printf("received RM pkt of size %d bytes from %s\n", length, server_sock_addr.s.addr->sun_path);

    /* Provide packet to RM Client for processing */       
    if ((rm_result = Rm_receivePacket(rmTransportMap[SERVER_TO_CLIENT_MAP_ENTRY].transportHandle, rm_pkt))) {
        printf("RM failed to process received packet: %d\n", rm_result);
    }

    transportFree(rm_pkt);
}

int32_t transportSendRcv (Rm_AppTransportHandle appTransport, Rm_PacketHandle pktHandle)
{
    sock_name_t *server_sock_name = (sock_name_t *)appTransport;
    Rm_Packet   *rm_pkt = (Rm_Packet *)pktHandle;
    
    if (sock_send(rmClientSocket, (char *)rm_pkt, (int) rm_pkt->pktLenBytes, server_sock_name)) {
        printf("send data failed\n");
    }

    /* Wait for response from Server */
    transportReceive();
 
    return (0);
}

int connection_setup(void)
{
    Rm_TransportCfg rmTransCfg;
    int32_t         rm_result;
    int             i;
    sock_name_t     sock_name;
    char            server_sock_name[] = RM_SERVER_SOCKET_NAME;
    
    /* Initialize the transport map */
    for (i = 0; i < MAX_MAPPING_ENTRIES; i++) {
        rmTransportMap[i].transportHandle = NULL;
    }

    sock_name.type = sock_name_e;
    sock_name.s.name = rmClientSockName;

    rmClientSocket = sock_open(&sock_name);
    if (!rmClientSocket) {
        printf("connection_setup: Client socket open failed\n");
        return (-1);
    }

    rmTransportMap[SERVER_TO_CLIENT_MAP_ENTRY].remote_sock = calloc(1, sizeof(sock_name_t));
    rmTransportMap[SERVER_TO_CLIENT_MAP_ENTRY].remote_sock->type = sock_name_e;    
    rmTransportMap[SERVER_TO_CLIENT_MAP_ENTRY].remote_sock->s.name = calloc(1, strlen(server_sock_name)+1);
    strncpy(rmTransportMap[SERVER_TO_CLIENT_MAP_ENTRY].remote_sock->s.name, server_sock_name, strlen(server_sock_name)+1);

    /* Register the Server with the Client instance */
    rmTransCfg.rmHandle = rmClientHandle;
    rmTransCfg.appTransportHandle = (Rm_AppTransportHandle) rmTransportMap[SERVER_TO_CLIENT_MAP_ENTRY].remote_sock;
    rmTransCfg.remoteInstType = Rm_instType_SERVER;
    rmTransCfg.transportCallouts.rmAllocPkt = transportAlloc;
    rmTransCfg.transportCallouts.rmSendPkt = transportSendRcv;
    rmTransportMap[SERVER_TO_CLIENT_MAP_ENTRY].transportHandle = Rm_transportRegister(&rmTransCfg, &rm_result);  

    return(0);
}

/** ============================================================================
 *   @n@b initRm
 *
 *   @b Description
 *   @n This API initializes the RM Client for the QMSS test establishing
 *      a socket connection with the RM Server
 * 
 *   @return    int32_t
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
int initRm (void)
{
    Rm_InitCfg         rmInitCfg;
    int32_t            result;
    
    /* Initialize the RM Client - RM must be initialized before anything else in the system */
    memset(&rmInitCfg, 0, sizeof(rmInitCfg));
    rmInitCfg.instName = rmClientName;
    rmInitCfg.instType = Rm_instType_CLIENT;
    rmClientHandle = Rm_init(&rmInitCfg, &result);
    RM_ERROR_CHECK(RM_OK, result, rmClientName, "Initialization failed");

    printf("\n\nInitialized %s\n\n", rmClientName);

    /* Open Client service handle */
    rmClientServiceHandle = Rm_serviceOpenHandle(rmClientHandle, &result);
    RM_ERROR_CHECK(RM_OK, result, rmClientName, "Service handle open failed");

    return(connection_setup());
}

/** ============================================================================
 *   @n@b initQmss
 *
 *   @b Description
 *   @n This API initializes the QMSS LLD on core 0 only.
 *
 *   @param[in]  
 *   @n linkRamSz: linking RAM size
 *   @n internal: indicates if internal linking RAM has to be used 
 * 
 *   @return    int32_t
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
int initQmss (uint32_t linkRamSz, bool internal)
{
    int32_t                     result;
    Qmss_InitCfg                qmssInitConfig;
    Qmss_GlobalConfigParams     fw_qmssGblCfgParams;
    uint32_t                    count;

    /* Initialize QMSS */
    memset (&qmssInitConfig, 0, sizeof (Qmss_InitCfg));

    /* Set up QMSS configuration */

    /* Use internal linking RAM */
    if (internal) {
        qmssInitConfig.linkingRAM0Base  = 0;   
        qmssInitConfig.linkingRAM0Size  = 0;
        qmssInitConfig.linkingRAM1Base  = 0;
        qmssInitConfig.maxDescNum       = linkRamSz;
    } else {
        /* Memory allocation for linking RAM */
        linkingRAM0 = (uint64_t *)fw_memAlloc((linkRamSz*sizeof(uint64_t)), CACHE_LINESZ);
        if (linkingRAM0 == NULL) {
		    printf ("initQmss: Failed to allocate memory for linkingRAM, exiting\n");
		    return (-1);
        }

        memset ((void *) linkingRAM0, 0, (linkRamSz*sizeof(uint64_t)));
        qmssInitConfig.linkingRAM0Base = (uint32_t)linkingRAM0;
        qmssInitConfig.linkingRAM0Size = linkRamSz;
        qmssInitConfig.linkingRAM1Base = 0;
        qmssInitConfig.maxDescNum      = linkRamSz;
    }

    /* Bypass hardware initialization as it is done within Kernel */
    qmssInitConfig.qmssHwStatus     =   QMSS_HW_INIT_COMPLETE;

    fw_qmssGblCfgParams = qmssGblCfgParams;

    /* Convert address to Virtual address */ 
    for(count=0;count < fw_qmssGblCfgParams.maxQueMgrGroups;count++)
    {

        fw_qmssGblCfgParams.groupRegs[count].qmConfigReg = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.groupRegs[count].qmConfigReg);

        fw_qmssGblCfgParams.groupRegs[count].qmDescReg = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.groupRegs[count].qmDescReg);

        fw_qmssGblCfgParams.groupRegs[count].qmQueMgmtReg = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.groupRegs[count].qmQueMgmtReg);
        
        fw_qmssGblCfgParams.groupRegs[count].qmQueMgmtProxyReg = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.groupRegs[count].qmQueMgmtProxyReg);
        
        fw_qmssGblCfgParams.groupRegs[count].qmQueStatReg = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.groupRegs[count].qmQueStatReg);

        fw_qmssGblCfgParams.groupRegs[count].qmStatusRAM = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.groupRegs[count].qmStatusRAM);

        fw_qmssGblCfgParams.groupRegs[count].qmQueMgmtDataReg = 
            FW_GET_REG_VADDR(fw_qmssDataVaddr,QMSS_DATA_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.groupRegs[count].qmQueMgmtDataReg);
        
        fw_qmssGblCfgParams.groupRegs[count].qmQueMgmtProxyDataReg = NULL; /* not supported on k2 hardware, and not used by lld */
    }
    
    for(count=0;count < QMSS_MAX_INTD;count++)
    {
        fw_qmssGblCfgParams.regs.qmQueIntdReg[count] = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.regs.qmQueIntdReg[count]);
    }

    for(count=0;count < QMSS_MAX_PDSP;count++)
    {
        fw_qmssGblCfgParams.regs.qmPdspCmdReg[count] = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.regs.qmPdspCmdReg[count]);

        fw_qmssGblCfgParams.regs.qmPdspCtrlReg[count] = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.regs.qmPdspCtrlReg[count]);

        fw_qmssGblCfgParams.regs.qmPdspIRamReg[count] = 
            FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.regs.qmPdspIRamReg[count]);
    }

    fw_qmssGblCfgParams.regs.qmLinkingRAMReg = 
        FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.regs.qmLinkingRAMReg);

    fw_qmssGblCfgParams.regs.qmBaseAddr = 
        FW_GET_REG_VADDR(fw_qmssCfgVaddr,QMSS_CFG_BASE_ADDR,(uint32_t)fw_qmssGblCfgParams.regs.qmBaseAddr);

    if (rmClientServiceHandle) {
        fw_qmssGblCfgParams.qmRmServiceHandle = rmClientServiceHandle;
    }

    /* Initialize the Queue Manager */
    result = Qmss_init (&qmssInitConfig, &fw_qmssGblCfgParams);
    if (result != QMSS_SOK)
    {
        printf ("initQmss: Error initializing Queue Manager SubSystem, Error code : %d\n", result);
        return -1;
    }

    /* Start Queue manager on this core */
    result = Qmss_start ();
    if (result != QMSS_SOK)
    {
        printf ("initQmss: Error starting Queue Manager SubSystem, Error code : %d\n", result);
        return -1;
    }

    /* Queue Manager Initialization Done */
    return 0;
}

