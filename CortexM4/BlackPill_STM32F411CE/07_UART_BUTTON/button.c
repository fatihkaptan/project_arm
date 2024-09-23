#include "button.h"
#include "system.h"
#include "io.h"


int g_dbMax = 50;       //debounce max val. for succesfull state change(50ms)
int _bScan = 0;         //button scanning start flag

static BTN_PIN _bts[] = { /*BTN_PIN struct-> pin, init. state, idle state, init. debounce, edgetype */
  {IOP_BTN_ONBOARD,     LOW_PU,IDLE_HIGH, 0, RISING_EDGE}, /*internal pull-uup with zero debounce and rising edge*/
  {IOP_BTN_SET,         LOW_PU,IDLE_HIGH, 0, FALLING_EDGE},
  {IOP_BTN_DOWN,        LOW_PU,IDLE_HIGH, 0, RISING_EDGE},
  {IOP_BTN_UP,          LOW_PU,IDLE_HIGH, 0, RISING_EDGE},  
};


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
            
            if(((_bts[btIdx].edgeType == FALLING_EDGE) &&(_bts[btIdx].cState != _bts[btIdx].aState)) ||
               ((_bts[btIdx].edgeType == RISING_EDGE) &&(_bts[btIdx].cState == _bts[btIdx].aState))){
                //Signal!!!
                //g_Buttons[btIdx] = 1;   //binary semaphore_old
                ++g_Buttons[btIdx];      //counting semaphore

            }
            else{                
#ifdef BTN_LONG_PRESS
                _bts[btIdx].lState = 0;    //reset active timer
                _bts[btIdx].acc = 0;
#endif             
            }
        }
    }
    else{
        //state changed until reach debounce max value, reset value, may be parasite.
        _bts[btIdx].dbc=0;
    }
    
#ifdef BTN_LONG_PRESS
    if (_bts[btIdx].lState==0){
      if (_bts[btIdx].cState == _bts[btIdx].aState){
        if(++_bts[btIdx].acc >= BTN_LONG_PRESS_TIME){
          _bts[btIdx].acc = 0;
          _bts[btIdx].lState = 1;
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




