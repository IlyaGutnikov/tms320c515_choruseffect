#include "C5515.h"
// ������������� ���������������
uint16 c5515_init() {
// ������ �������� �������
	PCGCR1 &= ~PCGCR1_SYSCLK;
	PCGCR2 = 0x0000;
	return 0;
}
// ����������� ��������
void c5515_wait(uint32 delay) {
	volatile uint32 i;
	for (i = 0; i < delay; i++)
		;
}
