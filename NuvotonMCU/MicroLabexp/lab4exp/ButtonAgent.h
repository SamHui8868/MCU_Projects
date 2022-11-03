#ifndef __BUTTONAGENT_H__
#define __BUTTONAGENT_H__
#include "M451Series.h"

#define SW1 PE2
#define SW2 PA8
#define SW3 PB6
#define SW4 PB7

#define BTN_STATE_UP				0
#define BTN_STATE_BOUNCING	1
#define BTN_STATE_ONESHOT		2
#define BTN_STATE_DOWN			3

#define DEBOUNCEDELAY			100

extern uint32_t timecount;

void Btn_Initial(void);
void Btn_Task(void);

uint8_t Btn_IsDown(uint8_t btnSelMask);
uint8_t Btn_IsOneShot(uint8_t btnSelMask);
void Btn_OneShotClear(uint8_t btnSelMask);

#endif  /* __BUTTONAGENT_H__ */


