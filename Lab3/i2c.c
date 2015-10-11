#include "i2c.h"

unsigned long wait1 = 100;
// Глобальные данные
static int32 i2c_timeout = 0x7fff; // Таймаут
// Подключение I2C
uint16 I2C_open() {
	PCGCR1 &= ~PCGCR1_I2CCG; // Тактирование приборного интерфейса
	c5515_wait(100); // Ожидание завершения
	ICMDR = ICMDR_MST; // Режим ведущего и состояние сброса
	ICPSC = 15; // Длитель прескалера для 100 MГц
	ICCLKL = 25; // Делитель частоты 1 100 кГц
	ICCLKH = 25; // Делитель частоты 2 100 кГц
	ICMDR = ICMDR_MST // Ведущее устройство, 7-бит адреса
	| ICMDR_IRS; // Разрешение работы, 8 бит в посылке
	return 0;
}
// Отключение I2C
uint16 I2C_close() {
	ICMDR = 0; // Сброс и очистка I2C
	c5515_wait(100); // Ожидание завершения
	PCGCR1 |= PCGCR1_I2CCG; // Снять тактирование
	return 0;
}
// Сброс I2C
uint16 I2C_reset() {
	I2C_close();
	I2C_open();
	return 0;
}
// Передача пакета данных
uint16 I2C_write(uint16 i2c_addr, uint8* data, uint16 len) {
// Локальные данные
	int32 timeout, i;
// Инициализация передачи
	ICIVR = 0; // Запрет прерываний от I2C
	ICCNT = len; // Задание длины данных в посылках
	ICSAR = i2c_addr; // Задать адрес ведомого
	ICMDR = ICMDR_STT // Генерация состояния START
	| ICMDR_TRX // Передатчик
			| ICMDR_MST // Ведущее устройство
			| ICMDR_IRS // Разрешить работу
			| ICMDR_FREE; // Работа совместно с эмулятором

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
	ICMDR |= ICMDR_STP; // Генерация STOP
	c5515_wait(8000); // Перерыв в линии
	return 0;
}
// Прием пакета данных
uint16 I2C_read(uint16 i2c_addr, uint8* data, uint16 len) {
// Локальные данные
	int32 timeout, i;
// Инициализация передачи
	ICCNT = len; // Задание длины данных в посылках
	ICSAR = i2c_addr; // Задать адрес ведомого
	ICMDR = ICMDR_STT // Set for Master Read
	| ICMDR_MST // Ведущее устройство
			| ICMDR_IRS // Разрешить работу
			| ICMDR_FREE; // Работа совместно с эмулятором

	c5515_wait(10); // Задержка перед приемом
// Прием данных
	for (i = 0; i < len; i++) {
		timeout = i2c_timeout;
// Ожидание приема данных
		do
			if (timeout-- < 0) {
				I2C_reset();
				return 1;
			} while ((ICSTR & STR_RRDY) == 0);
		data[i] = ICDRR; // Получить данные
	}
	ICMDR |= ICMDR_STP; // Генерация STOP
	c5515_wait(80); // Перерыв в линии
	return 0;
}
