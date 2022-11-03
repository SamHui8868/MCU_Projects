/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC18F23K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.35	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set CD4021_PS aliases
#define CD4021_PS_TRIS                 TRISAbits.TRISA3
#define CD4021_PS_LAT                  LATAbits.LATA3
#define CD4021_PS_PORT                 PORTAbits.RA3
#define CD4021_PS_ANS                  ANSELAbits.ANSA3
#define CD4021_PS_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define CD4021_PS_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define CD4021_PS_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define CD4021_PS_GetValue()           PORTAbits.RA3
#define CD4021_PS_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define CD4021_PS_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define CD4021_PS_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define CD4021_PS_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set CD4021_Data aliases
#define CD4021_Data_TRIS                 TRISAbits.TRISA4
#define CD4021_Data_LAT                  LATAbits.LATA4
#define CD4021_Data_PORT                 PORTAbits.RA4
#define CD4021_Data_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define CD4021_Data_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define CD4021_Data_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define CD4021_Data_GetValue()           PORTAbits.RA4
#define CD4021_Data_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define CD4021_Data_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set CD4021_Clock aliases
#define CD4021_Clock_TRIS                 TRISAbits.TRISA5
#define CD4021_Clock_LAT                  LATAbits.LATA5
#define CD4021_Clock_PORT                 PORTAbits.RA5
#define CD4021_Clock_ANS                  ANSELAbits.ANSA5
#define CD4021_Clock_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define CD4021_Clock_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define CD4021_Clock_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define CD4021_Clock_GetValue()           PORTAbits.RA5
#define CD4021_Clock_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define CD4021_Clock_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define CD4021_Clock_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define CD4021_Clock_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/