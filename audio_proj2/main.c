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
        0x0000, 0x10b4, 0x2120, 0x30fb, 0x3fff, 0x4dea, 0x5a81, 0x658b,
        0x6ed8, 0x763f, 0x7ba1, 0x7ee5, 0x7ffd, 0x7ee5, 0x7ba1, 0x76ef,
        0x6ed8, 0x658b, 0x5a81, 0x4dea, 0x3fff, 0x30fb, 0x2120, 0x10b4,
        0x0000, 0xef4c, 0xdee0, 0xcf06, 0xc002, 0xb216, 0xa57f, 0x9a75,
        0x9128, 0x89c1, 0x845f, 0x811b, 0x8002, 0x811b, 0x845f, 0x89c1,
        0x9128, 0x9a76, 0xa57f, 0xb216, 0xc002, 0xcf06, 0xdee0, 0xef4c
    };

Int16 j, i = 0;
Int16 sample, left, right;

#define Rcv 0x08
#define Xmit 0x20

extern Int16 aic3204_mic();
extern Int16 aic3204_sin();
extern Int16 aic3204_read();

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
    I2S2_CR   = 0x8012;    // 16-bit word, Master, enable I2C

    aic3204_sin();

    /* Play Tone */
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
    }

	// Режим «с микрофона на наушники»
	aic3204_mic();

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5000; j++) {
			for (sample = 0; sample < 48; sample++) {

				/* Read Digital audio */
				while ((Rcv & I2S2_IR) == 0); // Wait for receive interrupt to be pending
				left = I2S2_W0_MSW_R; // 16 bit left channel received audio data
				right = I2S2_W1_MSW_R;// 16 bit right channel received audio data

				/* Write Digital audio */
				while ((Xmit & I2S2_IR) == 0); // Wait for receive interrupt to be pending
				I2S2_W0_MSW_W = left;  // 16 bit left channel transmit audio data
				I2S2_W1_MSW_W = right;// 16 bit right channel transmit audio data
		}
	}
}
/* Отключаем I2S */
I2S0_CR = 0x00;

c5515_GPIO_setOutput(GPIO26, 0);

SW_BREAKPOINT;
}
