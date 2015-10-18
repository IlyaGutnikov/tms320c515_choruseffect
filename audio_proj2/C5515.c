#include "C5515.h"

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  EVM5515_wait( delay )                                                   *
 *                                                                          *
 *      ����������� ��������                               					*
 *                                                                          *
 * ------------------------------------------------------------------------ */
void c5515_wait( Uint32 delay )
{
    volatile Uint32 i;
    for ( i = 0 ; i < delay ; i++ ){ };
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _waitusec( usec )                                                       *
 *                                                                          *
 *      ����������� �������� � 'x' �����������                              *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void c5515_waitusec( Uint32 usec )
{
    c5515_wait( (Uint32)usec * 8 );
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  EVM5515_init( )                                                         *
 *                                                                          *
 *      ������������� ���������������                                       *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 c5515_init( )
{
    /* Enable clocks to all peripherals */
    SYS_PCGCR1 = 0x0000;
    SYS_PCGCR2 = 0x0000;
	
    return 0;
}
