/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F25K22
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "crc16.h"
/*
                         Main application
 */
#define Max_Register_Size 66
#define current(Index) Modbus_Holding_Register[Index]
#define data_count Modbus_Holding_Register[60]
#define current_now Modbus_Holding_Register[61]
#define current_limit Modbus_Holding_Register[62]
#define sample_minute Modbus_Holding_Register[63]
#define relay Modbus_Holding_Register[64]
#define jumping Modbus_Holding_Register[65]
volatile uint16_t Modbus_Holding_Register[Max_Register_Size];
volatile uint16_t timer;
union modbus_485
{
    struct
	{
		unsigned char DeviceAddress;
		unsigned char func;
		unsigned char Address_Hi;
		unsigned char Address_Lo;
		unsigned char reg_num_Hi;
		unsigned char reg_num_Lo;
		unsigned char CRC_Lo;
		unsigned char CRC_Hi;
	}CMD01_04;
	struct
	{
		unsigned char DeviceAddress;
		unsigned char func;
		unsigned char Address_Hi;
		unsigned char Address_Lo;
		unsigned char data_Hi;
		unsigned char data_Lo;
		unsigned char CRC_Lo;
		unsigned char CRC_Hi;
	}CMD05_06;
	struct
	{
		unsigned char DeviceAddress;
		unsigned char func;
		unsigned char Address_Hi;
		unsigned char Address_Lo;
		unsigned char reg_num_Hi;
		unsigned char reg_num_Lo;
		unsigned char Byte_count;
		unsigned char buf[249];
	}CMD0F_10;

	struct
	{
		unsigned char DeviceAddress;
		unsigned char func;
		unsigned char ByteCount;
		unsigned char buf[253];
	}Reply01_04;
    struct
	{
		unsigned char DeviceAddress;
		unsigned char func;
		unsigned char Address_Hi;
		unsigned char Address_Lo;
		unsigned char data_Hi;
		unsigned char data_Lo;
		unsigned char CRC_Lo;
		unsigned char CRC_Hi;
	}Reply05_06;
	struct
	{
		unsigned char DeviceAddress;
		unsigned char func;
		unsigned char Address_Hi;
		unsigned char Address_Lo;
		unsigned char reg_num_Hi;
		unsigned char reg_num_Lo;
		unsigned char CRC_Lo;
		unsigned char CRC_Hi;
	}Reply0F_10;

	struct
	{
		unsigned char DeviceAddress;
		unsigned char func;
		unsigned char buf[254];
	}CMD;

	unsigned char buf[256];
};

