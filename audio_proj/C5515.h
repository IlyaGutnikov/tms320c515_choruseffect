#ifndef C5515_H_
#define C5515_H_
// Простые типы данных
#define uint32 unsigned long
#define uint16 unsigned short
#define uint8 unsigned char
#define int32 int
#define int16 short
#define int8 char
#define ioreg volatile uint16
// Маски бит
#define BIT0 (uint16)0x0001
#define BIT1 (uint16)0x0002
#define BIT2 (uint16)0x0004
#define BIT3 (uint16)0x0008
#define BIT4 (uint16)0x0010
#define BIT5 (uint16)0x0020
#define BIT6 (uint16)0x0040
#define BIT7 (uint16)0x0080
#define BIT8 (uint16)0x0100
#define BIT9 (uint16)0x0200
#define BIT10 (uint16)0x0400
#define BIT11 (uint16)0x0800
#define BIT12 (uint16)0x1000
#define BIT13 (uint16)0x2000
#define BIT14 (uint16)0x4000
#define BIT15 (uint16)0x8000
// Регистры выбора внешней шины (внешних выводов)
#define EBSR *(ioreg*)(0x1c00) // Содержимое регистра
#define EBSR_PPMODE 0x7000 // Маска параллельного порта
#define EBSR_PPMODE0 0x0000 // 21:LCD
#define EBSR_PPMODE1 0x1000 // 7:SPI,GP[29-27,20-18],4:UART,4:I2S2
#define EBSR_PPMODE2 0x2000 // 8:LCD,8:GP[31-27,20-18]
#define EBSR_PPMODE3 0x3000 // 8:LCD,4:SPI,4:I2S3
#define EBSR_PPMODE4 0x4000 // 8:LCD,4:I2S2,4:UART
#define EBSR_PPMODE5 0x5000 // 8:LCD,4:SPI,4:UART
#define EBSR_PPMODE6 0x6000 // 7:SPI,4:I2S2,4:I2S3,6:GP[29-27,20-18]
#define EBSR_PPMODE7 0x7000 // Резерв
#define EBSR_SP1MODE 0x0C00 // Маска последовательного порта 1
#define EBSR_SP1MODE0 0x0000 // GP[11:10]
#define EBSR_SP1MODE1 0x0400 // 6:MMC/SD1,4:I2S1,GP[11-10]
#define EBSR_SP0MODE 0x0300 // Маска последовательного порта 0
#define EBSR_SP1MODE0 0x0000 // GP[5-0]
#define EBSR_SP1MODE1 0x0400 // 6:MMC/SD0,4:I2S0,GP[5-4]
#define EBSR_A20MODE 0x0020 // GPIO[26]\EM_A[20]
#define EBSR_A19MODE 0x0010 // GPIO[25]\EM_A[19]
#define EBSR_A18MODE 0x0008 // GPIO[24]\EM_A[18]
#define EBSR_A17MODE 0x0004 // GPIO[23]\EM_A[17]
#define EBSR_A16MODE 0x0002 // GPIO[22]\EM_A[16]
#define EBSR_A15MODE 0x0001 // GPIO[21]\EM_A[15]
// Регистры конфигурации тактового питания устройств
#define PCGCR1 *(ioreg*)(0x1C02)
#define PCGCR2 *(ioreg*)(0x1C03)
#define PCGCR1_SYSCLK BIT15 // Флаг системного тактирования
#define PCGCR1_I2S2CG BIT14 // Флаг звукового интерфейса 2
#define PCGCR1_I2S1CG BIT9 // Флаг звукового интерфейса 1
#define PCGCR1_I2S0CG BIT8 // Флаг звукового интерфейса 0
#define PCGCR1_I2CCG BIT6 // Флаг приборного интерфейса
#define PCGCR1_I2S3CG BIT1 // Флаг звукового интерфейса 3
// Регистры входов-выходов общего назначения
#define GPIO_DIR0 *(ioreg*)(0x1c06)
#define GPIO_DIR1 *(ioreg*)(0x1c07)
#define GPIO_IN0 *(ioreg*)(0x1c08)
#define GPIO_IN1 *(ioreg*)(0x1c09)
#define GPIO_OUT0 *(ioreg*)(0x1c0a)
#define GPIO_OUT1 *(ioreg*)(0x1c0b)
// Инициализация микропроцессора
uint16 c5515_init();
// Программная задержка
void c5515_wait( uint32 delay);
#endif
