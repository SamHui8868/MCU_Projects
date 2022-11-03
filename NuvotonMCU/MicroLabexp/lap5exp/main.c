#include <stdio.h>

#include "M451Series.h"
#include "TimebaseAgent.h"
#include "SevenSegmentAgent.h"
#include "ButtonAgent.h"
#include "StepMotorAgent.h"
#include "ADCAgent.h"

#define TASK_CLKSHOW		0
#define TASK_CLKSET			1
#define TASK_MTRSHOW		2
#define TASK_MTRSET			3
#define TASK_MTRADC			4

#define STATE_CLKSHOW_SEC		0
#define STATE_CLKSHOW_MIN		1
#define STATE_CLKSHOW_HRS		2
	
#define STATE_CLKSET_ON			0
#define STATE_CLKSET_OFF		1

#define STATE_MTRSHOW_SPEED	0
#define STATE_MTRSHOW_DIR		1
#define STATE_MTRSHOW_TEMP	2

#define STATE_MTRSET_ON			0
#define STATE_MTRSET_OFF		1

#define STATE_MTRADC_SPEED	0
#define STATE_MTRADC_DIR		1
#define STATE_MTRADC_TEMP		2

uint32_t timecount;

uint8_t Task_ID;
uint8_t mtr_set;

uint8_t Task_ClkShow_State;
uint8_t Task_ClkSet_State;
uint8_t Task_MtrShow_State;
uint8_t Task_MtrSet_State;
uint8_t Task_MtrADC_State;

uint8_t _7seg_lo;
uint8_t _7seg_hi;

uint8_t mtr_speed; //rpm
uint8_t mtr_dir;
uint32_t mtr_d;
uint8_t stop;

int8_t clk_sec;
int8_t clk_min;
int8_t clk_hr;


void DisplayTask(uint8_t hi, uint8_t lo);
void ClkShow(void);
void ClkSet(void);
void MtrShow(void);
void MtrSet(void);
void MtrADC(void);
void CLOCK(void);
uint32_t StepMtr_RPMtoD(uint8_t rmp);

int __main(){

	Timebase_Initial();
	_7Seg_Initial();
	Btn_Initial();
	StepMtr_Initial();
	ADC_Initial();
	
	clk_sec = 0;
	clk_min = 0;
	clk_hr = 0;
	
	_7seg_hi = 0;
	_7seg_lo = 0;
	
	mtr_dir = 1;
	mtr_speed = 25;
	stop = 0;
	mtr_d = StepMtr_RPMtoD(mtr_speed);
	
	Task_ID = TASK_CLKSHOW;
	Task_ClkShow_State = STATE_CLKSHOW_SEC;
	Task_ClkSet_State = STATE_CLKSET_ON;
	Task_MtrShow_State = STATE_MTRSHOW_SPEED;
	Task_MtrSet_State = STATE_MTRSET_ON;
	Task_MtrADC_State = STATE_MTRADC_SPEED;
	
	while(1){
		
		switch(Task_ID)
		{
			case TASK_CLKSHOW:
				ClkShow();
			break;
			case TASK_CLKSET:
				ClkSet();
			break;
			case TASK_MTRSHOW:
				MtrShow();
         CLOCK();
			break;
			case TASK_MTRSET:
				MtrSet();
			  CLOCK();

			break;
			case TASK_MTRADC:
				MtrADC();
			  CLOCK();
			break;
			default:
				Task_ID = TASK_CLKSHOW;
		}
		
		DisplayTask(_7seg_hi, _7seg_lo);	//10Hz update rate
		_7Seg_Task();											//1kKz switch rate
		ADC_Task();												//ADC conversion
		StepMtr_Task(mtr_dir, mtr_d);			//Step motor output
		Btn_Task();												//Button scan
	}
}

void DisplayTask(uint8_t hi, uint8_t lo){
	static uint32_t DpOldCount = 0;
	if((uint32_t)(timecount - DpOldCount) < 1000)//100ms
		return;
	DpOldCount = timecount;
	
	_7Seg_WriteBuf(hi, lo);
}
void CLOCK(void)
{
	static uint32_t ClkOldCount = 0;
	/* Clock tick */
	if((uint32_t)(timecount - ClkOldCount) >= 10000)
	{
		if(++clk_sec >= 60){
			clk_sec = 0;
			if(++clk_min >= 60){
				clk_min = 0;
				if(++clk_hr >= 24)
					clk_hr = 0;
			}
		}
		ClkOldCount = timecount;
	}


}



