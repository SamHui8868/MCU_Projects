#include "ADCAgent.h"

uint8_t ADCState;
uint16_t TempBuf;
uint16_t VRBuf;

void ADC_Initial(void){
	CLK->APBCLK0 |= CLK_APBCLK0_EADCCKEN_Msk;			//adc clock enable
	
	CLK->CLKDIV0 &= ~CLK_CLKDIV0_EADCDIV_Msk;			//adc clock divide
	CLK->CLKDIV0 |= 0 << CLK_CLKDIV0_EADCDIV_Pos; //(div + 1)
	
	EADC->CTL |= EADC_CTL_ADCEN_Msk; 							//adc enable
	
	EADC->CTL &= ~EADC_CTL_DIFFEN_Msk;						//0 = Single-end analog input mode
	
	EADC->CTL &= ~EADC_CTL_SMPTSEL_Msk;
	EADC->CTL |= EADC_CTL_SMPTSEL8;								//adc sample time = 4
	
	EADC->SCTL[0] &= ~EADC_SCTL_TRGSEL_Msk; 
  EADC->SCTL[0] |= EADC_SOFTWARE_TRIGGER;				//set trigger source
	
	EADC->SCTL[0] &= ~EADC_SCTL_CHSEL_Msk;
	EADC->SCTL[0] |= 6 << EADC_SCTL_CHSEL_Pos;		//set sample module 0 to channel 6 
	
	SYS->GPB_MFPH &= ~SYS_GPB_MFPH_PB9MFP_Msk;		//set channel 6 pin(PB9) as analog input
  SYS->GPB_MFPH |= SYS_GPB_MFPH_PB9MFP_EADC_CH6;
	
	PB->DINOFF |= BIT9;														//disable digital input path
	
	SYS->IVSCTL |= SYS_IVSCTL_VTEMPEN_Msk;				//enable temperature sensor
	
	ADCState = 0;																	//inititial adc agent state
}


void ADC_Task(void){
	static uint32_t ADCOldCount = 0;
	
	if((uint32_t)(timecount - ADCOldCount) < 10)
		return;
	ADCOldCount = timecount;
	
	switch(ADCState){
		case 0:/* Software trigger VR(sample module 0) and temperature channel(sample module 17) */
			
			EADC->SWTRG |= (BIT0 | BIT17);
			ADCState = 1;
			break;
		
		case 1:/* wait for all conversion done */
			
			if(EADC->SWTRG == 0){
				ADCState = 2;
			}
			break;
			
		case 2:/* Get data */
			
			VRBuf = (EADC->DAT[0] & 0xFFF);
			TempBuf = (EADC->DAT[17] & 0xFFF);
			
			ADCState = 0;
			break;
			
		default:
			ADCState = 0;
	}
	
}


uint8_t ADC_GetTemperature(void){
	/* Vtemp(mV) = Gain(mV/C) * Temperature(C) + Offset(mV) 
	** Gain = 1.672(mV/C)
	** Offset = 740 (mV) 
	** Vref+ = Vcc = 3.3V
	** Vref- = 0V
	** Resolution = 2^12 = 4096LSB
	************************************************************************
	** Vtemp(mV) = (3300(mV) - 0(mV))*(Dtemp(LSB) / 4096(LSB))
	** Temperature(C)	= (Vtemp(mV) - Offset(mV)) /  Gain(mV/C)
	**								= (( (3300 - 0) * (Dtemp / 4096)) - 740) / - 1.672
	**								= ((3300 * Dtemp / 4096) - 740) / -1.672	
	**								= (740 - (3300 * Dtemp / 4096)) / 1.672	
	**								= (740000 - (3300000 * Dtemp / 4096)) / 1.672
	*/
	return (740000 - (TempBuf * (3300000 >> 12))) / 1672;
}

uint8_t ADC_GetVR(void){
	return VRBuf >> 4;
}




