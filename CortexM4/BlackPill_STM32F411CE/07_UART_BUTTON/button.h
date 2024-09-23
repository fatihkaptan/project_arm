#ifndef __BUTTON_H
#define __BUTTON_H

#define BTN_LONG_PRESS//
#define BTN_LONG_PRESS_TIME 1000 //1000ms 




enum BUTTONS{//must be same order with _bts arr.
  BTN_ONBOARD,
  BTN_SET,
  BTN_DOWN,
  BTN_UP,
  BTN_COUNT,
};

#define N_BUTTONS BTN_COUNT

void BTN_InitButtons(void);
void BTN_ScanButtons(void);

extern int g_Buttons[];
extern int g_ButtonsL[];

typedef enum{
  RISING_EDGE,
  FALLING_EDGE,
}eTypeEdge;

typedef enum{
  IDLE_HIGH,
  IDLE_LOW,
}eTypeIdle;

typedef enum{
  HIGH_PU,
  LOW_PU,
}eTypePUState;

typedef struct {
    int IO_idx;         //input pin index
    eTypePUState cState;         //current state of button
    eTypeIdle aState;         //active state of button (1 for active or 0 for active..)
    int dbc;            //debounce counter (for spikes)
    eTypeEdge edgeType;       //rising(0) / falling(1) edge setting for buttons
#ifdef BTN_LONG_PRESS
    int acc;            //active time counter for long press
    eTypePUState lState;         //long press state
#endif
}BTN_PIN;



#endif  //__BUTTON_H