void ClkShow(void){

	
	CLOCK();
	
	/* Button control */
	if(Btn_IsDown(0x01) == 0x01)
	{
		if(Btn_IsOneShot(0x02) == 0x02)
		{
			Task_ID = TASK_MTRSHOW;						//TASK_MTRSHOW
			Btn_OneShotClear(0x02);
		}
		
		if(Btn_IsOneShot(0x04) == 0x04){
			Task_ID = TASK_CLKSET;
			Btn_OneShotClear(0x04);
		}
		
		if(Btn_IsOneShot(0x08) == 0x08){
			Btn_OneShotClear(0x08);
		}
		
	}else{
		if(Btn_IsOneShot(0x02) == 0x02){
			Task_ClkShow_State = STATE_CLKSHOW_HRS;
			Btn_OneShotClear(0x02);
		}
		
		if(Btn_IsOneShot(0x04) == 0x04){
			Task_ClkShow_State = STATE_CLKSHOW_MIN;
			Btn_OneShotClear(0x04);
		}
		
		if(Btn_IsOneShot(0x08) == 0x08){
			Task_ClkShow_State = STATE_CLKSHOW_SEC;
			Btn_OneShotClear(0x08);
		}
	}
	
	/* 7segment control */
	switch(Task_ClkShow_State){
		case STATE_CLKSHOW_SEC:
			_7seg_hi = (clk_sec / 10) % 10;
			_7seg_lo = clk_sec % 10;
			break;
		case STATE_CLKSHOW_MIN:
			_7seg_hi = (clk_min / 10) % 10;
			_7seg_lo = clk_min % 10;
			break;
		case STATE_CLKSHOW_HRS:
			_7seg_hi = (clk_hr / 10) % 10;
			_7seg_lo = clk_hr % 10;
			break;
		default:
			Task_ClkShow_State = STATE_CLKSHOW_SEC;
	}
	
}

