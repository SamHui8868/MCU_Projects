 #include "mcc_generated_files/mcc.h"
#include"CD4021.h"
#include<xc.h> 
 uint32_t  CD4021DriveTimeCounter = 0;
 extern uint16_t timeCounter;
void DIPSW_Driver(void){

       if((timeCounter - CD4021DriveTimeCounter)>=5){
            CD4021DriveTimeCounter = timeCounter;
            CD4021Driver();
        }
}
