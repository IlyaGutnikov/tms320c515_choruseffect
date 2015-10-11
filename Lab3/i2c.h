#ifndef I2C_H_
#define I2C_H_
#include "C5515.h"
// Адреса регистров
#define ICOAR *(ioreg*)(0x1A00) // Регистр собственного адреса
#define ICIMR *(ioreg*)(0x1A04) // Регистр маски прерываний
#define ICSTR *(ioreg*)(0x1A08) // Регистр статуса
#define ICCLKL *(ioreg*)(0x1A0C) // Регистр делителя частоты младший
#define ICCLKH *(ioreg*)(0x1A10) // Регистр делителя частоты старший
#define ICCNT *(ioreg*)(0x1A14) // Счетчик данных
#define ICDRR *(ioreg*)(0x1A18) // Регистр принятых данных
#define ICSAR *(ioreg*)(0x1A1C) // Регистр подчиненного адреса
#define ICDXR *(ioreg*)(0x1A20) // Регистр передаваемых данных
#define ICMDR *(ioreg*)(0x1A24) // Регистр режима
#define ICIVR *(ioreg*)(0x1A28) // Регистр вертора прерываний
#define ICEMDR *(ioreg*)(0x1A2C) // Регистр расширенного режима
#define ICPSC *(ioreg*)(0x1A30) // Регистр прескалера
// Биты регистра режима
#define ICMDR_NACKMOD BIT15 // Без подтверждения
#define ICMDR_FREE BIT14 // Работа с эмулятором
#define ICMDR_STT BIT13 // Генерация START
#define ICMDR_STP BIT11 // Генерация STOP
#define ICMDR_MST BIT10 // Ведущиее устройство
#define ICMDR_TRX BIT9 // Передатчик
#define ICMDR_XA BIT8 // Расширенный адрес
#define ICMDR_RM BIT7 // Режим повторения
#define ICMDR_DLB BIT6 // Цифровая петля
#define ICMDR_IRS BIT5 // Разрешение работы
#define ICMDR_STB BIT4 // Удлиненный старт
#define ICMDR_FDF BIT3 // Свободные данные
#define ICMDR_BC (BIT2|BIT1|BIT0) // Маска числа бит
// Биты регистра состояния
#define ICSTR_SDIR BIT14 // Ведомое направление
#define ICSTR_NACKSNT BIT13 // Отправлено подтверждение
#define ICSTR_BB BIT10 // Занятость шины
#define ICSTR_RSFULL BIT9 // Переполнение приемника
#define ICSTR_XSMT BIT8 // Пустота передатчика
#define ICSTR_AAS BIT7 // Получен собственный адрес
#define ICSTR_ASD0 BIT6 // Получен нулевой адрес
#define ICSTR_SCD BIT5 // Обнаружен STOP
#define ICSTR_ICXRDY BIT4 // Готовность передатчика
#define ICSTR_ICRRDY BIT3 // Готовность приемника
#define ICSTR_ARDY BIT2 // Готовность доступа
#define ICSTR_MACK BIT1 // Нет подтверждения
#define ICSTR_AL BIT0 // Потеря арбитража
#define MDR_STT                 0x2000
#define MDR_TRX                 0x0200
#define MDR_MST                 0x0400
#define MDR_IRS                 0x0020
#define MDR_FREE                0x4000
#define STR_XRDY                0x0010
#define STR_RRDY                0x0008
#define MDR_STP                 0x0800
// Прототипы функций
uint16 I2C_open();
uint16 I2C_close();
uint16 I2C_reset();
uint16 I2C_read(uint16 i2c_addr, uint8* data, uint16 len);
uint16 I2C_write(uint16 i2c_addr, uint8* data, uint16 len);
#endif /* I2C_H_ */
