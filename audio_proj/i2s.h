#ifndef I2S_H_
#define I2S_H_
#include "C5515.h"
// Структура регистровой памяти

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

// Регистровая память интерфейсов
#define I2S0 ((I2S_RegsOvly) 0x2800)
#define I2S1 ((I2S_RegsOvly) 0x2900)
#define I2S2 ((I2S_RegsOvly) 0x2A00)
#define I2S3 ((I2S_RegsOvly) 0x2B00)
// Регистр управления SCTL
#define SCTL_ENABLE BIT15 // Разрешение работы
#define SCTL_MONO BIT12 // Режим моно
#define SCTL_LOOPBACK BIT11 // Обратная петля
#define SCTL_FSPOL BIT10 // Полярность кадровой синхронизации
#define SCTL_CLKPOL BIT9 // Полярность битовой синхронизации
#define SCTL_DATADLY BIT8 // Задержка данных
#define SCTL_PACK BIT7 // Упаковка данных
#define SCTL_SIGN_EXT BIT6 // Расширение знака
#define SCTL_WDLNGTH 0x0034 // Маска длины слова
#define SCTL_WDLNGTH8 0x0000 // Длина слова 8 бит
#define SCTL_WDLNGTH12 0x0004 // Длина слова 12 бит
#define SCTL_WDLNGTH14 0x0008 // Длина слова 14 бит
#define SCTL_WDLNGTH16 0x0014 // Длина слова 16 бит
#define SCTL_WDLNGTH18 0x0018 // Длина слова 18 бит
#define SCTL_WDLNGTH20 0x0020 // Длина слова 20 бит
#define SCTL_WDLNGTH24 0x0024 // Длина слова 24 бита
#define SCTL_WDLNGTH32 0x0028 // Длина слова 32 бита
#define SCTL_MODE 0x0002 // Режим ведомого
#define SCTL_FRMT 0x0001 // Формат DSP
// Регистр флагов прерываний
#define INTFL_XMITL BIT5 // Готовность стерео передатчика
#define INTFL_XMITR BIT4 // Готовность моно передатчика
#define INTFL_RCVL BIT3 // Готовность стерео приемника
#define INTFL_RCVR BIT2 // Готовность моно приемника
#define INTFL_FERR BIT1 // Ошибка кадровой синхронизации
#define INTFL_OUERR BIT0 // Ошибка передержка
#endif /* I2S_H_ */
