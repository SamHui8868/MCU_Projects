#ifndef __SEVENSEGMENTAGENT_H__
#define __SEVENSEGMENTAGENT_H__
#include "myM451Header.h"

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

extern uint8_t _7Seg_OutputBuf[2];

void _7Seg_Initial(void);
void _7Seg_Switch(void);
void _7Seg_Output(void);

#endif  /* __SEVENSEGMENTAGENT_H__ */
