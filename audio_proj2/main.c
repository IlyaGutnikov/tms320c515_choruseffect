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

/* Pre-generated sine wave data, 16-bit signed samples */Int16 sinetable[48] = {
		0x0000, 0x10b4, 0x2120, 0x30fb, 0x3fff, 0x4dea, 0x5a81, 0x658b, 0x6ed8,
		0x763f, 0x7ba1, 0x7ee5, 0x7ffd, 0x7ee5, 0x7ba1, 0x76ef, 0x6ed8, 0x658b,
		0x5a81, 0x4dea, 0x3fff, 0x30fb, 0x2120, 0x10b4, 0x0000, 0xef4c, 0xdee0,
		0xcf06, 0xc002, 0xb216, 0xa57f, 0x9a75, 0x9128, 0x89c1, 0x845f, 0x811b,
		0x8002, 0x811b, 0x845f, 0x89c1, 0x9128, 0x9a76, 0xa57f, 0xb216, 0xc002,
		0xcf06, 0xdee0, 0xef4c };

Int16 j, i = 0;
Int16 sample, left, right;
Int16 out_left = 0, out_right = 0;

Int16 arrayLeft[48];
Int16 arrayRight[48];

Int16 arrayLeft_delay[4800] = {0};
Int16 arrayRight_delay[4800] = {0};

Int16 index_delay = 0;

Int16 index1 = 0;
Int16 delay_ind1 = 0;

Int16 index2 = 0;
Int16 delay_ind2 = 0;

#define Rcv 0x08
#define Xmit 0x20

extern Int16 aic3204_mic();
extern Int16 aic3204_stereo_in1();
extern Int16 aic3204_sin();
extern Int16 aic3204_read();

Int16 reverb_left(Int16 left_ch, Int16 delay) {

	Int16 buf = 0;
	Int16 ret_left_ch = 0;

	arrayLeft[index1] = left_ch;

	delay_ind1 = (delay + index1 -1) % delay;

	buf = arrayLeft[delay_ind1];

	ret_left_ch = left_ch + buf;

	index1 = (index1 + 1) % delay;

	return ret_left_ch;

}

Int16 reverb_right(Int16 right_ch, Int16 delay) {

	Int16 buf = 0;
	Int16 ret_right_ch = 0;

	arrayRight[index2] = right_ch;

	delay_ind2 = (delay + index2 -1) % delay;

	buf = arrayRight[delay_ind2];

	ret_right_ch = right_ch + buf;

	index2 = (index2 + 1) % delay;

	return ret_right_ch;

}

Int16 chorus_left(Int16 left_ch, Int16 voices,  Int16 chorus_width, Int16 shift) {

	Int16 buf = 0;
	Int16 ret_left_ch = 0;
	Int16 v;

	arrayLeft[index1] = left_ch / voices;

	for (v = 1; v < voices; v++) {

		Int16 accumulator = 0;

		delay_ind1 = shift + 20*v + (chorus_width);


	}

	return ret_left_ch;

}

Int16 chorus_right(Int16 right_ch, Int16 delay) {

	Int16 buf = 0;
	Int16 ret_right_ch = 0;

	arrayRight[index2] = right_ch;

	delay_ind2 = (delay + index2 -1) % delay;

	buf = arrayRight[delay_ind2];

	ret_right_ch = right_ch + buf;

	index2 = (index2 + 1) % delay;

	return ret_right_ch;

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
			for (sample = 0; sample < 4800; sample++) {

				/* Read Digital audio */
				while ((Rcv & I2S2_IR) == 0); // Wait for receive interrupt to be pending
						left = I2S2_W0_MSW_R; // 16 bit left channel received audio data
						right = I2S2_W1_MSW_R;// 16 bit right channel received audio data

						arrayLeft_delay[sample] = left;
						arrayRight_delay[sample] = right;

						index_delay = (4800 + sample - 240) % 4800;


						//out_left = (arrayLeft_delay[index_delay]); //+ (left / 2) ;
						out_right = arrayRight_delay[index_delay]; //+ (right / 2);

						out_left = left;
						//out_right = right;

						//out_left =  reverb_left(left, 48);
						//out_right =  reverb_right(right, 48);


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
