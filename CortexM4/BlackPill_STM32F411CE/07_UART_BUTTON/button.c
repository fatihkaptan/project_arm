#include "button.h"
#include "system.h"
#include "io.h"


int g_dbMax = 50;       //debounce max val. for succesfull state change(50ms)
int _bScan = 0;         //button scanning start flag

static BTN_PIN _bts[] = { /*BTN_PIN struct*/
  {IOP_BTN_ONBOARD,1,0,0}, /*internal pull-uup with zero debounce*/
  {IOP_BTN_SET,1,0,0},
  {IOP_BTN_DOWN,1,0,0},
  {IOP_BTN_UP,1,0,0},  
};

#define N_BUTTONS (sizeof(_bts)/sizeof(BTN_PIN))
int g_Buttons[N_BUTTONS] = { 0 };       //semaphore arr(counting, for all buttons)
int g_ButtonsL[N_BUTTONS]= { 0 };      //semaphore arr(binary, for long press)

//every button timer calls with systick,
//perform single button scans
static void BTN_Scan(int btIdx){
    int r; //pin read value

    r = IO_Read(_bts[btIdx].IO_idx);

    if(r != _bts[btIdx].cState){
        if (++_bts[btIdx].dbc >= g_dbMax){
            //successfull counter reached, change state, reset debounce counter. 
            _bts[btIdx].cState = r;
            _bts[btIdx].dbc=0;
            
            if(_bts[btIdx].cState == _bts[btIdx].aState){
                //Signal!!!
                //g_Buttons[btIdx] = 1;   //binary semaphore_old
                ++g_Buttons[btIdx];      //counting semaphore
#ifdef BTN_LONG_PRESS
                _bts[btIdx].acc = 0;    //reset active timer
#endif
            }
        }
    }
    else{
        //state changed until reach debounce max value, reset value, may be parasite.
        _bts[btIdx].dbc=0;
    }
    
#ifdef BTN_LONG_PRESS
    if (g_ButtonsL[btIdx]==0){
      if (_bts[btIdx].cState == _bts[btIdx].aState){
        if(++_bts[btIdx].acc >= BTN_LONG_PRESS_TIME){
          _bts[btIdx].acc = 0;
          g_ButtonsL[btIdx] = 1; //binary semaphore for long press
        }
      }
    }
#endif
    
}


void BTN_InitButtons(void){
    int i;
    
    for(i=0; i < N_BUTTONS; i++){
    IO_Init(_bts[i].IO_idx,IO_MODE_INPUT_PU);
    }
    
    _bScan= 1;
}


void BTN_ScanButtons(void){
    if (!_bScan)
        return;
    
    int i;
    
    for (i=0;i<N_BUTTONS;i++){
        BTN_Scan(i);
    }
        
}




