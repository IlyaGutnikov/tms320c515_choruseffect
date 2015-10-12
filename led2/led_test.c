/*
 *  Copyright 2009 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  LED Test
 *
 */

#include "evm5515.h"
#include "evm5515_led.h"

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  led_test( )                                                             *
 *      Running Eight LED test                                              *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 led_test( )
{
    Int16 j;

    /* Initialize the LED module */
    EVM5515_LED_init( );

    /* Running LED test */
    for ( j = 0 ; j < 10 ; j++ )
    {
        EVM5515_LED_on( 0 );
        EVM5515_waitusec( 500000 );
        EVM5515_LED_off( 0 );
        EVM5515_waitusec( 500000 );
    }

    /* Turn on LED to indicate a PASS */
    EVM5515_LED_on( 0 );

    return 0;
}

