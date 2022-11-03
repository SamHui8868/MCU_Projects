#include "ButtonAgent.h"

uint8_t  BtnDownFlag;
uint8_t  BtnOneShot;
uint8_t  BtnState[4];
uint32_t BtnOldCount[4];
volatile uint32_t* pSW[4];

void Btn_Initial(void){
	GPIO_SetMode(PE, BIT2, GPIO_MODE_INPUT);
	GPIO_SetMode(PA, BIT8, GPIO_MODE_INPUT);
	GPIO_SetMode(PB, BIT6, GPIO_MODE_INPUT);
	GPIO_SetMode(PB, BIT7, GPIO_MODE_INPUT);
	
	BtnDownFlag = 0;
	BtnOneShot = 0;
	pSW[0] = &SW1;
	pSW[1] = &SW2;
	pSW[2] = &SW3;
	pSW[3] = &SW4;
	
	for(uint8_t i = 0; i < 4 ; i++){
		BtnState[i] = BTN_STATE_UP;
		BtnOldCount[i] = 0;
	}
}

void Btn_Task(void){
	for(uint8_t i = 0 ; i < 4 ; i++){
		
		switch(BtnState[i]){
			case BTN_STATE_UP:
				if(*pSW[i] == 0){
					BtnState[i] = BTN_STATE_BOUNCING;
				}
				BtnOldCount[i] = timecount;
				BtnDownFlag &= ~(0x01 << i);
				BtnOneShot &= ~(0x01 << i);
				break;
				
			case BTN_STATE_BOUNCING:
				if(*pSW[i] == 1){
					BtnState[i] = BTN_STATE_UP;
				}else if((uint32_t)(timecount - BtnOldCount[i]) > DEBOUNCEDELAY){
					BtnState[i] = BTN_STATE_ONESHOT;
				}
				break;
				
			case BTN_STATE_ONESHOT:
					BtnState[i] = BTN_STATE_DOWN;
					BtnOneShot |= 0x01 << i;
				break;
				
			case BTN_STATE_DOWN:
				if(*pSW[i] == 1){
					BtnState[i] = BTN_STATE_UP;
				}else {
					BtnDownFlag |= 0x01 << i;
				}
				break;
				
			default:
				BtnState[i] = BTN_STATE_UP;
			
		}//switch(BtnState[i])
	}//for(0:3)
}

uint8_t Btn_IsDown(uint8_t btnSelMask){
	return BtnDownFlag & btnSelMask;
}

uint8_t Btn_IsOneShot(uint8_t btnSelMask){
	return BtnOneShot & btnSelMask;
}

void Btn_OneShotClear(uint8_t btnSelMask){
	BtnOneShot &= ~btnSelMask;
}

