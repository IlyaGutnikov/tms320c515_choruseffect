/*
 *  Copyright 2009 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  AIC3204 Test
 *
 */

#define AIC3204_I2C_ADDR 0x18
#include "C5515.h"
#include "gpio.h"
#include "i2c.h"
#include "stdio.h"

extern Int16 aic3204_tone_headphone( );
extern Int16 aic3204_loop_mic_in( );
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _AIC3204_rget( regnum, regval )                                         *
 *                                                                          *
 *      Return value of codec register regnum                               *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 AIC3204_rget(  Uint16 regnum, Uint16* regval )
{
    Int16 retcode = 0;
    Uint8 cmd[2];

    cmd[0] = regnum & 0x007F;       // 7-bit Device Address
    cmd[1] = 0;

    retcode |= I2C_write( AIC3204_I2C_ADDR, cmd, 1 );
    retcode |= I2C_read( AIC3204_I2C_ADDR, cmd, 1 );

    *regval = cmd[0];
    EVM5515_wait( 10 );
    return retcode;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _AIC3204_rset( regnum, regval )                                         *
 *                                                                          *
 *      Set codec register regnum to value regval                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 AIC3204_rset( Uint16 regnum, Uint16 regval )
{
    Uint8 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Register Address
    cmd[1] = regval;                // 8-bit Register Data

    return I2C_write( AIC3204_I2C_ADDR, cmd, 2 );
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  aic3204_test( )                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 aic3204_test( )
{
	/* Configure Parallel Port */
    SYS_EXBUSSEL &= ~0x7000;   //
    SYS_EXBUSSEL |=  0x1000;   // Configure Parallel Port for I2S2
    /* Configure Serial Port */
	SYS_EXBUSSEL &= ~0x0C00;   //
	SYS_EXBUSSEL |=  0x0400;   // Serial Port mode 1 (I2S1 and GP[11:10]).
	EVM5515_GPIO_init();
	EVM5515_GPIO_setDirection(GPIO10, GPIO_OUT);
	EVM5515_GPIO_setOutput( GPIO10, 1 );    // Take AIC3201 chip out of reset
	I2C_init( );                    // Initialize I2C
    /* Codec tests */


    printf( "<-> Microphone --> to HP\n" );
    if ( aic3204_loop_mic_in( ) )
        return 1;
	EVM5515_GPIO_setOutput( GPIO26, 0 );



    return 0;
}