void ClkSet(void){
	static uint32_t ClkOldCount = 0;

	
	if((uint32_t)(timecount - ClkOldCount) >= 3000){
		Task_ClkSet_State = !Task_ClkSet_State;
		ClkOldCount = timecount;
	}
	
	if(Btn_IsDown(0x01) == 0x01)
	{
		if(Btn_IsOneShot(0x02) == 0x02){
			Btn_OneShotClear(0x02);
		}
		
		if(Btn_IsOneShot(0x04) == 0x04){
			Btn_OneShotClear(0x04);
		}
		
		if(Btn_IsOneShot(0x08) == 0x08){
			Btn_OneShotClear(0x08);
		}
		
	}
	else
	{
		if(Btn_IsOneShot(0x02) == 0x02)
		{
			switch(Task_ClkShow_State)
			{
				case STATE_CLKSHOW_SEC:
					if(++clk_sec >= 60)
						clk_sec = 0;
					break;
				case STATE_CLKSHOW_MIN:
					if(++clk_min >= 60)
						clk_min = 0;
					break;
				case STATE_CLKSHOW_HRS:
					if(++clk_hr >= 24)
						clk_hr = 0;
					break;
			}
			Btn_OneShotClear(0x02);
		}
		
		if(Btn_IsOneShot(0x04) == 0x04)
		{
			switch(Task_ClkShow_State)
			{
				case STATE_CLKSHOW_SEC:
					if(--clk_sec < 0)
						clk_sec = 59;
					break;
				case STATE_CLKSHOW_MIN:
					if(--clk_min < 0)
						clk_min = 59;
					break;
				case STATE_CLKSHOW_HRS:
					if(--clk_hr < 0)
						clk_hr = 23;
					break;
			}
			Btn_OneShotClear(0x04);
		}
		
		if(Btn_IsOneShot(0x08) == 0x08)
		{
			Task_ID = TASK_CLKSHOW;
			Btn_OneShotClear(0x08);
		}
			/* 7segment control */
	switch(Task_ClkShow_State){
		case STATE_CLKSHOW_SEC:
			_7seg_hi = (clk_sec / 10) % 10;
			_7seg_lo = clk_sec % 10;
			break;
		case STATE_CLKSHOW_MIN:
			_7seg_hi = (clk_min / 10) % 10;
			_7seg_lo = clk_min % 10;
			break;
		case STATE_CLKSHOW_HRS:
			_7seg_hi = (clk_hr / 10) % 10;
			_7seg_lo = clk_hr % 10;
			break;
		default:
			Task_ClkShow_State = STATE_CLKSHOW_SEC;
	}
		
	}
	
	switch(Task_ClkSet_State){
		case STATE_CLKSET_ON:
			switch(Task_ClkShow_State){
				case STATE_CLKSHOW_SEC:
					_7seg_hi = (clk_sec / 10) % 10;
					_7seg_lo = clk_sec % 10;
					break;
				case STATE_CLKSHOW_MIN:
					_7seg_hi = (clk_min / 10) % 10;
					_7seg_lo = clk_min % 10;
					break;
				case STATE_CLKSHOW_HRS:
					_7seg_hi = (clk_hr / 10) % 10;
					_7seg_lo = clk_hr % 10;
					break;
				default:
					Task_ClkShow_State = STATE_CLKSHOW_SEC;
			}
			break;
		case STATE_CLKSET_OFF:
			_7seg_hi = 10;
			_7seg_lo = 10;
			break;
		
		default:
			Task_ClkSet_State = STATE_CLKSET_ON;
	}
	
}
/*
#define TASK_CLKSHOW		0
#define TASK_CLKSET			1
#define TASK_MTRSHOW		2
#define TASK_MTRSET			3
#define TASK_MTRADC			4
*/
void MtrShow(void){
	static uint32_t MtrShowOldCount = 0;
	if((uint32_t)(timecount - MtrShowOldCount) < 1000)//100 ms
		return;
	MtrShowOldCount = timecount;
	if(Btn_IsDown(0x01) == 0x01)
	{
		if(Btn_IsOneShot(0x02) == 0x02){
			Task_ID = TASK_MTRADC;
			Btn_OneShotClear(0x02);
		}
		if(Btn_IsOneShot(0x04) == 0x04){
			Task_ID = TASK_MTRSET;
			Btn_OneShotClear(0x04);
		}
		if(Btn_IsOneShot(0x08) == 0x08){
			mtr_d= 0;
			Btn_OneShotClear(0x08);
		}
	}
	else
	{
		if(Btn_IsOneShot(0x02) == 0x02)
		{
			Task_MtrShow_State=STATE_MTRSHOW_SPEED;
			mtr_set=0;
			Btn_OneShotClear(0x02);
		}
		
		if(Btn_IsOneShot(0x04) == 0x04)
		{
			Task_MtrShow_State=STATE_MTRSHOW_DIR;
			mtr_set=1;
			Btn_OneShotClear(0x04);
		}
		
		if(Btn_IsOneShot(0x08) == 0x08)
		{
			Task_MtrShow_State=STATE_MTRSHOW_TEMP;
			Btn_OneShotClear(0x08);
		}
	}
			/* 7segment control */
			switch(Task_MtrShow_State){
		case STATE_MTRSHOW_SPEED:
			_7seg_hi = (mtr_speed / 10) % 10;
			_7seg_lo = mtr_speed % 10;
			break;
		case STATE_MTRSHOW_DIR:
			_7seg_hi = 0;
			_7seg_lo = mtr_dir % 10;
			break;
		case STATE_MTRSHOW_TEMP:
			_7seg_hi =(ADC_GetTemperature()/10)%10;
			_7seg_lo = ADC_GetTemperature()%10;
			break;
		default:
			Task_MtrShow_State = STATE_MTRSHOW_SPEED;
	}

}

