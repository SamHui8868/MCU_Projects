/*
 * File:   _4094.c
 * Author: user
 *
 * Created on March 19, 2019, 12:42 PM
 */


#include "CD4094.h"
#include "mcc.h"
#include "pin_manager.h"
union Buffer16{
    struct{
        uint8_t BufferH;
        uint8_t BufferL;
    };
    uint16_t Buffer;
};
static union Buffer16 CD4094Buffer;
uint16_t temp;
void CD4094Driver(){
    temp = CD4094Buffer.Buffer;
    CD4094_Data_LAT = CD4094_Strobe_LAT = CD4094_Clock_LAT = 0;
    NOP();
    NOP();
    for(int i=0;i<16;i++){
        CD4094_Data_LAT = (temp&0x0001);
        NOP();
        NOP();
        CD4094_Clock_LAT = 1;
        NOP();
        NOP();
        CD4094_Clock_LAT = 0;
        if(i==15){
            CD4094_Strobe_LAT = 1;
            NOP();
            NOP();
            CD4094_Strobe_LAT = 0;
        }
        temp>>=1;
        NOP();
        NOP();
    }
    //print data from CD4094Buffer.Buffer to 4094
    return;
}
void CD4094Write16(uint16_t Buffer){
    CD4094Buffer.Buffer = Buffer;
    //put Buffer into CD4094Buffer.Buffer
}
void CD4094WriteH(uint8_t BufferH){
    CD4094Buffer.BufferH = BufferH;
    //put BufferH into CD4094Buffer.BufferH
}
void CD4094WriteL(uint8_t BufferL){
    CD4094Buffer.BufferL = BufferL;
    //put BufferL into CD4094Buffer.BufferL
}