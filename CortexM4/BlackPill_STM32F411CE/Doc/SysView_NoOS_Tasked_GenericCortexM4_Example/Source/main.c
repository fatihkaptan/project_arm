/*********************************************************************
*               (c) SEGGER Microcontroller GmbH & Co. KG             *
*                        The Embedded Experts                        *
*                           www.segger.com                           *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Shows simple SystemView implementation for NoOS applications as tasks.
*/

#include "SEGGER_SYSVIEW_Conf.h"
#include "SEGGER_SYSVIEW.h"

/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/

#define SYSTICK ((SYSTICK_REGS*)0xE000E010)
#define SCS     ((SCS_REGS*)0xE000ED00)

#define EXEC_TASK(p)  SEGGER_SYSVIEW_OnTaskStartExec((U32)p);         \
                      p();                                            \
                      SEGGER_SYSVIEW_OnTaskStopReady((U32)p, 0);

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct {
  volatile unsigned int CSR;
  volatile unsigned int RVR;
  volatile unsigned int CVR;
  volatile unsigned int CALIB;
} SYSTICK_REGS;

typedef struct {
  volatile unsigned int CPUID;       // CPUID Base Register
  volatile unsigned int ICSR;        // Interrupt Control and State Register
  volatile unsigned int VTOR;        // Vector Table Offset Register
  volatile unsigned int AIRCR;       // Application Interrupt and Reset Control Register
  volatile unsigned int SCR;         // System Control Register
  volatile unsigned int CCR;         // Configuration and Control Register
  volatile unsigned int SHPR1;       // System Handler Priority Register 1
  volatile unsigned int SHPR2;       // System Handler Priority Register 2
  volatile unsigned int SHPR3;       // System Handler Priority Register 3
  volatile unsigned int SHCSR;       // System Handler Control and State Register
  volatile unsigned int CFSR;        // Configurable Fault Status Register
  volatile unsigned int HFSR;        // HardFault Status Register
  volatile unsigned int DFSR;        // Debug Fault Status Register
  volatile unsigned int MMFAR;       // MemManage Fault Address Register
  volatile unsigned int BFAR;        // BusFault Address Register
  volatile unsigned int AFSR;        // Auxiliary Fault Status Register
  volatile unsigned int aDummy0[4];  // 0x40-0x4C Reserved
  volatile unsigned int aDummy1[4];  // 0x50-0x5C Reserved
  volatile unsigned int aDummy2[4];  // 0x60-0x6C Reserved
  volatile unsigned int aDummy3[4];  // 0x70-0x7C Reserved
  volatile unsigned int aDummy4[2];  // 0x80-0x87 - - - Reserved.
  volatile unsigned int CPACR;       // Coprocessor Access Control Register
} SCS_REGS;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

volatile unsigned int _TestFunc0Cnt;
volatile unsigned int _TestFunc1Cnt;
//
//  ToDo: Edit this value to the current CPU clock value of
//  your system to receive 1 ms Systick interrupts
//
U32 SystemCoreClock = 16000000;

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/********************************************************************* 
*
*       _TestFunc1()
*
*  Function description
*    Simple dummy function.
*/
static void _TestFunc1(void) {
  _TestFunc1Cnt = 100;
  do {
    _TestFunc1Cnt--;
  } while (_TestFunc1Cnt);
}

typedef enum {
  STATE_INIT = 0,
  STATE_WAIT_FOR_DATA,
  STATE_PROCESS_DATA,
  STATE_SEND_DATA
} TASK_STATE_0;


/********************************************************************* 
*
*       _TestFunc0()
*
*  Function description
*    Simple dummy function with a state machine
*/
static void _TestFunc0(void) {
  static TASK_STATE_0 _State = STATE_INIT;

  switch (_State) {
  case STATE_INIT:
    SEGGER_SYSVIEW_RecordVoid(50 + STATE_INIT);
    _TestFunc0Cnt = 100;
    while(50 < --_TestFunc0Cnt);
    while(--_TestFunc0Cnt);
    _State = STATE_WAIT_FOR_DATA;
    SEGGER_SYSVIEW_RecordEndCall(50 + STATE_INIT);
    break;
  case STATE_WAIT_FOR_DATA:
    SEGGER_SYSVIEW_RecordVoid(50 + STATE_WAIT_FOR_DATA);
    _TestFunc0Cnt = 100;
    while(50 < --_TestFunc0Cnt);
    while(--_TestFunc0Cnt);
    _State = STATE_PROCESS_DATA;
    SEGGER_SYSVIEW_RecordEndCall(50 + STATE_WAIT_FOR_DATA);
    break;
  case STATE_PROCESS_DATA:
    SEGGER_SYSVIEW_RecordVoid(50 + STATE_PROCESS_DATA);
    _TestFunc0Cnt = 100;
    while(50 < --_TestFunc0Cnt);
    while(--_TestFunc0Cnt);
    _State = STATE_SEND_DATA;
    SEGGER_SYSVIEW_RecordEndCall(50 + STATE_PROCESS_DATA);
    break;
  case STATE_SEND_DATA:
    SEGGER_SYSVIEW_RecordVoid(50 + STATE_SEND_DATA);
    _TestFunc0Cnt = 100;
    while(50 < --_TestFunc0Cnt);
    while(--_TestFunc0Cnt);
    _State = STATE_WAIT_FOR_DATA;
    SEGGER_SYSVIEW_RecordEndCall(50 + STATE_SEND_DATA);
    break;
  }
}


/********************************************************************* 
*
*       SysTick_Handler()
*
*  Function description
*    Handles Systick
*/
void SysTick_Handler(void) {
  volatile U32 Cnt;
  SEGGER_SYSVIEW_RecordEnterISR();
  Cnt++;
  SEGGER_SYSVIEW_RecordExitISR();
}

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/
void SYSVIEW_AddTask(void* pTask, const char* sName, U32 Prio);


/********************************************************************* 
*
*       main()
*/
int main(void) {
  U32 v;
  int Cnt;

  Cnt = 0;
  SEGGER_SYSVIEW_Conf();            /* Configure and initialize SystemView  */
  SYSVIEW_AddTask(_TestFunc0, "TestFunc0", 10);
  SYSVIEW_AddTask(_TestFunc1, "TestFunc1", 10);
  //
  // Configure SysTick and debug monitor interrupt priorities
  // Low value means high priority
  // A maximum of 8 priority bits and a minimum of 3 bits is implemented per interrupt.
  // How many bits are implemented depends on the actual CPU being used
  // If less than 8 bits are supported, the lower bits of the priority byte are RAZ.
  // In order to make sure that priority of monitor and SysTick always differ, please make sure that the difference is visible in the highest 3 bits
  v = SCS->SHPR3;
  v |= (0xFFuL << 24);   // Lowest prio for SysTick so SystemView does not get interrupted by Systick
  SCS->SHPR3 = v;
  //
  // Configure SysTick interrupt
  // SysTick is running at CPU speed
  // Configure SysTick to fire every ms
  //
  SYSTICK->RVR = (SystemCoreClock / 1000) - 1;     // set reload
  SYSTICK->CVR = 0x00;      // set counter
  SYSTICK->CSR = 0x07;      // enable systick
  //
  // Main "super loop" of the system.
  // Calls every "task" function in an endless loop.
  // Each task function maintains its own state machine, and has to return on its own.
  //
  while (1) {
    Cnt = 100;
    EXEC_TASK(_TestFunc0);
    EXEC_TASK(_TestFunc1);
    while(--Cnt);  // Delay
  }                // Wait for SysTick interrupts to fire
  return 0;
}

/****** End Of File *************************************************/
