#include "system.h"
#include "io.h"

volatile int g_bEOC; // End of conversion flag

/*Internal(layered) ADC Functions */
void IADC_IoInit(int idx)
{
    IO_Init(idx, IO_MODE_ANALOG);   
    
}

void IADC_Channel(int ch, int rank)
{
    ADC_RegularChannelConfig(ADC1, ch, rank, ADC_SampleTime_3Cycles/*sample time*/);

}

//nConv: total ch number, 
//cmode: TRUE/FALSE continious mode, 
//smode: TRUE/FALSE scanMode
void IADC_Init(int nConv, int cmode, int smode)
{
    //1)ADC Clock Setup
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);   
    
    //2) Init structures.
    
    ADC_InitTypeDef adcInit;
    ADC_CommonInitTypeDef adcCommonInit;
    //ADC_StructInit(&adcInit); //auto assign default parameters
    //ADC_CommonStructInit(&adcCommonInit);
    
    adcInit.ADC_ContinuousConvMode = cmode ? ENABLE : DISABLE;
    adcInit.ADC_DataAlign = ADC_DataAlign_Right;
    adcInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    adcInit.ADC_Resolution= ADC_Resolution_12b;
    adcInit.ADC_ScanConvMode = smode ? ENABLE : DISABLE;
    adcInit.ADC_NbrOfConversion = 1;
    adcInit.ADC_ExternalTrigConvEdge= ADC_ExternalTrigConvEdge_None;
    
    
    adcCommonInit.ADC_DMAAccessMode =ADC_DMAAccessMode_Disabled ;
    adcCommonInit.ADC_Mode= ADC_Mode_Independent;
    adcCommonInit.ADC_Prescaler = ADC_Prescaler_Div4;
    adcCommonInit.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;
    
    ADC_Init(ADC1, &adcInit);
    ADC_CommonInit(&adcCommonInit);
    
    //3) Start ADC Periph
    ADC_Cmd(ADC1,ENABLE);
    
    //4)Activate Vref and cputemp sensor.    
    ADC_TempSensorVrefintCmd(ENABLE); //AN16: cputemp, AN17: internal LDO voltage
       
}

//software triggered adc
void IADC_Start(void)
{
    ADC_SoftwareStartConv(ADC1);
}

int IADC_Result(void)
{
    SEGGER_SYSVIEW_MarkStart(0x05);
    return ADC_GetConversionValue(ADC1);
}

int ADC_Convert(int ch)
{
    SEGGER_SYSVIEW_MarkStart(0x04);
    //1) add ch to list 
    IADC_Channel(ch,1);
    //2) start conversion
    IADC_Start();
    //3)wait until end (primitive/preemtive way)
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);
    //4 return val
    SEGGER_SYSVIEW_MarkStop(0x04);
    //return ADC_GetConversionValue(ADC1);
}

//ADC End of conversion interrupt config.
void IADC_IntConfig(void)
{
    //1) periphs configs.
    ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
    ADC_ITConfig(ADC1, ADC_IT_EOC,ENABLE);
    //2) core nvic configs.
    NVIC_SetPriority(ADC_IRQn,2); //oncelik ayni ise digeri bitmesini bekler. sayi kuculdukce onem artar.  
    NVIC_EnableIRQ(ADC_IRQn);
}

///////INT - EOC
void ADC_IRQHandler(void)
{   
    if(ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET){
        g_bEOC = 1;
        
        ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
    }
}












