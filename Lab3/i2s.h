#ifndef I2S_H_
#define I2S_H_
#include "C5515.h"
// ��������� ����������� ������

typedef struct  {
	ioreg SCTL;
	ioreg SRATE;
	ioreg TXLT0;
	ioreg TXLT1;
	ioreg TXRT0;
	ioreg TXRT1;
	ioreg INTFL;
	ioreg INTMASK;
	ioreg RXLT0;
	ioreg RXLT1;
	ioreg RXRT0;
	ioreg RXRT1;
} I2S_Regs ;

//struct I2S_Regs * I2S_RegsOvly;
typedef volatile ioport I2S_Regs * I2S_RegsOvly;

// ����������� ������ �����������
#define I2S0 ((I2S_RegsOvly) 0x2800)
#define I2S1 ((I2S_RegsOvly) 0x2900)
#define I2S2 ((I2S_RegsOvly) 0x2A00)
#define I2S3 ((I2S_RegsOvly) 0x2B00)
// ������� ���������� SCTL
#define SCTL_ENABLE BIT15 // ���������� ������
#define SCTL_MONO BIT12 // ����� ����
#define SCTL_LOOPBACK BIT11 // �������� �����
#define SCTL_FSPOL BIT10 // ���������� �������� �������������
#define SCTL_CLKPOL BIT9 // ���������� ������� �������������
#define SCTL_DATADLY BIT8 // �������� ������
#define SCTL_PACK BIT7 // �������� ������
#define SCTL_SIGN_EXT BIT6 // ���������� �����
#define SCTL_WDLNGTH 0x0034 // ����� ����� �����
#define SCTL_WDLNGTH8 0x0000 // ����� ����� 8 ���
#define SCTL_WDLNGTH12 0x0004 // ����� ����� 12 ���
#define SCTL_WDLNGTH14 0x0008 // ����� ����� 14 ���
#define SCTL_WDLNGTH16 0x0014 // ����� ����� 16 ���
#define SCTL_WDLNGTH18 0x0018 // ����� ����� 18 ���
#define SCTL_WDLNGTH20 0x0020 // ����� ����� 20 ���
#define SCTL_WDLNGTH24 0x0024 // ����� ����� 24 ����
#define SCTL_WDLNGTH32 0x0028 // ����� ����� 32 ����
#define SCTL_MODE 0x0002 // ����� ��������
#define SCTL_FRMT 0x0001 // ������ DSP
// ������� ������ ����������
#define INTFL_XMITL BIT5 // ���������� ������ �����������
#define INTFL_XMITR BIT4 // ���������� ���� �����������
#define INTFL_RCVL BIT3 // ���������� ������ ���������
#define INTFL_RCVR BIT2 // ���������� ���� ���������
#define INTFL_FERR BIT1 // ������ �������� �������������
#define INTFL_OUERR BIT0 // ������ ����������
#endif /* I2S_H_ */
