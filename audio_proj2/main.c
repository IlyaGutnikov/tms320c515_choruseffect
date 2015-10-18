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

Int16 j, i = 0;
Int16 sample, data1, data2, data3, data4;

#define Rcv 0x08
#define Xmit 0x20

extern Int16 aic3204_mic();

void main(void) {
	/* Initialize BSL */
	EVM5515_init();

	/* Configure Parallel Port */
	SYS_EXBUSSEL &= ~0x7000;   //
	SYS_EXBUSSEL |= 0x1000;// Configure Parallel Port for I2S2
	/* Configure Serial Port */
	SYS_EXBUSSEL &= ~0x0C00;   //
	SYS_EXBUSSEL |= 0x0400;// Serial Port mode 1 (I2S1 and GP[11:10]).
	EVM5515_GPIO_init();
	EVM5515_GPIO_setDirection(GPIO10, GPIO_OUT);
	EVM5515_GPIO_setOutput(GPIO10, 1);    // Take AIC3201 chip out of reset
	I2C_init();                    // Initialize I2C

	// Режим «с микрофона на наушники»
	aic3204_mic();

	/* I2S settings */
	I2S2_SRGR = 0x0015;
	I2S2_ICMR = 0x0028;    // Enable interrupts
	I2S2_CR = 0x8012;// 16-bit word, Master, enable I2C

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5000; j++) {
			for (sample = 0; sample < 48; sample++) {

				/* Read Digital audio */
				while ((Rcv & I2S2_IR) == 0); // Wait for receive interrupt to be pending
				data3 = I2S2_W0_MSW_R; // 16 bit left channel received audio data
				data4 = I2S2_W1_MSW_R;// 16 bit right channel received audio data

				/* Write Digital audio */
				while ((Xmit & I2S2_IR) == 0); // Wait for receive interrupt to be pending
			I2S2_W0_MSW_W = data3;  // 16 bit left channel transmit audio data
			I2S2_W1_MSW_W = data4;// 16 bit right channel transmit audio data
		}
	}
}
/* Disble I2S */
I2S0_CR = 0x00;

EVM5515_GPIO_setOutput(GPIO26, 0);

SW_BREAKPOINT;
}
