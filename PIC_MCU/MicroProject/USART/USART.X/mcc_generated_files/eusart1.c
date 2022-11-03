/**
  EUSART1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart1.c

  @Summary
    This is the generated driver implementation file for the EUSART1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for EUSART1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC18F23K22
        Driver Version    :  2.1.0
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
#include "eusart1.h"




/**
  Section: Macro Declarations
*/

#define EUSART1_TX_BUFFER_SIZE 8
#define EUSART1_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
*/
volatile uint8_t eusart1TxHead = 0;
volatile uint8_t eusart1TxTail = 0;
volatile uint8_t eusart1TxBuffer[EUSART1_TX_BUFFER_SIZE];


volatile uint8_t eusart1RxHead = 0;
volatile uint8_t eusart1RxTail = 0;
volatile uint8_t eusart1RxBuffer[EUSART1_RX_BUFFER_SIZE];
#define buffer_size 16
uint8_t TX_CQ[buffer_size];
uint8_t RX_CQ[buffer_size];
uint8_t TX_Head;
uint8_t TX_Tail;
uint8_t RX_Head;
uint8_t RX_Tail;



/**
  Section: EUSART1 APIs
*/
void (*EUSART1_TxDefaultInterruptHandler)(void);
void (*EUSART1_RxDefaultInterruptHandler)(void);


void EUSART1_Initialize(void)
{
    // disable interrupts before changing states
    PIE1bits.RC1IE = 0;
    EUSART1_SetRxInterruptHandler(EUSART1_Receive_ISR);
    PIE1bits.TX1IE = 0;
    EUSART1_SetTxInterruptHandler(EUSART1_Transmit_ISR);
    // Set the EUSART1 module to the options selected in the user interface.

    // ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; WUE disabled; ABDEN disabled; DTRXP not_inverted; 
    BAUDCON1 = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA1 = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode; 
    TXSTA1 = 0x24;

    // 
    SPBRG1 = 0x33;

    // 
    SPBRGH1 = 0x00;

    // enable receive interrupt
    PIE1bits.RC1IE = 1;
}


uint8_t EUSART1_Read(void)
{
    return RXdeQ();
}

void EUSART1_Write(uint8_t txData)
{
    TXenQ( txData);
}

void EUSART1_Write_Task(void)
{
    TXREG1=TXdeQ();
}

void EUSART1_Receive_ISR(void)
{
   if(1==RCSTA1bits.OERR) 
   {
    RCSTA1bits.CREN = 0;
    RCSTA1bits.CREN = 1;
   }
   uint8_t c= RCREG1;
   if(RXisFull())
   {
       RXenQ(c);
   }

    // or set custom function using EUSART1_SetRxInterruptHandler()
}


bool TXisFull(void)
{
	//check the CQ is Full?
	return  ((TX_Head+1)&0x0F) == TX_Tail; 
}
bool TXisEmpty(void)
{
        //check the CQ is Empty?
        return  TX_Head == TX_Tail; 
}
uint8_t TXdeQ(void)
{
	uint8_t  data;
	data = TX_CQ[TX_Tail++];
	TX_Tail &= 0x0F;
    	return data;
}
void TXenQ(uint8_t data)
{
	TX_CQ[TX_Head++] = data;
    	TX_Head &= 0x0F;
}



bool RXisFull(void)
{
	//check the CQ is Full?
	return  ((RX_Head+1)&0x0F) == RX_Tail; 
}
bool RXisEmpty(void)
{
        //check the CQ is Empty?
        return  RX_Head == RX_Tail; 
}
uint8_t RXdeQ(void)
{
	uint8_t  data;
	data = RX_CQ[RX_Tail++];
	RX_Tail &= 0x0F;
    	return data;
}
void RXenQ(uint8_t data)
{
	RX_CQ[TX_Head++] = data;
    	RX_Head &= 0x0F;
}
  
void EUSART1_SetTxInterruptHandler(void (* interruptHandler)(void)){
    EUSART1_TxDefaultInterruptHandler = interruptHandler;
}

void EUSART1_SetRxInterruptHandler(void (* interruptHandler)(void)){
    EUSART1_RxDefaultInterruptHandler = interruptHandler;
}
/**
  End of File
*/
