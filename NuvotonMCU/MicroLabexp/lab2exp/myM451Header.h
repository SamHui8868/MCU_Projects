#ifndef __MYM451HEADER_H__
#define __MYM451HEADER_H__

#include <stdint.h>
#include "myGPIO.h"

#define myGPIO_BASE_ADDR 0x40004000
#define myPA_MODE (*(uint32_t*)(myGPIO_BASE_ADDR + 0x000))
#define myPB_MODE (*(uint32_t*)(myGPIO_BASE_ADDR + 0x040))
#define myPC_MODE (*(uint32_t*)(myGPIO_BASE_ADDR + 0x080))
#define myPD_MODE (*(uint32_t*)(myGPIO_BASE_ADDR + 0x0C0))
#define myPE_MODE (*(uint32_t*)(myGPIO_BASE_ADDR + 0x100))
#define myPF_MODE (*(uint32_t*)(myGPIO_BASE_ADDR + 0x140))

#define GPIO_INPUT_MODE 0x00
#define GPIO_OUTPUT_MODE 0x01

#define myPA_DATA_BASE_ADDR (myGPIO_BASE_ADDR + 0x800)
#define myPB_DATA_BASE_ADDR (myGPIO_BASE_ADDR + 0x840)
#define myPC_DATA_BASE_ADDR (myGPIO_BASE_ADDR + 0x880)
#define myPD_DATA_BASE_ADDR (myGPIO_BASE_ADDR + 0x8C0)
#define myPE_DATA_BASE_ADDR (myGPIO_BASE_ADDR + 0x900)
#define myPF_DATA_BASE_ADDR (myGPIO_BASE_ADDR + 0x940)

//GPIO_BASE_ADDR + 0x800 + (0x40 * port) + (0x04 * pin)
#define PA0             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (0 << 2 )))
#define PA1             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (1 << 2 )))
#define PA2             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (2 << 2 )))
#define PA3             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (3 << 2 )))
#define PA4             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (4 << 2 )))
#define PA5             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (5 << 2 )))
#define PA6             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (6 << 2 )))
#define PA7             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (7 << 2 )))
#define PA8             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (8 << 2 )))
#define PA9             (*(uint32_t*)(myPA_DATA_BASE_ADDR + (9 << 2 )))
#define PA10            (*(uint32_t*)(myPA_DATA_BASE_ADDR + (10 << 2 )))
#define PA11            (*(uint32_t*)(myPA_DATA_BASE_ADDR + (11 << 2 )))
#define PA12            (*(uint32_t*)(myPA_DATA_BASE_ADDR + (12 << 2 )))
#define PA13            (*(uint32_t*)(myPA_DATA_BASE_ADDR + (13 << 2 )))
#define PA14            (*(uint32_t*)(myPA_DATA_BASE_ADDR + (14 << 2 )))
#define PA15            (*(uint32_t*)(myPA_DATA_BASE_ADDR + (15 << 2 )))
#define PB0             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (0 << 2 )))
#define PB1             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (1 << 2 )))
#define PB2             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (2 << 2 )))
#define PB3             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (3 << 2 )))
#define PB4             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (4 << 2 )))
#define PB5             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (5 << 2 )))
#define PB6             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (6 << 2 )))
#define PB7             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (7 << 2 )))
#define PB8             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (8 << 2 )))
#define PB9             (*(uint32_t*)(myPB_DATA_BASE_ADDR + (9 << 2 )))
#define PB10            (*(uint32_t*)(myPB_DATA_BASE_ADDR + (10 << 2 )))
#define PB11            (*(uint32_t*)(myPB_DATA_BASE_ADDR + (11 << 2 )))
#define PB12            (*(uint32_t*)(myPB_DATA_BASE_ADDR + (12 << 2 )))
#define PB13            (*(uint32_t*)(myPB_DATA_BASE_ADDR + (13 << 2 )))
#define PB14            (*(uint32_t*)(myPB_DATA_BASE_ADDR + (14 << 2 )))
#define PB15            (*(uint32_t*)(myPB_DATA_BASE_ADDR + (15 << 2 )))
#define PC0             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (0 << 2 )))
#define PC1             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (1 << 2 )))
#define PC2             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (2 << 2 )))
#define PC3             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (3 << 2 )))
#define PC4             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (4 << 2 )))
#define PC5             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (5 << 2 )))
#define PC6             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (6 << 2 )))
#define PC7             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (7 << 2 )))
#define PC8             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (8 << 2 )))
#define PC9             (*(uint32_t*)(myPC_DATA_BASE_ADDR + (9 << 2 )))
#define PC10            (*(uint32_t*)(myPC_DATA_BASE_ADDR + (10 << 2 )))
#define PC11            (*(uint32_t*)(myPC_DATA_BASE_ADDR + (11 << 2 )))
#define PC12            (*(uint32_t*)(myPC_DATA_BASE_ADDR + (12 << 2 )))
#define PC13            (*(uint32_t*)(myPC_DATA_BASE_ADDR + (13 << 2 )))
#define PC14            (*(uint32_t*)(myPC_DATA_BASE_ADDR + (14 << 2 )))
#define PC15            (*(uint32_t*)(myPC_DATA_BASE_ADDR + (15 << 2 )))
#define PD0             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (0 << 2 )))
#define PD1             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (1 << 2 )))
#define PD2             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (2 << 2 )))
#define PD3             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (3 << 2 )))
#define PD4             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (4 << 2 )))
#define PD5             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (5 << 2 )))
#define PD6             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (6 << 2 )))
#define PD7             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (7 << 2 )))
#define PD8             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (8 << 2 )))
#define PD9             (*(uint32_t*)(myPD_DATA_BASE_ADDR + (9 << 2 )))
#define PD10            (*(uint32_t*)(myPD_DATA_BASE_ADDR + (10 << 2 )))
#define PD11            (*(uint32_t*)(myPD_DATA_BASE_ADDR + (11 << 2 )))
#define PD12            (*(uint32_t*)(myPD_DATA_BASE_ADDR + (12 << 2 )))
#define PD13            (*(uint32_t*)(myPD_DATA_BASE_ADDR + (13 << 2 )))
#define PD14            (*(uint32_t*)(myPD_DATA_BASE_ADDR + (14 << 2 )))
#define PD15            (*(uint32_t*)(myPD_DATA_BASE_ADDR + (15 << 2 )))
#define PE0             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (0 << 2 )))
#define PE1             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (1 << 2 )))
#define PE2             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (2 << 2 )))
#define PE3             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (3 << 2 )))
#define PE4             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (4 << 2 )))
#define PE5             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (5 << 2 )))
#define PE6             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (6 << 2 )))
#define PE7             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (7 << 2 )))
#define PE8             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (8 << 2 )))
#define PE9             (*(uint32_t*)(myPE_DATA_BASE_ADDR + (9 << 2 )))
#define PE10            (*(uint32_t*)(myPE_DATA_BASE_ADDR + (10 << 2 )))
#define PE11            (*(uint32_t*)(myPE_DATA_BASE_ADDR + (11 << 2 )))
#define PE12            (*(uint32_t*)(myPE_DATA_BASE_ADDR + (12 << 2 )))
#define PE13            (*(uint32_t*)(myPE_DATA_BASE_ADDR + (13 << 2 )))
#define PE14            (*(uint32_t*)(myPE_DATA_BASE_ADDR + (14 << 2 )))
#define PF0             (*(uint32_t*)(myPF_DATA_BASE_ADDR + (0 << 2 )))
#define PF1             (*(uint32_t*)(myPF_DATA_BASE_ADDR + (1 << 2 )))
#define PF2             (*(uint32_t*)(myPF_DATA_BASE_ADDR + (2 << 2 )))
#define PF3             (*(uint32_t*)(myPF_DATA_BASE_ADDR + (3 << 2 )))
#define PF4             (*(uint32_t*)(myPF_DATA_BASE_ADDR + (4 << 2 )))
#define PF5             (*(uint32_t*)(myPF_DATA_BASE_ADDR + (5 << 2 )))
#define PF6             (*(uint32_t*)(myPF_DATA_BASE_ADDR + (6 << 2 )))
#define PF7             (*(uint32_t*)(myPF_DATA_BASE_ADDR + (7 << 2 )))

