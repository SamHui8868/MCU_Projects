#include "myM451Header.h"
#include "SevenSegmentAgent.h"
#include "M451Series.h"

/* Timer function and variables*/
void TMR0_Initial(void);
uint32_t timecount;

/* Seven segment function and variables*/
void _7Seg_Task(void);

/* Clock function and variables*/
void Clock_Initial(void);
void Clock_TimeTick(void);
void Clock_TimeWrite(void);

uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t display;
uint8_t mode;

int __main(){
	TMR0_Initial();
	_7Seg_Initial();
	Clock_Initial();
	minute=0;
	hour=0;
	PE_MODE &= ~(0x3 << 4);
	PE_MODE |= (0x0 << 4);
	PA_MODE &= ~(0x3 << 16);
	PA_MODE |= (0x0 << 16);
	PB_MODE &= ~(0x3 << 12);
	PB_MODE |= (0x0 << 12);
	mode=0;

	while(1){
		if(mode==0)
		{
			display=second;
			
		}else if(mode==1)
		{
			display=minute;
		}else if(mode==2)
		{
			display=hour;
		}		
		Clock_TimeTick();
		Clock_TimeWrite();	//Write to output buffer
		_7Seg_Task();//7Seg scan
		if(PE2==0)
		{
			mode=0;
			
		}else if(PA8==0)
		{
			mode=1;
		}else if(PB6==0)
		{
			mode=2;
		}
	}
}

void TMR0_IRQHandler(void)
{
	timecount++;
	myTMR0_TIF |= myTMR0_TIF_MASK; //clear interrupt flag by set to 1.
}

void TMR0_Initial(void){
	myCLK_APBCLK0 |= myTMR0_CLKEN_MASK;					//timer0 clock enable
		
	myCLK_CLKSEL1 &= ~myTMR0_CLKSEL_MASK;     	//select timer0 clock source 
	myCLK_CLKSEL1 |= 0x7 << myTMR0_CLKSEL_POS;	//22.1184MHz
	
	myTMR0_CTL &= ~myTMR0_PRESCL_MASK;	
	myTMR0_CTL |= 0xF6 << myTMR0_PRESCL_POS;  	//prescale:254
	
	myTMR0_CTL &= ~myTMR0_OPMODE_MASK;	
	myTMR0_CTL |= 0x01 << myTMR0_OPMODE_POS;  	//0x01 for periodic mode
		
	myTMR0_CMP = 9;												    	//compare value:8.6064
		
	myTMR0_CTL |= myTMR0_INTEN_MASK;						//enable interrupt
	
	myTMR0_CTL |= myTMR0_CNTEN_MASK;						//start timer
	
	myNVIC_ISER2 |= myTMR0_ISER2_MASK;					//enable NVIC timer0 interrupt
	
	timecount = 0;
}

void _7Seg_Task(void){
	static uint32_t _7SegOldCount = 0;
	if((uint32_t)(timecount - _7SegOldCount) > 0){
		_7Seg_Switch();
		_7Seg_Output();
		_7SegOldCount = timecount;
	}
}

void Clock_Initial(void){
	second = 0;
}

void Clock_TimeTick(void){
	static uint32_t ClockOldCount = 0;
	if((uint32_t)(timecount - ClockOldCount) > 10000){
		second++;
		if(second >= 60)
		{
			second = 0;
		  minute++;
		}
		  if(minute>=60)
			{
				hour++;
			}
		ClockOldCount = timecount;
	}
}

void Clock_TimeWrite(void){
	_7Seg_OutputBuf[0] = display % 10;
	_7Seg_OutputBuf[1] = display / 10;
}
