#include "M451Series.h"
#include "TimebaseAgent.h"
#include "SevenSegmentAgent.h"
#include "ButtonAgent.h"
#include "StepMotorAgent.h"
#include "ADCAgent.h"

uint32_t timecount;

uint8_t dir;
uint32_t speed;
uint8_t mtr_speed;
int DisplayMode;
uint32_t StepMtr_RPMtoD(uint8_t rpm);
void DisplayTask (void);
int __main(){
	/* Initial timer0 */
	Timebase_Initial();
	
	/* Initial 7 segment I/O and variables*/
	_7Seg_Initial();
	
	/* Initial push button */
	Btn_Initial();
	
	/* Initial step motor I/O and variables*/
	StepMtr_Initial();
	
	/* Initial ADC I/O and variables*/
	ADC_Initial();
	
	//Initial LED1
	GPIO_SetMode(PB,BIT2,GPIO_MODE_OUTPUT);
	
	dir = 1;
	speed = 0;

	while(1){
			
		
		/* if the two buttons pressed "only" */
		if(Btn_IsDown(0xF) == 0x03)
			PB2 = 0;
		else
			PB2 = 1;

		/* if the button pressed */
		if(Btn_IsOneShot(0x01) == 0x01){
			DisplayMode=1;//1=display temp
			//clear one-shot flag
			Btn_OneShotClear(0x01);
		}
		
		if(Btn_IsOneShot(0x02) == 0x02){
			DisplayMode=2;//2=display speed
			Btn_OneShotClear(0x02);
		}
		
		 if(Btn_IsOneShot(0x04) == 0x04){
			DisplayMode=3;//3=display dir
			 dir=!dir;
				Btn_OneShotClear(0x04);
			//Btn_OneShotClear(0x04);
		}
		 
		
		/* Convert Analog to Digital */
		ADC_Task();
		
		mtr_speed=ADC_GetVR();
	  speed=StepMtr_RPMtoD(mtr_speed);
		
		/* Write to 7_seg buffer */
		DisplayTask();
		
		/* Step motor output */
		StepMtr_Task(dir,speed);
		
		/* Scan button */
		Btn_Task();
		
		/* 7 segment output */
		_7Seg_Task();
	}
}

void DisplayTask (void){
static uint32_t Dpoldcount=0;
	if((uint32_t)timecount-Dpoldcount<1000)return;
	Dpoldcount=timecount;
	switch(DisplayMode)
		{case 1:
	    _7Seg_WriteBuf((ADC_GetTemperature()/10)%10, ADC_GetTemperature()%10);
			break;
		 case 2:
		 _7Seg_WriteBuf((mtr_speed/10)%10,mtr_speed%10);
			break;
		 case 3:
		 _7Seg_WriteBuf(dir/10,dir);
		 break;
		 default:
		_7Seg_WriteBuf((ADC_GetTemperature()/10)%10, ADC_GetTemperature()%10);
		}
			
	}

uint32_t StepMtr_RPMtoD(uint8_t rpm)
	{
		return rpm?6000/rpm:0;
	}









