/*
 * Copyright (C) 2021 Texas Instruments Incorporated - https://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *	* Redistributions of source code must retain the above copyright
 *	  notice, this list of conditions and the following disclaimer.
 *
 *	* Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in the
 *	  documentation and/or other materials provided with the
 *	  distribution.
 *
 *	* Neither the name of Texas Instruments Incorporated nor the names of
 *	  its contributors may be used to endorse or promote products derived
 *	  from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* PRU side interrupt mapping description for v5.10+ Linux kernels  */

#ifndef _PRU_INTC_MAP_H_
#define _PRU_INTC_MAP_H_

#include <stdint.h>
#include <stddef.h>
#include <pru_types.h>

#ifdef PRU0
struct sysevt_host_map pru_intc_map_new[] = { {42, 0, 0},
};
#endif
#ifdef PRU1
struct sysevt_host_map pru_intc_map_new[] = { {54, 1, 1},
};
#endif

/**
 * struct pru_irq_rsc - PRU side IRQ resource info
 *
 * @type: should be 0
 * @num_evts: number of entries in pru_intc_map
 */
struct pru_irq_rsc {
        uint8_t type;
        uint8_t num_evts;
} __packed;

#pragma DATA_SECTION(pru_intc_map_new, ".pru_irq_map.map")
#pragma DATA_SECTION(rsc_map, ".pru_irq_map")
#pragma RETAIN(rsc_map)
#pragma RETAIN(pru_intc_map_new)
struct pru_irq_rsc rsc_map  = {
	0,
       (sizeof(pru_intc_map_new) / sizeof(struct sysevt_host_map)),
       /* pru_intc_map_new is placed just after rsc_map by the linker */
};

#endif /* _PRU_INTC_MAP_H_ */
