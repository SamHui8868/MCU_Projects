#ifndef __SEVENSEGMENTAGENT_H__
#define __SEVENSEGMENTAGENT_H__
#include "M451Series.h"

//Segment output pin definition
#define SEG_A PB11
#define SEG_B PB12
#define SEG_C PB13
#define SEG_D PB14
#define SEG_E PB15
#define SEG_F PB5
#define SEG_G PD11
#define SEG_H PF2

#define SEG0_EN PD8
#define SEG1_EN PC8

//Switch delay of two segment
#define SWITCH_DELAY 10


//in main.c
extern uint32_t timecount;

/* Initial 7 segment I/O and variables */
void _7Seg_Initial(void);

/* Output task*/
void _7Seg_Task(void);

/* Write new data to output buffer */
void _7Seg_WriteBuf(uint8_t DataH, uint8_t DataL);


void _7Seg_Switch(void);
void _7Seg_Output(void);

#endif  /* __SEVENSEGMENTAGENT_H__ */
