#ifndef I2C_H_
#define I2C_H_
#include "C5515.h"
// ������ ���������
#define ICOAR *(ioreg*)(0x1A00) // ������� ������������ ������
#define ICIMR *(ioreg*)(0x1A04) // ������� ����� ����������
#define ICSTR *(ioreg*)(0x1A08) // ������� �������
#define ICCLKL *(ioreg*)(0x1A0C) // ������� �������� ������� �������
#define ICCLKH *(ioreg*)(0x1A10) // ������� �������� ������� �������
#define ICCNT *(ioreg*)(0x1A14) // ������� ������
#define ICDRR *(ioreg*)(0x1A18) // ������� �������� ������
#define ICSAR *(ioreg*)(0x1A1C) // ������� ������������ ������
#define ICDXR *(ioreg*)(0x1A20) // ������� ������������ ������
#define ICMDR *(ioreg*)(0x1A24) // ������� ������
#define ICIVR *(ioreg*)(0x1A28) // ������� ������� ����������
#define ICEMDR *(ioreg*)(0x1A2C) // ������� ������������ ������
#define ICPSC *(ioreg*)(0x1A30) // ������� ����������
// ���� �������� ������
#define ICMDR_NACKMOD BIT15 // ��� �������������
#define ICMDR_FREE BIT14 // ������ � ����������
#define ICMDR_STT BIT13 // ��������� START
#define ICMDR_STP BIT11 // ��������� STOP
#define ICMDR_MST BIT10 // �������� ����������
#define ICMDR_TRX BIT9 // ����������
#define ICMDR_XA BIT8 // ����������� �����
#define ICMDR_RM BIT7 // ����� ����������
#define ICMDR_DLB BIT6 // �������� �����
#define ICMDR_IRS BIT5 // ���������� ������
#define ICMDR_STB BIT4 // ���������� �����
#define ICMDR_FDF BIT3 // ��������� ������
#define ICMDR_BC (BIT2|BIT1|BIT0) // ����� ����� ���
// ���� �������� ���������
#define ICSTR_SDIR BIT14 // ������� �����������
#define ICSTR_NACKSNT BIT13 // ���������� �������������
#define ICSTR_BB BIT10 // ��������� ����
#define ICSTR_RSFULL BIT9 // ������������ ���������
#define ICSTR_XSMT BIT8 // ������� �����������
#define ICSTR_AAS BIT7 // ������� ����������� �����
#define ICSTR_ASD0 BIT6 // ������� ������� �����
#define ICSTR_SCD BIT5 // ��������� STOP
#define ICSTR_ICXRDY BIT4 // ���������� �����������
#define ICSTR_ICRRDY BIT3 // ���������� ���������
#define ICSTR_ARDY BIT2 // ���������� �������
#define ICSTR_MACK BIT1 // ��� �������������
#define ICSTR_AL BIT0 // ������ ���������
#define MDR_STT                 0x2000
#define MDR_TRX                 0x0200
#define MDR_MST                 0x0400
#define MDR_IRS                 0x0020
#define MDR_FREE                0x4000
#define STR_XRDY                0x0010
#define STR_RRDY                0x0008
#define MDR_STP                 0x0800
// ��������� �������
uint16 I2C_open();
uint16 I2C_close();
uint16 I2C_reset();
uint16 I2C_read(uint16 i2c_addr, uint8* data, uint16 len);
uint16 I2C_write(uint16 i2c_addr, uint8* data, uint16 len);
#endif /* I2C_H_ */