void MtrSet(void){
	static uint32_t MtrSetOldCount = 0;
	if((uint32_t)(timecount - MtrSetOldCount)  >= 3000)//100 ms
	{
	Task_MtrSet_State =!Task_MtrSet_State;
		MtrSetOldCount = timecount;
	}


	if(Btn_IsDown(0x01) == 0x01)
	{
		if(Btn_IsOneShot(0x02) == 0x02){
			Btn_OneShotClear(0x02);
		}
		if(Btn_IsOneShot(0x04) == 0x04){
			Btn_OneShotClear(0x04);
		}
		if(Btn_IsOneShot(0x08) == 0x08){
			Btn_OneShotClear(0x08);
		}
	}
	else
	{
		if(Btn_IsOneShot(0x02) == 0x02)
		{
			if(mtr_set==0)
			{
			mtr_speed++;
			_7seg_hi = (mtr_speed / 10) % 10;
			_7seg_lo = mtr_speed % 10;
			Btn_OneShotClear(0x02);
			}
			
			if(mtr_set==1)
			{
			mtr_dir=1;
			Btn_OneShotClear(0x02);
			}

		}
		
		if(Btn_IsOneShot(0x04) == 0x04)
		{
			if(mtr_set==0)
			{
			mtr_speed--;
			_7seg_hi = (mtr_speed / 10) % 10;
			_7seg_lo = mtr_speed % 10;
			Btn_OneShotClear(0x04);
			}
			
			if(mtr_set==1)
			{
			mtr_dir=0;
			Btn_OneShotClear(0x04);
			}

		}
		
		if(Btn_IsOneShot(0x08) == 0x08)
		{
			Task_ID = TASK_MTRSHOW;
			Btn_OneShotClear(0x08);
		}
		
					/*switch(Task_MtrShow_State){
		case STATE_MTRSHOW_SPEED:
			_7seg_hi = (mtr_speed / 10) % 10;
			_7seg_lo = mtr_speed % 10;
			break;
		case STATE_MTRSHOW_DIR:
			_7seg_hi = 0;
			_7seg_lo = mtr_dir % 10;
			break;
		case STATE_MTRSHOW_TEMP:
			_7seg_hi =(ADC_GetTemperature()/10)%10;
			_7seg_lo = ADC_GetTemperature()%10;
			break;
		default:
			Task_MtrShow_State = STATE_MTRSHOW_SPEED;
	}*/
	}
	mtr_d = StepMtr_RPMtoD(mtr_speed);
			/* 7segment control */
	
		switch(Task_MtrSet_State){
		case STATE_MTRSET_ON:
			switch(Task_MtrShow_State){
		case STATE_MTRSHOW_SPEED:
			_7seg_hi = (mtr_speed / 10) % 10;
			_7seg_lo = mtr_speed % 10;
					break;
		case STATE_MTRSHOW_DIR:
			_7seg_hi = 0;
			_7seg_lo = mtr_dir % 10;
					break;
		case STATE_MTRSHOW_TEMP:
			_7seg_hi =(ADC_GetTemperature()/10)%10;
			_7seg_lo = ADC_GetTemperature()%10;
					break;
				default:
					Task_ClkShow_State = STATE_MTRSHOW_SPEED;
			}
			break;
		case STATE_MTRSET_OFF:
			_7seg_hi = 10;
			_7seg_lo = 10;
			break;
		
		default:
			Task_MtrSet_State = STATE_MTRSET_ON;
	}
		
}

void MtrADC(void){
	static uint32_t SpeedUpdateOldCount = 0;
	static uint8_t select_speed ;
	      select_speed = mtr_speed;
	if((uint32_t)(timecount - SpeedUpdateOldCount) >= 1000)//100 ms
	{
		if(Btn_IsDown(0x01) == 0x01)
		{
			if(Btn_IsOneShot(0x02) == 0x02){
				Task_ID = TASK_CLKSHOW;
				Btn_OneShotClear(0x02);
			}
			
			if(Btn_IsOneShot(0x04) == 0x04){
				mtr_dir = (mtr_dir)? 0 : 1;
				Btn_OneShotClear(0x04);
			}
			
			if(Btn_IsOneShot(0x08) == 0x08){
				stop = stop? 0 : 1;
				select_speed = (stop)? 0 : mtr_speed;
				
				Btn_OneShotClear(0x08);
			}
		}
		else
		{
			if(Btn_IsOneShot(0x02) == 0x02)
			{
				Task_MtrADC_State=STATE_MTRADC_SPEED;
				Btn_OneShotClear(0x02);
			}
			
			if(Btn_IsOneShot(0x04) == 0x04)
			{
				Task_MtrADC_State=STATE_MTRADC_DIR;
				Btn_OneShotClear(0x04);
			}
			
			if(Btn_IsOneShot(0x08) == 0x08)
			{
				Task_MtrADC_State=STATE_MTRADC_TEMP;
				Btn_OneShotClear(0x08);
			}
		}
		mtr_speed = ADC_GetVR();
		mtr_d = StepMtr_RPMtoD(select_speed);
		SpeedUpdateOldCount = timecount;
	}
				/* 7segment control */
				switch(Task_MtrADC_State){
		case STATE_MTRADC_SPEED:
			_7seg_hi = (mtr_speed / 10) % 10;
			_7seg_lo = mtr_speed % 10;
			break;
		case STATE_MTRADC_DIR:
			_7seg_hi = 0;
			_7seg_lo = mtr_dir % 10;
			break;
		case STATE_MTRADC_TEMP:
			_7seg_hi =(ADC_GetTemperature()/10)%10;
			_7seg_lo = ADC_GetTemperature()%10;
			break;
		default:
			Task_MtrADC_State = STATE_MTRADC_SPEED;
	}
}


uint32_t StepMtr_RPMtoD(uint8_t rmp)
{
	return rmp ? 6000/rmp : 0; 
}



