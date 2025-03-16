#ifndef _MAIN_H
#define _MAIN_H

#include "system.h"
#include "io.h"
#include "oled.h"
#include "timer.h"
#include "adc.h"

//#include "SEGGER_SYSVIEW_ConfDefaults.h"
//#include "SEGGER_RTT.h"
//#include "SEGGER_RTT_Conf.h"

//makro tanimla task izlemek icin. task stateleri txt dosyasina gir. 
#define EXEC_TASK(p)    SEGGER_SYSVIEW_OnTaskStartExec((U32)p);   \
                        p();                                      \
                        SEGGER_SYSVIEW_OnTaskStopReady((U32)p, 0);
                        

#define SYS_CLOCK_FREQ CLOCK_FREQ  //100000000


void init(void);
void Task_Print(void);
void init_OLED(void);
void Task_LED(void);
void Task_Sensor(void);
void init_Timers(void);
void init_SeggerModules(void);
void SYSVIEW_AddTask(void* pTask, const char* sName, U32 Prio);
void init_ADC(void);


#endif /*_MAIN_H*/