/*
 *  Copyright 2009 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

#define AIC3204_I2C_ADDR 0x18
#include "C5515.h"
#include "gpio.h"
#include "i2c.h"
#include "i2s.h"
#include "stdio.h"

/* Pre-generated sine wave data, 16-bit signed samples */
Int16 sinetable[48] = {
		0x0000, 0x10b4, 0x2120, 0x30fb, 0x3fff, 0x4dea, 0x5a81, 0x658b, 0x6ed8,
		0x763f, 0x7ba1, 0x7ee5, 0x7ffd, 0x7ee5, 0x7ba1, 0x76ef, 0x6ed8, 0x658b,
		0x5a81, 0x4dea, 0x3fff, 0x30fb, 0x2120, 0x10b4, 0x0000, 0xef4c, 0xdee0,
		0xcf06, 0xc002, 0xb216, 0xa57f, 0x9a75, 0x9128, 0x89c1, 0x845f, 0x811b,
		0x8002, 0x811b, 0x845f, 0x89c1, 0x9128, 0x9a76, 0xa57f, 0xb216, 0xc002,
		0xcf06, 0xdee0, 0xef4c };

Int16 j, i = 0;
Int16 sample, left, right;

//отсчеты после поимененого эффекта
Int16 out_left = 0, out_right = 0;

Int16 array_size = 4800;

Int16 arrayLeft_delay[4800] = {0};
Int16 arrayRight_delay[4800] = {0};

Int16 index_delay = 0; //вычисляемая задержка
Int16 accumulator_left = 0; //аккумулятор для левого сигнала
Int16 accumulator_right = 0; //аккумулятор для правого сигнала

#define Rcv 0x08
#define Xmit 0x20

extern Int16 aic3204_mic();
extern Int16 aic3204_stereo_in1();
extern Int16 aic3204_sin();

void chorus_effect(Int16 left_ch, Int16 right_ch, Int16 voices, Int16 chorus_width) {

	Int16 v = 0; //счетчик голосов

	arrayLeft_delay[sample] = left_ch; //буфер задержки с отсчетами левого канала
	arrayRight_delay[sample] = right_ch; //буфер задержки с отсчетами правого канала

	out_left = left_ch;
	out_right = right_ch;

	for (v = 1; v < voices; v++) {

		//обнуляем аккумуляторы
		accumulator_left = 0;
		accumulator_right = 0;

		//находим номер отсчета в буфере задержки
		index_delay = (array_size + sample - (chorus_width*v)) % array_size;

		//суммируем отсчеты
		accumulator_left += arrayLeft_delay[index_delay];
		accumulator_right += arrayRight_delay[index_delay];

	}

	//суммируем с текущим значением отсчета
	out_left += accumulator_left;
	out_right += accumulator_right;

	//делим на количество голосов
	//для того чтобы не было
	//перегрузки звука
	out_left = out_left / voices;
	out_right = out_right / voices;

}


void main(void) {
	/* Initialize BSL */
	c5515_init();

	/* Configure Parallel Port */
	SYS_EXBUSSEL &= ~0x7000;   //
	SYS_EXBUSSEL |= 0x1000;// Configure Parallel Port for I2S2
	/* Configure Serial Port */
	SYS_EXBUSSEL &= ~0x0C00;   //
	SYS_EXBUSSEL |= 0x0400;// Serial Port mode 1 (I2S1 and GP[11:10]).
	c5515_GPIO_init();
	c5515_GPIO_setDirection(GPIO10, GPIO_OUT);
	c5515_GPIO_setOutput(GPIO10, 1);    // Take AIC3201 chip out of reset
	I2C_init();                    // Initialize I2C

	/* I2S settings */
	I2S2_SRGR = 0x0015;
	I2S2_ICMR = 0x0028;    // Enable interrupts
	I2S2_CR = 0x8012;// 16-bit word, Master, enable I2C

	/*(  aic3204_sin();


	 for ( i = 0 ; i < 5 ; i++ )
	 {
	 for ( j = 0 ; j < 1000 ; j++ )
	 {
	 for ( sample = 0 ; sample < 48 ; sample++ )
	 {
	 while((Xmit & I2S2_IR) == 0);  // Wait for interrupt
	 I2S2_W0_MSW_W = (sinetable[sample]) ;
	 I2S2_W0_LSW_W = 0;
	 I2S2_W1_MSW_W = (sinetable[sample]) ;
	 I2S2_W1_LSW_W = 0;
	 }
	 }
	 }*/

	// Режим «с микрофона на наушники»
	aic3204_stereo_in1();

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 1000; j++) {
			for (sample = 0; sample < array_size; sample++) {

				/* Read Digital audio */
				while ((Rcv & I2S2_IR) == 0); // Wait for receive interrupt to be pending
				left = I2S2_W0_MSW_R; // 16 bit left channel received audio data
				right = I2S2_W1_MSW_R;// 16 bit right channel received audio data

				chorus_effect(left, right, 4, 440);


				/* Write Digital audio */
				while ((Xmit & I2S2_IR) == 0); // Wait for receive interrupt to be pending
				I2S2_W0_MSW_W = out_left;  // 16 bit left channel transmit audio data
				I2S2_W1_MSW_W = out_right;// 16 bit right channel transmit audio data

					//I2S2_W0_MSW_W = left;  // 16 bit left channel transmit audio data
					//I2S2_W1_MSW_W = right;// 16 bit right channel transmit audio data

		}
	}
}
/* Отключаем I2S */
I2S0_CR = 0x00;

c5515_GPIO_setOutput(GPIO26, 0);

SW_BREAKPOINT;
}

