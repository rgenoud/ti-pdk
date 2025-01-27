IPC over SHM Benchmark Example

A benchmark example demonstrating how to use the IPC over Shared Memory (Circ) transport as well 
as its performance.

Steps to build the benchmark example:

1. Import the shmIpcBenchmark_c66xx CCS project from transport\ipc\examples\shmIpcBenchmark directory. (in CCSv5, 
   Project->Import Existing CCS/CCE Eclipse Projects)

2. Clean the shmIpcBenchmark_c66xx project, delete the Debug and Release directories, and re-build the project. 
   After the build is complete, shmIpcBenchmark_c66xx.out and shmIpcBenchmark_c66xx.map will be generated under 
   transport\ipc\examples\shmIpcBenchmark\Debug (or \Release depending on the build configuration) directory.

Steps to run shmIpcBenchmark_c66xx in CCSv5:

1. Be sure to set the boot mode dip switch to no boot/EMIF16 boot mode on the EVM.

2. Group Core 0 and Core 1 in CCS.

3. Connect to both cores via the group.

4. Load the evmc66xxl.gel to initialize the DDR.  The GEL can be found in the 
    "CCS install dir"\ccsv5\ccs_base_x.x.x.xxxxx\emulation\boards\evmc66xxl\gel directory.  Once loaded execute
   the default setup script on each core.  In the CCS menu go to Scripts->EVMC6657L Init Functions->Global_Default_Setup.

5. Highlighting the Group in the CCS Debug window, load 
    transport\ipc\examples\shmIpcBenchmark\Debug\shmIpcBenchmark_c66xx.out on each core

6. Highlighting the Group in CCS Debug window, run the program in CCS on both cores simultaneously, shmIpcBenchmark_c66xx          will send messageQ messages between the cores via the SHM circ transport.  The messages will be used to measure the       transport's performance.  The test will be complete after the throughput (msg/s) has been calculated.
