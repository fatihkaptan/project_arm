#ifndef _MAIN_H
#define _MAIN_H

#include "system.h"
#include "io.h"
#include "timer.h"

#define SYS_CLOCK_FREQ CLOCK_FREQ  //100000000


void init(void);
void Task_Print(void);
void Task_LED(void);
void init_Timers(void);

#endif /*_MAIN_H*/