#include "aic3204.h"

// ����� ����� � ���������
void main(void) {

	// ������� ��������� � ������� Q1.15
	int16 sinus[48] = { 0x0000, 0x10b4, 0x2120, 0x30fb, 0x3fff, 0x4dea, 0x5a81,
			0x658b, 0x6ed8, 0x763f, 0x7ba1, 0x7ee5, 0x7ffd, 0x7ee5, 0x7ba1, 0x76ef,
			0x6ed8, 0x658b, 0x5a81, 0x4dea, 0x3fff, 0x30fb, 0x2120, 0x10b4, 0x0000,
			0xef4c, 0xdee0, 0xcf06, 0xc002, 0xb216, 0xa57f, 0x9a75, 0x9128, 0x89c1,
			0x845f, 0x811b, 0x8002, 0x811b, 0x845f, 0x89c1, 0x9128, 0x9a76, 0xa57f,
			0xb216, 0xc002, 0xcf06, 0xdee0, 0xef4c };

	int i, j, k;
	int16 lft, rgh;
// ������������� ���������������
	c5515_init();
// ������������ ������������� ����� (0x1000)
	EBSR &= ~EBSR_PPMODE; // ������� ������ ������������� �����
	EBSR |= EBSR_PPMODE1; // LCD, I2S2, UART
// ������������ ����������������� ����� 1 (0x0400)
	EBSR &= ~EBSR_SP1MODE; // ������� ������ ����������������� ����� 1
	EBSR |= EBSR_PPMODE1; // MMC/SD1, I2S1, GP[11-10]
// ��������� ������
	aic3204_open();
// �������� ������ ����� � �������� 1 ��� �� ��������
	aic3204_config(Sin_Headphone, sizeof Sin_Headphone);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 1000; j++) {
			for (k = 0; k < 48; k++) {
				while (!(I2S2->INTFL & INTFL_XMITR))
					;
// ������ ������� � ����� �����
				I2S2->TXLT0 = sinus[k];
				I2S2->TXLT1 = 0;
// ������ ������� � ������ �����
				I2S2->TXRT0 = sinus[k];
				I2S2->TXRT1 = 0;
			}
		}
	}
// ����� �� ��������� �� ��������
//	aic3204_config(Mic_Headphone, sizeof Mic_Headphone);
//	for (i = 0; i < 500000; i++) {
//		aic3204_read(&lft, &rgh);
//		aic3204_write(&lft, &rgh);
//	}
// ���������� ������
	aic3204_close();
}
