#ifndef _ADC_H
#define _ADC_H


extern volatile int g_bEOC; // End of conversion flag
void IADC_IoInit(int idx);
void IADC_Channel(int ch, int rank);
void IADC_Init(int nConv, int cmode, int smode);
void IADC_Start(void);
int ADC_Convert(int ch);

//marker convert fonksiyon olcumleri 
    /* 12bit res. & ADC_TwoSamplingDelay_5Cycles ayarlarda marker olcumu;
    //sample time
    //3Cycles  : -> 4.1us sonuc verdi. 
    //15Cycles : -> 4.5us sonuc verdi. 
    //144Cycles: -> 9.6us sonuc verdi.
    //480Cycles: -> 23 us sonuc verdi. 
    //
    //12bit res. & ADC_SampleTime_3Cycles ayarlarda marker olcumu;
    //TwoSamplingDelay
    //5Cycles -->  4.1us sonuc verdi. 
    //20Cycles: -> 3.8 - 4.1us arasi sonuc verdi.
    //  
    //ADC_SampleTime_3Cycles & ADC_TwoSamplingDelay_5Cycles ayarlarda marker olcumu;
    //12bit res: -> 4.1us sonuc verdi. 
    //10bit res: -> 3.8us sonuc verdi. cok nadir 4.0 us oldu. 
    //8bit res: -> 3.8us sonuc verdi.
    //6bit res: -> 3.6 us sonuc verdi. 
    */

#endif /* _ADC_H*/