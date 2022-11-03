#ifndef __STEPMOTORAGENT_H__
#define __STEPMOTORAGENT_H__
#include "M451Series.h"

#define MTR_A			PE11
#define MTR_B			PE10
#define MTR_A_BAR	PE13
#define MTR_B_BAR	PE12

extern uint32_t timecount;

void StepMtr_Initial(void);
void StepMtr_Task(uint8_t dir, uint32_t d);

#endif  /* __STEPMOTORAGENT_H__ */