#define myCLK_BASE_ADDR			0x40000200
#define myCLK_APBCLK0				(*(uint32_t*)(myCLK_BASE_ADDR + 0x08))
#define myTMR0_CLKEN_POS		2
#define myTMR0_CLKEN_MASK		(1 << myTMR0_CLKEN_POS)

#define myCLK_CLKSEL1				(*(uint32_t*)(myCLK_BASE_ADDR + 0x14))
#define myTMR0_CLKSEL_POS		8
#define myTMR0_CLKSEL_MASK	(7 << myTMR0_CLKSEL_POS)

#define myTMR_BASE_ADDR01		0x40050000
#define myTMR0_CTL					(*(uint32_t*)(myTMR_BASE_ADDR01 + 0x00))
#define myTMR0_CNTEN_POS		30
#define myTMR0_CNTEN_MASK		(1 << myTMR0_CNTEN_POS)
#define myTMR0_INTEN_POS		29
#define myTMR0_INTEN_MASK		(1 << myTMR0_INTEN_POS)
#define myTMR0_OPMODE_POS		27
#define myTMR0_OPMODE_MASK	(3 << myTMR0_OPMODE_POS)
#define myTMR0_PRESCL_POS		0
#define myTMR0_PRESCL_MASK	(0xFF << myTMR0_PRESCL_POS)

#define myTMR0_CMP					(*(uint32_t*)(myTMR_BASE_ADDR01 + 0x04))
#define myTMR0_TIF					(*(uint32_t*)(myTMR_BASE_ADDR01 + 0x08))
#define myTMR0_TIF_POS			0
#define myTMR0_TIF_MASK			(0x1 << myTMR0_TIF_POS)

#define myNVIC_ISER1				(*(uint32_t*)(0xE000E100))
#define myNVIC_ISER2				(*(uint32_t*)(0xE000E104))

#define myTMR0_ISER2_POS		0
#define myTMR0_ISER2_MASK		(1 << myTMR0_ISER2_POS)



#endif  /* __MYM451HEADER_H__ */
