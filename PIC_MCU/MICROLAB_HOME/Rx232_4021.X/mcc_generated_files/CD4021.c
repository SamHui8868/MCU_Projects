/*
 * File:   CD4021.c
 * Author: user
 *
 * Created on March 19, 2019, 12:54 PM
 */


#include "CD4021.h"
#include "mcc.h"
static uint8_t CD4021Buffer;

void CD4021Driver(){
    uint8_t temp = 0;
    CD4021_Clock_LAT = 0;
    CD4021_PS_LAT = 0;
    NOP();
    NOP();
    CD4021_PS_LAT = 1;
    NOP();
    NOP();
    CD4021_PS_LAT = 0;
    for(int i=0;i<8;i++){
        temp =temp|(CD4021_Data_PORT);
        NOP();
        NOP();
        CD4021_Clock_LAT = 1;
        NOP();
        NOP();
        CD4021_Clock_LAT = 0;
        if(i<7)
            temp<<=1;
    }
    CD4021Buffer = temp;
    return;
}
uint8_t CD4021Read(){
    return CD4021Buffer;
}
