#ifndef __TIMEBASEAGENT_H__
#define __TIMEBASEAGENT_H__
#include "M451Series.h"

extern uint32_t timecount;

void Timebase_Initial(void);
void TMR0_IRQHandler(void);

#endif  /* __TIMEBASEAGENT_H__ */
