#ifndef __BUTTON_H
#define __BUTTON_H

#define BTN_LONG_PRESS
#define BTN_LONG_PRESS_TIME 1000 //1000ms 

typedef struct {
    int IO_idx;         //input pin index
    int cState;         //current state of button
    int aState;         //active state of button (1 for active or 0 for active..)
    int dbc;            //debiunce counter (for spikes)
#ifdef BTN_LONG_PRESS
    int acc;            //active time counter for long press
#endif
}BTN_PIN;


enum{//must be same order with _bts arr.
  BTN_ONBOARD,
  BTN_SET,
  BTN_DOWN,
  BTN_UP,
};

void BTN_InitButtons(void);
void BTN_ScanButtons(void);

extern int g_Buttons[];
extern int g_ButtonsL[];



#endif  //__BUTTON_H