void string_tx_uart2(char *text)
{
    uint8_t i;
    for(i=0;text[i]!=0;i++)
    {
        EUSART2_Write(text[i]);
    }
    return;
}
void uint_tx_uart2(uint32_t number,uint8_t len)
{
    uint8_t i;
    for(i=len;i>=1;i--)
    {
        switch((number>>(i-1)*4)&0x0f)
        {
            case 0x00:
                EUSART2_Write('0');
                break;
            case 0x01:
                EUSART2_Write('1');
                break;
            case 0x02:
                EUSART2_Write('2');
                break;
            case 0x03:
                EUSART2_Write('3');
                break;
            case 0x04:
                EUSART2_Write('4');
                break;
            case 0x05:
                EUSART2_Write('5');
                break;
            case 0x06:
                EUSART2_Write('6');
                break;
            case 0x07:
                EUSART2_Write('7');
                break;
            case 0x08:
                EUSART2_Write('8');
                break;
            case 0x09:
                EUSART2_Write('9');
                break;
            case 0x0a:
                EUSART2_Write('a');
                break;
            case 0x0b:
                EUSART2_Write('b');
                break;
            case 0x0c:
                EUSART2_Write('c');
                break;
            case 0x0d:
                EUSART2_Write('d');
                break;
            case 0x0e:
                EUSART2_Write('e');
                break;
            case 0x0f:
                EUSART2_Write('f');
                break;
        }
    }
}
uint16_t u32_sqrt(uint32_t a)
{
  uint32_t rem = 0;
  uint32_t root = 0;
  uint32_t pisor = 0;
  for(int i=0; i<16; i++)
  {
    root <<= 1;
    rem = ((rem << 2) + (a >> 30));
    a <<= 2;
    pisor = (root<<1) + 1;
    if(pisor <= rem)
    {
      rem -= pisor;
      root++;
    }
  }
  return (uint16_t)(root);
}
void check_register()
{
    if(relay)
    {
        if(jumping)
        {
            string_tx_uart2("jumping,relay can't open\n");
            relay=0;
            IO_relay_LAT=1;
        }
        else
        {
            string_tx_uart2("relay open\n");
            IO_relay_LAT=0;
        }
    }
    else
    {
        string_tx_uart2("relay close\n");
        IO_relay_LAT=1;
    }
}
void ADC_run()
{
    static uint32_t Vrms=0;
    static uint32_t sample_total=0;
    static uint16_t adc_count=0;
    static uint16_t sample_count=0;

    if(ADC_IsConversionDone())
    {
        uint16_t adc_value=ADC_GetConversionResult();
        ADC_StartConversion();
        
        uint32_t Vnow=(adc_value>=512)?adc_value-512:512-adc_value;
        Vrms+=Vnow*Vnow;
        adc_count++;
    }

    if(125<=timer)
    {
        timer=0;
        current_now=u32_sqrt(Vrms/adc_count);
        sample_total=current_now;
        if(current_now>current_limit)
        {
            relay=0;
            jumping=1;
            string_tx_uart2("jumping\n");
            check_register();
        }
        Vrms=0;
        adc_count=0;
        
        if(sample_minute)
        {
            sample_count++;
            if(sample_count>=sample_minute)
            {
                current(data_count%60)=sample_total/sample_count;
                data_count=(data_count==59999)?0:data_count+1;
                sample_count=0;
            }
        }
        else
            sample_count=0;
    }
}
uint8_t uart_run() //careful! use euart1.c variable
{
    uint16_t addr,len,data,crc,i;
    union modbus_485 *recv=(union modbus_485*)eusart1RxBuffer;
    union modbus_485 *tran=(union modbus_485*)eusart1TxBuffer;

    PIE1bits.RC1IE = 0;//close rx ISR
    PIE1bits.TX1IE = 0;//close tx ISR

    if(recv->CMD.DeviceAddress==0xff)
    {
        string_tx_uart2("new data, check crc\n");
        for(i=0;i<eusart1RxCount;i++)
        {
            uint_tx_uart2(eusart1RxBuffer[i],2);
            EUSART2_Write(' ');
        }
        EUSART2_Write('\n');
        crc=crcGen(eusart1RxBuffer,eusart1RxCount-2);
        if(crc==(eusart1RxBuffer[eusart1RxCount-1]<<8)+eusart1RxBuffer[eusart1RxCount-2])
        {
            string_tx_uart2("crc:O\n");
            switch(recv->CMD.func)
            {
                case 0x03:
                    addr=(recv->CMD01_04.Address_Hi<<8)+recv->CMD01_04.Address_Lo;
                    len=(recv->CMD01_04.reg_num_Hi<<8)+recv->CMD01_04.reg_num_Lo;
                    string_tx_uart2("code:03");
                    string_tx_uart2(" addr:");
                    uint_tx_uart2(addr,4);
                    string_tx_uart2(" len:");
                    uint_tx_uart2(len,4);
                    string_tx_uart2("\n");


                    if(addr+len>Max_Register_Size)//ILLEGAL DATA ADDRESS
                    {
                        tran->CMD.DeviceAddress=0xff;
                        tran->CMD.func=0x83;
                        tran->CMD.buf[0]=0x02;
                        tran->CMD.buf[2]=0x2E;
                        tran->CMD.buf[1]=0x71;
                        eusart1TxBufferRemaining=sizeof(eusart1TxBuffer)-5;
                        break;
                    }

                    tran->Reply01_04.DeviceAddress=0xff;
                    tran->Reply01_04.func=0x03;
                    tran->Reply01_04.ByteCount=len<<1;
                    for(i=0;i<len;i++)
                    {
                        tran->Reply01_04.buf[i*2]=Modbus_Holding_Register[addr+i]>>8;
                        tran->Reply01_04.buf[i*2+1]=Modbus_Holding_Register[addr+i]&0xff;
                    }

                    crc=crcGen(eusart1TxBuffer,len*2+3);
                    tran->Reply01_04.buf[len*2+1]=crc>>8;
                    tran->Reply01_04.buf[len*2]=crc&0xff;

                    eusart1TxBufferRemaining=sizeof(eusart1TxBuffer)-len*2-5;
                    break;

                case 0x06:
                    addr=(recv->Reply05_06.Address_Hi<<8)+recv->Reply05_06.Address_Lo;
                    data=(recv->Reply05_06.data_Hi<<8)+recv->Reply05_06.data_Lo;
                    string_tx_uart2("code:06");
                    string_tx_uart2(" addr:");
                    uint_tx_uart2(addr,4);
                    string_tx_uart2(" data:");
                    uint_tx_uart2(data,4);
                    string_tx_uart2("\n");

                   if(addr>=Max_Register_Size)//ILLEGAL DATA ADDRESS
                    {
                        tran->CMD.DeviceAddress=0xff;
                        tran->CMD.func=0x86;
                        tran->CMD.buf[0]=0x02;
                        tran->CMD.buf[2]=0x7E;
                        tran->CMD.buf[1]=0x72;
                        eusart1TxBufferRemaining=sizeof(eusart1TxBuffer)-5;
                        break;
                    }

                    Modbus_Holding_Register[addr]=data;
                    check_register();

                    for(i=0;i<8;i++)
                        eusart1TxBuffer[i]=eusart1RxBuffer[i];

                    eusart1TxBufferRemaining=sizeof(eusart1TxBuffer)-8;
                    break;

                case 0x10:
                    addr=(recv->CMD0F_10.Address_Hi<<8)+recv->CMD0F_10.Address_Lo;
                    len=recv->CMD0F_10.Byte_count>>1;
                    string_tx_uart2("code:10");
                    string_tx_uart2(" addr:");
                    uint_tx_uart2(addr,4);
                    string_tx_uart2(" len:");
                    uint_tx_uart2(len,4);
                    string_tx_uart2("\n");

                    if(addr+len>Max_Register_Size)//ILLEGAL DATA ADDRESS
                    {
                        tran->CMD.DeviceAddress=0xff;
                        tran->CMD.func=0x90;
                        tran->CMD.buf[0]=0x02;
                        tran->CMD.buf[2]=0x1E;
                        tran->CMD.buf[1]=0x7C;
                        eusart1TxBufferRemaining=sizeof(eusart1TxBuffer)-5;
                        break;
                    }

                    for(i=0;i<len;i++)
                        Modbus_Holding_Register[addr+i]=(recv->CMD0F_10.buf[i*2]<<8)+recv->CMD0F_10.buf[i*2+1];
                    check_register();

                    for(i=0;i<6;i++)
                        eusart1TxBuffer[i]=eusart1RxBuffer[i];

                    crc=crcGen(eusart1TxBuffer,6);
                    eusart1TxBuffer[7]=crc>>8;
                    eusart1TxBuffer[6]=crc&0xff;

                    eusart1TxBufferRemaining=sizeof(eusart1TxBuffer)-8;
                    break;

                default://ILLEGAL FUNCTION
                    string_tx_uart2("code:");
                    uint_tx_uart2(eusart1RxBuffer[1],2);
                    string_tx_uart2(" illegal\n");
                    tran->CMD.DeviceAddress=0xff;
                    tran->CMD.func=recv->CMD.func|0x80;
                    tran->CMD.buf[0]=0x01;

                    crc=crcGen(eusart1TxBuffer,3);
                    tran->CMD.buf[2]=crc>>8;
                    tran->CMD.buf[1]=crc&0xff;

                    eusart1TxBufferRemaining=sizeof(eusart1TxBuffer)-5;
                    break;
            }
            IO_UARTTX_LAT=1;//start to Transmit
            eusart1TxTail = 0;//back TxTail
            PIE1bits.TX1IE = 1;//open tx ISR
            return 1;
        }
        else
        {
            string_tx_uart2("crc:X\n");
        }
    }
    else
    {
        string_tx_uart2("new data, for:");
        uint_tx_uart2(eusart1RxBuffer[0],2);
        string_tx_uart2("\n");
    }
    return 0;
}
void timer_8ms()
{
    timer++;
}
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    ADC_SelectChannel(channel_AN0);
    TMR0_SetInterruptHandler(timer_8ms);

    uint8_t i;
    for(i=0;i<60;i++)
        current(i)=0;
    timer=0;
    data_count=0;
    current_now=0;
    current_limit=300;
    sample_minute=1;
    relay=1;
    jumping=0;

    IO_relay_LAT=0;
    IO_UARTTX_LAT=0;

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    int8_t state=-1;
    while (1)
    {
        switch(state)
        {
        case -1:
            if(125<=timer)
            {
                string_tx_uart2("run\n");
                PIE1bits.RC1IE = 1;
                timer=0;
                state=0;
            }
            break;
        case 0:
            if(EUSART1_is_rx_ready())
            {
                timer=0;
                state=1;
                break;
            }
            ADC_run();
            break;
        case 1:
            if(34<=timer)
            {
                if(uart_run())
                {
                    timer=0;
                    state=2;
                }
                else
                {
                    PIE1bits.RC1IE = 1;
                    timer=0;
                    state=3;
                }
            }
            break;
        case 2:
            if(EUSART1_is_tx_done())
            {
                IO_UARTTX_LAT=0;
                PIE1bits.RC1IE = 1;//open rx ISR
                timer=0;
                state=3;
            }
            break;
        case 3:
            if(1<timer)
            {
                eusart1RxHead = 0;//back RxHead
                eusart1RxCount = 0;//clear rx data
                timer=0;
                state=0;
            }
            break;
        }
    }
}
/**
 End of File
*/
