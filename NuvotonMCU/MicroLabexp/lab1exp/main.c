#include "M451Series.h"

void GPIO_initial(void);

int main()
{
	GPIO_initial();
	while (1)

	{
		int BT = (~PA8 | ~PB6 | ~PB7);
			  PA9 = (PA8 == 0 & PE2 == 0) ? 0 : 1;
		    PB1 = (PB6 == 0 & PE2 == 0) ? 0 : 1;
		    PC7 = (PB7 == 0 & PE2 == 0) ? 0 : 1;
			PB2 = (PE2 == 0 && ~BT) ? 0 : 1;
			PB3 = (PA8 == 0 && PE2&&PB6&&PB7) ? 0 : 1;
			PC3 = (PB6 == 0 && PE2&&PA6&&PB7) ? 0 : 1;
			PC2 = (PB7 == 0 && PE2&&PA8&&PB6) ? 0 : 1;
	}
}

void GPIO_initial(void)
{
	PE_MODE &= ~(0x3 << 4);
	PE_MODE |= (0x0 << 4);
	PB_MODE &= ~(0x3 << 4);
	PB_MODE |= (0x1 << 4);
	PA_MODE &= ~(0x3 << 16);
	PA_MODE |= (0x0 << 16);
	PB_MODE &= ~(0x3 << 12);
	PB_MODE |= (0x0 << 12);
	PB_MODE &= ~(0x3 << 14);
	PB_MODE |= (0x0 << 14);
	PB_MODE &= ~(0x3 << 6);
	PB_MODE |= (0x1 << 6);
	PC_MODE &= ~(0x3 << 6);
	PC_MODE |= (0x1 << 6);
	PC_MODE &= ~(0x3 << 4);
	PC_MODE |= (0x1 << 4);
	PA_MODE &= ~(0x3 << 18);
	PA_MODE |= (0x1 << 18);
	PB_MODE &= ~(0x3 << 2);
	PB_MODE |= (0x1 << 2);
	PC_MODE &= ~(0x3 << 14);
	PC_MODE |= (0x1 << 14);

}
