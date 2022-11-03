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

// get/set LED_1 aliases
#define LED_1_TRIS                 TRISAbits.TRISA0
#define LED_1_LAT                  LATAbits.LATA0
#define LED_1_PORT                 PORTAbits.RA0
#define LED_1_ANS                  ANSELAbits.ANSA0
#define LED_1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LED_1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LED_1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LED_1_GetValue()           PORTAbits.RA0
#define LED_1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LED_1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LED_1_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define LED_1_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set LED_2 aliases
#define LED_2_TRIS                 TRISAbits.TRISA1
#define LED_2_LAT                  LATAbits.LATA1
#define LED_2_PORT                 PORTAbits.RA1
#define LED_2_ANS                  ANSELAbits.ANSA1
#define LED_2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LED_2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LED_2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LED_2_GetValue()           PORTAbits.RA1
#define LED_2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LED_2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LED_2_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define LED_2_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set SW aliases
#define SW_TRIS                 TRISAbits.TRISA2
#define SW_LAT                  LATAbits.LATA2
#define SW_PORT                 PORTAbits.RA2
#define SW_ANS                  ANSELAbits.ANSA2
#define SW_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define SW_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define SW_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define SW_GetValue()           PORTAbits.RA2
#define SW_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define SW_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define SW_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define SW_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set LED_3 aliases
#define LED_3_TRIS                 TRISCbits.TRISC6
#define LED_3_LAT                  LATCbits.LATC6
#define LED_3_PORT                 PORTCbits.RC6
#define LED_3_ANS                  ANSELCbits.ANSC6
#define LED_3_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define LED_3_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define LED_3_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define LED_3_GetValue()           PORTCbits.RC6
#define LED_3_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define LED_3_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define LED_3_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define LED_3_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set LED_4 aliases
#define LED_4_TRIS                 TRISCbits.TRISC7
#define LED_4_LAT                  LATCbits.LATC7
#define LED_4_PORT                 PORTCbits.RC7
#define LED_4_ANS                  ANSELCbits.ANSC7
#define LED_4_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define LED_4_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define LED_4_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define LED_4_GetValue()           PORTCbits.RC7
#define LED_4_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define LED_4_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define LED_4_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define LED_4_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

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