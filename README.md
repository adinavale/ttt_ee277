**SNAKE GAME SETUP**

1. Connect Nexys A7 board to the PC using USB and Monitor using VGA cable
2. Open Vivado Project:
* Program and Debug -> Open Target -> Autoconnect
* Program and Debug -> Program Target -> 'choose device' -> Load Bitstream file(Vivado/VivadoProject/reflash.bit) -> Program
3. Open TeraTerm
*  Setup -> Serial Port -> set Baud rate:19200 -> New setting
4. Follow instructions displayed in the text console of VGA Monitor to play the game

*************************************************************
		ENJOY THE GAME !!!
*************************************************************

**Software & Hardware Used**
1. Keil: Keil uVision 5 is used for C and assembly language i.e. for snake game application
development.
2. Tera term: Tera Term software is used to send (UP, DOWN, RIGHT, LEFT) commands via
UART to the SoC.
3. Vivado: Xilinx Vivado software is used for the hardware designing of the processor and
other peripherals.
4. Nexys A7: SoC board Nexys A7 

**Software Files used in the application**
1. _Core folder_
*  core_cm0.h: CMSIS Cortex-M0 Core Peripheral Access Layer Header File
*  core_cmFunc.h: CMSIS Cortex-M Core Function Access Header File
*  core_cmInstr.h: CMSIS Cortex-M Core Instruction Access Header File

2. _Device folder_
*  retarget.c: Retarget functions for ARM DS-5 Professional / Keil MDK, allows us to use print library functions
*  edk_api.h: Initialization of parameters and functions used for VGA, UART, rectangle etc. 
*  edk_api.c: Application Programming Interface (API) functions
*  edk_driver.h: Peripheral driver header file
*  edk_driver.c: Functions definition for VGA, timer, 7 segments, GPIO peripherals 
*  EDK_CM0.h: Used to specify Interrupt Number Definition
*  cm0dsasm.s: Assembly file

3. _Application folder_
*  main.c : Tasks performing game initialization settings, boundary hit condition, self hit condition, mutual hit condition, target generation, UART, Timer for double player
*  main_1player.c : Tasks performing game initialization settings, boundary hit condition, self hit condition, mutual hit condition, target generation, UART, Timer for single player
