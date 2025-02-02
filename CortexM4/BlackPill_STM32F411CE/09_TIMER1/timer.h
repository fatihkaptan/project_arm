#ifndef _TIMER_H
#define _TIMER_H

#define TIMER_DEBUG 1

enum {
TIMER_1,
TIMER_2,
TIMER_3,
TIMER_4,
TIMER_5,
};


extern volatile unsigned long g_T1Count;
extern volatile unsigned long g_T2Count;
extern volatile unsigned long g_T3Count;
extern volatile unsigned long g_T4Count;
extern volatile unsigned long g_T5Count;
void Timer_Init(int tmNo, unsigned prescale, unsigned period, unsigned repeat);
void Timer_Start(int tmNo, int bStart);
void Timer_Reset(int tmNo);
void TimerIntConfig(int tmNo, int priority);

#endif