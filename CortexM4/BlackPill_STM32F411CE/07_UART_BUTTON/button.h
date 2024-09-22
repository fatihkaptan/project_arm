#ifndef __BUTTON_H
#define __BUTTON_H



typedef struct {
int IO_idx;     //input pin index
int cState;     //current state of button
int aState;     //active state of button (1 for active or 0 for active..)
int dbc;        //debiunce counter (for spikes)
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



#endif  //__BUTTON_H