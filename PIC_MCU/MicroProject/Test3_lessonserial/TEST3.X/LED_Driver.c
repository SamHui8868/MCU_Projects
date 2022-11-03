#include "mcc_generated_files/mcc.h"
#include"CD4094.h"
#include<xc.h> 
uint32_t CD4094DriveTimeCounter = 0;
extern uint16_t timeCounter;
void LED_Driver(void){
        if((timeCounter - CD4094DriveTimeCounter)>=1000){
            CD4094DriveTimeCounter = timeCounter;
            CD4094Driver();
        }
        }


