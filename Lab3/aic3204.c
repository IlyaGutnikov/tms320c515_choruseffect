#include "aic3204.h"
// ����������� ������
uint16 aic3204_open(void) {
// ����� ������������ ����� ������
	EBSR |= 0x0020; // ����� A20 - GPIO[26]
	GPIO_DIR1 |= BIT10; // GPIO[26] - �����
	GPIO_OUT1 |= BIT10; // GPIO[26]=1 - ����� ����� AIC3204
// ������������� ���������� ���������
	I2C_open(); // ���������� I2C
// ������������� ��������� ���������
	PCGCR1 &= ~PCGCR1_I2S2CG; // ������ ������������
	c5515_wait(100); // �������� ����������

	I2S2->SRATE = 0x15; // �������������: ������ 32, ��� 64
	I2S2->INTMASK = INTFL_XMITL // ���������� ������ �����������
	| INTFL_RCVL; // ���������� ������ ��������� (0x0028)
	I2S2->SCTL = SCTL_ENABLE | SCTL_WDLNGTH16 | SCTL_MODE;
	c5515_wait(100); // �������� ���������� �������������
	return 0;
}
// ���������� ������
uint16 aic3204_close(void) {
// ���������� ������
	aic3204_set(1, 1); // ����������� ����� ������
	GPIO_OUT1 &= ~BIT10; // ������������ �����: GPIO[26]=0
// ���������� ��������� ����������
	I2S2->SCTL &= ~SCTL_ENABLE; // ������ I2S2
	c5515_wait(100); // �������� ����������
	PCGCR1 |= PCGCR1_I2S2CG; // ����� ������������ I2S
// ���������� ���������� ���������
	I2C_close(); // ��������� I2C
	return 0;
}
// ������ �� �������� ������
uint16 aic3204_get(uint16 regnum, uint16* regval) {
// ��������� ������
	int16 retcode = 0;
	uint8 cmd[1];
// ������������ ����� I2C
	cmd[0] = regnum & 0x007F; // 7 ��� ������ ��������
// ������ �������
	retcode |= I2C_write(AIC3204_ICADDR, cmd, 1);
// �������� �����
	retcode |= I2C_read(AIC3204_ICADDR, cmd, 1);
// �������� ���������� ���������� ���������
	c5515_wait(10);
// ������� ����������
	*regval = cmd[0];
	return retcode;
}
// ������ � ������� ������
uint16 aic3204_set(uint16 regnum, uint16 regval) {
// ��������� ������
	uint8 cmd[2];
// ������������ ����� I2C
	cmd[0] = regnum & 0x007F; // 7 ��� ������ ��������
	cmd[1] = regval; // 8 ��� ������ ��������
// ������ ������� � �������
	return I2C_write(AIC3204_ICADDR, cmd, 2);
}
// ������������ ������
uint16 aic3204_config(uint16* prg, uint16 len) {
// ��������� ������
	uint16 dat;
	uint8 reg, cmd;
// ���� �� ��������� �������
	while (--len > 0) {
// ������ �������� ��������
		dat = *prg++;
// ���������� �������� ��������
		reg = dat >> 8, cmd = dat & 0xFF;
// ������������� ������
		if (reg == 0xFF)
// ��������
			c5515_wait(cmd * 10);
		else
// ������ � ������� ������
			aic3204_set(reg, cmd);
	}
	return 0;
}
// ������ ������� �������
uint16 aic3204_read(int16* left_input, int16* right_input) {
	volatile int16 dummy;
// �������� ���������� ����������
	while (!(I2S2->INTFL & INTFL_RCVR))
		dummy++;
// ������ ������� ������ ������
	*left_input = I2S2->RXLT0;
	dummy = I2S2->RXLT1;
// ������ ������� ������� ������
	*right_input = I2S2->RXRT0;
	dummy = I2S2->RXRT1;
	return 0;
}
// ������ ������� �������
uint16 aic3204_write(int16* left_output, int16* right_output) {
	volatile int16 dummy;
// �������� ���������� �����������
	while (!(I2S2->INTFL & INTFL_XMITR))
		dummy++;
// ������ ������� � ����� �����
	I2S2->TXLT0 = *left_output;
	I2S2->TXLT1 = 0;
// ������ ������� � ������ �����
	I2S2->TXRT0 = *right_output;
	I2S2->TXRT1 = 0;
	return 0;
}
