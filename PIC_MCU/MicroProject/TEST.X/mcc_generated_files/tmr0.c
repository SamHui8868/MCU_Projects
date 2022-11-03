/**
  TMR0 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr0.c

  @Summary
    This is the generated driver implementation file for the TMR0 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR0.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC18F25K22
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.30
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr0.h"
#include "mcc.h"
#include "pin_manager.h"

/**
  Section: Global Variables Definitions
*/



volatile uint8_t timer0ReloadVal;

/**
  Section: TMR0 APIs
*/


void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface

    // TMR0H 0; 
    TMR0H = 0x00;

    // TMR0L 156; 
    TMR0L = 0x9C;

	
    // Load TMR0 value to the 8-bit reload variable
    timer0ReloadVal = 156;

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    // Set Default Interrupt Handler
   
    // T0PS 1:16; T08BIT 8-bit; T0SE Increment_hi_lo; T0CS FOSC/4; TMR0ON enabled; PSA assigned; 
    T0CON = 0xD3;
}
int timecount;
void TMR0_ISR(void)
{
    

    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    // reload TMR0
    TMR0L = timer0ReloadVal;
    timecount++;

    // add your TMR0 interrupt custom code
}


/**
  End of File
*/