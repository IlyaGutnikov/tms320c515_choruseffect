/*
 *  I2C implementation
 *
 */
#include "i2c.h"

Int32 i2c_timeout = 0x0fff;

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_init( )                                                            *
 *                                                                          *
 *      Enable and initalize the I2C module                                 *
 *      The I2C clk is set to run at 20 KHz                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 I2C_init( )
{
    I2C_MDR = 0x0400;             // Reset I2C
    I2C_PSC   = 15;               // Config prescaler for 100MHz
    I2C_CLKL  = 25;               // Config clk LOW for 100kHz
    I2C_CLKH  = 25;               // Config clk HIGH for 100kHz
    
    I2C_MDR   = 0x0420;        // Release from reset; Master, Transmitter, 7-bit address
    
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_close( )                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 I2C_close( )
{
    I2C_MDR = 0;                      // Reset I2C
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_reset( )															*
 *  ����� I2C                                                               *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 I2C_reset( )
{
    I2C_close( );
    I2C_init( );
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_write( i2c_addr, data, len )                                       *
 *                                                                          *
 *      I2C write in Master mode                                            *
 *                                                                          *
 *      i2c_addr    <- I2C slave address                                    *
 *      data        <- I2C data ptr                                         *
 *      len         <- # of bytes to write                                  *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 I2C_write( Uint16 i2c_addr, Uint8* data, Uint16 len )
{
    Int16 timeout, i;

		//I2C_IER = 0x0000;
        I2C_CNT = len;                    // Set length
        I2C_SAR = i2c_addr;               // Set I2C slave address
        I2C_MDR = MDR_STT                 // Set for Master Write
                  | MDR_TRX				  // ����������
                  | MDR_MST				  // ������� ����������
                  | MDR_IRS				  // ��������� ������
                  | MDR_FREE;			  // ������ ��������� � ����������

        c5515_wait(100);                // �������� ����� ���������

        for ( i = 0 ; i < len ; i++ )
        {
           I2C_DXR = data[i];            // ������ ����� � ������� �����������
           timeout = 0x7fff; 			 //i2c_timeout
            // �������� �������� ������
            do
            {
                if ( timeout-- < 0  )
                {
                    I2C_reset( );
                    return -1;
                }
            } while ( ( I2C_STR & STR_XRDY ) == 0 );// Wait for Tx Ready
        }

        I2C_MDR |= MDR_STP;             // ��������� STOP

		c5515_waitusec(1000); 			// ������� � �����

        return 0;

}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _I2C_read( i2c_addr, data, len )                                        *
 *                                                                          *
 *      I2C read in Master mode                                             *
 *                                                                          *
 *      i2c_addr    <- I2C slave address                                    *
 *      data        <- I2C data ptr                                         *
 *      len         <- # of bytes to write                                  *
 *                                                                          *
 *      Returns:    0: PASS                                                 *
 *                 -1: FAIL Timeout                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 I2C_read( Uint16 i2c_addr, Uint8* data, Uint16 len )
{
	// ��������� ������
    Int32 timeout, i;

    I2C_CNT = len;                    // ������� ����� ������ � ��������
    I2C_SAR = i2c_addr;               // ������ ����� ��������
    I2C_MDR = MDR_STT                 // Set for Master Read
              | MDR_MST				  // ������� ����������
              | MDR_IRS				  // ��������� ������
              | MDR_FREE;			  // ������ ��������� � ����������

    c5515_wait( 10 );            // �������� ����� �������

    // ����� ������
    for ( i = 0 ; i < len ; i++ )
    {
        timeout = i2c_timeout;

        // �������� ������ ������
        do
        {
            if ( timeout-- < 0 )
            {
                I2C_reset( );
                return -1;
            }
        } while ( ( I2C_STR & STR_RRDY ) == 0 );

        data[i] = I2C_DRR;            // �������� ������
    }

    I2C_MDR |= MDR_STP;               // ��������� STOP

	c5515_waitusec(10);				  // ������� � �����
    return 0;
}
