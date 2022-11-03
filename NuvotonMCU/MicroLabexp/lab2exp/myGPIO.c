#include "myGPIO.h"

/**
* @example GPIO_Mode_Set(&PE_MODE, 2, GPIO_INPUT_MODE);
* @example GPIO_Mode_Set(&PB_MODE, 2, GPIO_OUTPUT_MODE);
**/
void GPIO_Mode_Set(uint32_t *ptrPortMode, uint8_t Pin, uint8_t Mode){
	
	uint32_t PinBitPos = Pin << 1;						//pos of pin is 2*n
	uint32_t PinBitMask = 0x3 << PinBitPos;		//two bit for a pin
	uint32_t PinBitMode = Mode << PinBitPos;
	
	*ptrPortMode &= ~PinBitMask;
	*ptrPortMode |= PinBitMode;
	
}


