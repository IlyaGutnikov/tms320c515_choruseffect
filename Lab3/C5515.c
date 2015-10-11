#include "C5515.h"
// Инициализация микропроцессора
uint16 c5515_init() {
// Подать тактовое питание
	PCGCR1 &= ~PCGCR1_SYSCLK;
	PCGCR2 = 0x0000;
	return 0;
}
// Программная задержка
void c5515_wait(uint32 delay) {
	volatile uint32 i;
	for (i = 0; i < delay; i++)
		;
}
