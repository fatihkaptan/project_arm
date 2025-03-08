#ifndef _MAIN_H
#define _MAIN_H

#include "system.h"
#include "io.h"
#include "oled.h"
#include "timer.h"

//#include "SEGGER_SYSVIEW_ConfDefaults.h"
//#include "SEGGER_RTT.h"
//#include "SEGGER_RTT_Conf.h"

#define SYS_CLOCK_FREQ CLOCK_FREQ  //100000000


void init(void);
void Task_Print(void);
void init_OLED(void);
void Task_LED(void);
void init_Timers(void);
void init_SeggerModules(void);
void SYSVIEW_AddTask(void* pTask, const char* sName, U32 Prio);

#endif /*_MAIN_H*/