#include "M451Series.h"
#include "TimebaseAgent.h"
#include "SevenSegmentAgent.h"
#include "ButtonAgent.h"
#include "StepMotorAgent.h"

uint32_t timecount;

uint8_t dir;
uint8_t speed;
uint8_t oldspeed;
int flag;

int __main(){
	/* Initial timer0 */
	Timebase_Initial();
	
	/* Initial 7 segment I/O and variables*/
	_7Seg_Initial();
	
	/* Initial push button */
	Btn_Initial();
	
	/* Initial step motor I/O and variables*/
	StepMtr_Initial();
	
	//Initial LED1
	GPIO_SetMode(PB,BIT2,GPIO_MODE_OUTPUT);
	
	dir = 1;
	speed = 25;
	_7Seg_WriteBuf(2,5);
	flag=0;
	
	while(1){
			
		
		/* if the two buttons pressed "only" */
		if(Btn_IsDown(0xF) == 0x03)
			PB2 = 0;
		else
			PB2 = 1;
		if(flag==1 && Btn_IsOneShot(0x04) == 0x04)
		{
		speed=oldspeed;
			flag=0;
		//write to 7seg output buffer
			_7Seg_WriteBuf(1000/speed/10,1000/speed%10);
			Btn_OneShotClear(0x04);
		}
		/* if the button pressed */
		if(Btn_IsOneShot(0x01) == 0x01){
			speed++;
			//write to 7seg output buffer
			_7Seg_WriteBuf(1000/speed/10,1000/speed%10);
			//clear one-shot flag
			Btn_OneShotClear(0x01);
		}
		
		if(Btn_IsOneShot(0x02) == 0x02){
			if(speed)
				speed--;
			//write to 7seg output buffer
			_7Seg_WriteBuf(1000/speed/10,1000/speed%10);
			Btn_OneShotClear(0x02);
		}
		
				 if(Btn_IsOneShot(0x04) == 0x04){
				oldspeed=speed;
				speed=0;
				flag=1;
			//write to 7seg output buffer
			_7Seg_WriteBuf(1000/speed/10,1000/speed%10);
			Btn_OneShotClear(0x04);
		}

		 if(Btn_IsOneShot(0x08) == 0x08){
			if(dir==0)
			{
			  dir=1;
			}
				
		else if(dir==1)
		{
		  dir=0;
		}
				
			//write to 7seg output buffer
			_7Seg_WriteBuf(1000/speed/10,1000/speed%10);
			Btn_OneShotClear(0x08);
		}
		/* Step motor output */
		StepMtr_Task(dir, speed);
		
		/* Scan button */
		Btn_Task();
		
		/* 7 segment output */
		_7Seg_Task();
	}
}

