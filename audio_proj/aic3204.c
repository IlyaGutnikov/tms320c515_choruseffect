#include "aic3204.h"
// Подключение кодека
uint16 aic3204_open(void) {
// Снять аппаратурный сброс кодека
	EBSR |= 0x0020; // Вывод A20 - GPIO[26]
	GPIO_DIR1 |= BIT10; // GPIO[26] - выход
	GPIO_OUT1 |= BIT10; // GPIO[26]=1 - снять сброс AIC3204
// Инициализация приборного интерфеса
	I2C_open(); // Подключить I2C
// Инициализация звукового интерфеса
	PCGCR1 &= ~PCGCR1_I2S2CG; // Подать тактирование
	c5515_wait(100); // Ожидание завершения

	I2S2->SRATE = 0x15; // Синхронизация: кадров 32, бит 64
	I2S2->INTMASK = INTFL_XMITL // Готовность стерео передатчика
	| INTFL_RCVL; // Готовность стерео приемника (0x0028)
	I2S2->SCTL = SCTL_ENABLE | SCTL_WDLNGTH16 | SCTL_MODE;
	c5515_wait(100); // Ожидание завершения инициализации
	return 0;
}
// Отключение кодека
uint16 aic3204_close(void) {
// Отключение кодека
	aic3204_set(1, 1); // Программный сброс кодека
	GPIO_OUT1 &= ~BIT10; // Аппаратуреый сброс: GPIO[26]=0
// Отключение звукового интерфейса
	I2S2->SCTL &= ~SCTL_ENABLE; // Запрет I2S2
	c5515_wait(100); // Ожидание завершения
	PCGCR1 |= PCGCR1_I2S2CG; // Снять тактирование I2S
// Отключение приборного интерфеса
	I2C_close(); // Отключить I2C
	return 0;
}
// Чтение из регистра кодека
uint16 aic3204_get(uint16 regnum, uint16* regval) {
// Локальные данные
	int16 retcode = 0;
	uint8 cmd[1];
// Сформировать пакет I2C
	cmd[0] = regnum & 0x007F; // 7 бит адреса регистра
// Выдать команду
	retcode |= I2C_write(AIC3204_ICADDR, cmd, 1);
// Получить ответ
	retcode |= I2C_read(AIC3204_ICADDR, cmd, 1);
// Ожидание завершения переходных процессов
	c5515_wait(10);
// Возврат результата
	*regval = cmd[0];
	return retcode;
}
// Запись в регистр кодека
uint16 aic3204_set(uint16 regnum, uint16 regval) {
// Локальные данные
	uint8 cmd[2];
// Сформировать пакет I2C
	cmd[0] = regnum & 0x007F; // 7 бит адреса регистра
	cmd[1] = regval; // 8 бит данных регистра
// Выдать команду и возврат
	return I2C_write(AIC3204_ICADDR, cmd, 2);
}
// Конфигурация кодека
uint16 aic3204_config(uint16* prg, uint16 len) {
// Локальные данные
	uint16 dat;
	uint8 reg, cmd;
// Цикл по элементам таблицы
	while (--len > 0) {
// Чтение текущего элемента
		dat = *prg++;
// Распаковка текущего элемента
		reg = dat >> 8, cmd = dat & 0xFF;
// Интерпретация данных
		if (reg == 0xFF)
// Ожидание
			c5515_wait(cmd * 10);
		else
// Запись в регистр кодека
			aic3204_set(reg, cmd);
	}
	return 0;
}
// Чтение отсчета сигнала
uint16 aic3204_read(int16* left_input, int16* right_input) {
	volatile int16 dummy;
// Ожидание готовности примемника
	while (!(I2S2->INTFL & INTFL_RCVR))
		dummy++;
// Чтение отсчета левого канала
	*left_input = I2S2->RXLT0;
	dummy = I2S2->RXLT1;
// Чтение отсчета правого канала
	*right_input = I2S2->RXRT0;
	dummy = I2S2->RXRT1;
	return 0;
}
// Запись отсчета сигнала
uint16 aic3204_write(int16* left_output, int16* right_output) {
	volatile int16 dummy;
// Ожидание готовности передатчика
	while (!(I2S2->INTFL & INTFL_XMITR))
		dummy++;
// Запись отсчета в левый канал
	I2S2->TXLT0 = *left_output;
	I2S2->TXLT1 = 0;
// Запись отсчета в правый канал
	I2S2->TXRT0 = *right_output;
	I2S2->TXRT1 = 0;
	return 0;
}
