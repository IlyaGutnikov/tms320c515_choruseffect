#include "i2c.h"

unsigned long wait1 = 100;
// ���������� ������
static int32 i2c_timeout = 0x7fff; // �������
// ����������� I2C
uint16 I2C_open() {
	PCGCR1 &= ~PCGCR1_I2CCG; // ������������ ���������� ����������
	c5515_wait(100); // �������� ����������
	ICMDR = ICMDR_MST; // ����� �������� � ��������� ������
	ICPSC = 15; // ������� ���������� ��� 100 M��
	ICCLKL = 25; // �������� ������� 1 100 ���
	ICCLKH = 25; // �������� ������� 2 100 ���
	ICMDR = ICMDR_MST // ������� ����������, 7-��� ������
	| ICMDR_IRS; // ���������� ������, 8 ��� � �������
	return 0;
}
// ���������� I2C
uint16 I2C_close() {
	ICMDR = 0; // ����� � ������� I2C
	c5515_wait(100); // �������� ����������
	PCGCR1 |= PCGCR1_I2CCG; // ����� ������������
	return 0;
}
// ����� I2C
uint16 I2C_reset() {
	I2C_close();
	I2C_open();
	return 0;
}
// �������� ������ ������
uint16 I2C_write(uint16 i2c_addr, uint8* data, uint16 len) {
// ��������� ������
	int32 timeout, i;
// ������������� ��������
	ICIVR = 0; // ������ ���������� �� I2C
	ICCNT = len; // ������� ����� ������ � ��������
	ICSAR = i2c_addr; // ������ ����� ��������
	ICMDR = ICMDR_STT // ��������� ��������� START
	| ICMDR_TRX // ����������
			| ICMDR_MST // ������� ����������
			| ICMDR_IRS // ��������� ������
			| ICMDR_FREE; // ������ ��������� � ����������

	c5515_wait(100);

	for (i = 0; i < len; i++) {
		ICDXR = data[i];
		timeout = i2c_timeout;
		do
			if (timeout-- < 0) {
				I2C_reset();
				return 1;
			} while ((ICSTR & ICSTR_ICXRDY) == 0);
	}
	ICMDR |= ICMDR_STP; // ��������� STOP
	c5515_wait(8000); // ������� � �����
	return 0;
}
// ����� ������ ������
uint16 I2C_read(uint16 i2c_addr, uint8* data, uint16 len) {
// ��������� ������
	int32 timeout, i;
// ������������� ��������
	ICCNT = len; // ������� ����� ������ � ��������
	ICSAR = i2c_addr; // ������ ����� ��������
	ICMDR = ICMDR_STT // Set for Master Read
	| ICMDR_MST // ������� ����������
			| ICMDR_IRS // ��������� ������
			| ICMDR_FREE; // ������ ��������� � ����������

	c5515_wait(10); // �������� ����� �������
// ����� ������
	for (i = 0; i < len; i++) {
		timeout = i2c_timeout;
// �������� ������ ������
		do
			if (timeout-- < 0) {
				I2C_reset();
				return 1;
			} while ((ICSTR & STR_RRDY) == 0);
		data[i] = ICDRR; // �������� ������
	}
	ICMDR |= ICMDR_STP; // ��������� STOP
	c5515_wait(80); // ������� � �����
	return 0;
}
