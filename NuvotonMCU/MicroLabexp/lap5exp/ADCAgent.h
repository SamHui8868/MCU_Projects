#ifndef __ADCAGENT_H__
#define __ADCAGENT_H__
#include "M451Series.h"

extern uint32_t timecount;

void ADC_Initial(void);
void ADC_Task(void);
uint8_t ADC_GetTemperature(void);
uint8_t ADC_GetVR(void);

#endif  /* __ADCAGENT_H__ */





