/**
  Generated Interrupt Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F23K22
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45 or later
        MPLAB 	          :  MPLAB X 4.15
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

#include "interrupt_manager.h"
#include "mcc.h"

void  INTERRUPT_Initialize (void)
{
    // Enable Interrupt Priority Vectors
    RCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors

    // RCI - high priority
    IPR1bits.RC1IP = 1;

    // TXI - high priority
    IPR1bits.TX1IP = 1;

    // TMRI - high priority
    INTCON2bits.TMR0IP = 1;


    // ADI - low priority
    IPR1bits.ADIP = 0;    

    // RCI - low priority
    IPR3bits.RC2IP = 0;    

    // TXI - low priority
    IPR3bits.TX2IP = 0;    

}

void interrupt INTERRUPT_InterruptManagerHigh (void)
{
   // interrupt handler
    if(PIE1bits.RC1IE == 1 && PIR1bits.RC1IF == 1)
    {
        EUSART1_RxDefaultInterruptHandler();
    }
    else if(PIE1bits.TX1IE == 1 && PIR1bits.TX1IF == 1)
    {
        EUSART1_TxDefaultInterruptHandler();
    }
    else if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        TMR0_ISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}

void interrupt low_priority INTERRUPT_InterruptManagerLow (void)
{
    // interrupt handler
    if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
    {
        ADC_ISR();
    }
    else if(PIE3bits.RC2IE == 1 && PIR3bits.RC2IF == 1)
    {
        EUSART2_RxDefaultInterruptHandler();
    }
    else if(PIE3bits.TX2IE == 1 && PIR3bits.TX2IF == 1)
    {
        EUSART2_TxDefaultInterruptHandler();
    }
    else
    {
        //Unhandled Interrupt
    }
}
/**
 End of File
*/
