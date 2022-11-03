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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC18F25K22
        Driver Version    :  2.11
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

// get/set led aliases
#define led_TRIS                 TRISAbits.TRISA0
#define led_LAT                  LATAbits.LATA0
#define led_PORT                 PORTAbits.RA0
#define led_ANS                  ANSELAbits.ANSA0
#define led_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define led_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define led_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define led_GetValue()           PORTAbits.RA0
#define led_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define led_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define led_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define led_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set led2 aliases
#define led2_TRIS                 TRISAbits.TRISA1
#define led2_LAT                  LATAbits.LATA1
#define led2_PORT                 PORTAbits.RA1
#define led2_ANS                  ANSELAbits.ANSA1
#define led2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define led2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define led2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define led2_GetValue()           PORTAbits.RA1
#define led2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define led2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define led2_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define led2_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set led3 aliases
#define led3_TRIS                 TRISAbits.TRISA2
#define led3_LAT                  LATAbits.LATA2
#define led3_PORT                 PORTAbits.RA2
#define led3_ANS                  ANSELAbits.ANSA2
#define led3_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define led3_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define led3_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define led3_GetValue()           PORTAbits.RA2
#define led3_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define led3_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define led3_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define led3_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

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