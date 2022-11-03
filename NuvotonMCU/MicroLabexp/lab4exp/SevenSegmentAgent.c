#include "SevenSegmentAgent.h"

uint8_t _7Seg_OutputBuf[2];
uint8_t BufSel;

const uint8_t _7SegPatTable[] = { 0xC0,      //7-Segment shows 0
																  0xF9,      //7-Segment shows 1
																  0xA4,      //7-Segment shows 2
															    0xB0,      //7-Segment shows 3
																  0x99,      //7-Segment shows 4
																  0x92,      //7-Segment shows 5
																  0x82,      //7-Segment shows 6
																  0xD8,      //7-Segment shows 7
																  0x80,      //7-Segment shows 8
																  0x98,      //7-Segment shows 9
                                  0xFF
};    

void _7Seg_Initial(void){
	GPIO_SetMode(PB, BIT11 | BIT12 | BIT13 | BIT14 | BIT15 | BIT5, GPIO_MODE_OUTPUT);
	GPIO_SetMode(PD, BIT11, GPIO_MODE_OUTPUT);
	GPIO_SetMode(PF, BIT2 , GPIO_MODE_OUTPUT);
	     
	GPIO_SetMode(PD, BIT8 , GPIO_MODE_OUTPUT);
	GPIO_SetMode(PC, BIT8 , GPIO_MODE_OUTPUT);
	
	BufSel = 0;
	_7Seg_OutputBuf[0] = 0xFF;
	_7Seg_OutputBuf[1] = 0xFF;
	
}

void _7Seg_Switch(void){
	BufSel ^= 1;
}

void _7Seg_Output(void){
	uint8_t OutputNumber;
	uint8_t OutputData;
	
	OutputNumber = BufSel ? _7Seg_OutputBuf[1] : _7Seg_OutputBuf[0];
	
	if(OutputNumber >= 10)
		OutputNumber = 10;
		
	OutputData = _7SegPatTable[OutputNumber];
	
	SEG0_EN = 0;
	SEG1_EN = 0;
	
	SEG_A = (OutputData & (1 << 0)) ? 1 : 0;
	SEG_B = (OutputData & (1 << 1)) ? 1 : 0;
	SEG_C = (OutputData & (1 << 2)) ? 1 : 0;
	SEG_D = (OutputData & (1 << 3)) ? 1 : 0;
	SEG_E = (OutputData & (1 << 4)) ? 1 : 0;
	SEG_F = (OutputData & (1 << 5)) ? 1 : 0;
	SEG_G = (OutputData & (1 << 6)) ? 1 : 0;
	SEG_H = (OutputData & (1 << 7)) ? 1 : 0;
	
	SEG0_EN = BufSel ? 1 : 0;
	SEG1_EN = BufSel ? 0 : 1;
	
}


void _7Seg_Task(void){
	static uint32_t _7SegOldCount = 0;
	if((uint32_t)(timecount - _7SegOldCount) > SWITCH_DELAY){
		_7Seg_Output();
		_7Seg_Switch();
		_7SegOldCount = timecount;
	}
}

void _7Seg_WriteBuf(uint8_t DataH, uint8_t DataL){
	_7Seg_OutputBuf[0] = DataL;
	_7Seg_OutputBuf[1] = DataH;
}


