#include "TimebaseAgent.h"



void Timebase_Initial(void){
	CLK->APBCLK0 |= CLK_APBCLK0_TMR0CKEN_Msk;					//timer0 clock enable
		
	CLK->CLKSEL1 &= ~CLK_CLKSEL1_TMR0SEL_Msk;     	//select timer0 clock source 
	CLK->CLKSEL1 |= 0x7 << CLK_CLKSEL1_TMR0SEL_Pos;	//22.1184MHz
	
	TIMER0->CTL &= ~TIMER_CTL_PSC_Msk;	
	TIMER0->CTL |= 0x00 << TIMER_CTL_PSC_Pos;  	//prescale:0
	
	TIMER0->CTL &= ~TIMER_CTL_OPMODE_Msk;	
	TIMER0->CTL |= 0x01 << TIMER_CTL_OPMODE_Pos;  	//0x01 for periodic mode
		
	TIMER0->CMP = 2211;												  //compare value:2211
		
	TIMER0->CTL |= TIMER_CTL_INTEN_Msk;						//enable interrupt
	
	TIMER0->CTL |= TIMER_CTL_CNTEN_Msk;						//start timer
	
	NVIC->ISER[1] |= 1;					//enable NVIC timer0 interrupt
	
	timecount = 0;
}

void TMR0_IRQHandler(void){
	timecount++;
	TIMER0->INTSTS |= TIMER_INTSTS_TIF_Msk;	
}


