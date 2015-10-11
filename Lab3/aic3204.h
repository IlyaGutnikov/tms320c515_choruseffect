#ifndef AIC3204_H_
#define AIC3204_H_
#include "i2c.h"
#include "i2s.h"


#define AIC3204_ICADDR 0x18

static uint16 Sin_Headphone[] = { 0x0000, 0x0101, 0x0001, 0x0108, 0x0200, 0x0000, 0x1B00, 0x0407, 0x0620, 0x0700,
		0x0800,
		0x0592,
		0x0D00,
		0x0E80,
		0x1480,
		0x0B84,
		0x0C82,
		0x1284,
		0x1382,
		0x0001,
		0x0C08,
		0x0D08,
		0x0000,
		0x4002,
		0x4100,
		0x3Fd4,
		0x0001,
		0x1000,
		0x1100,
		0x0930,
		0x0000,
		0xFF40,
		0x0001,
		0x340C,
		0x370C,
		0x3603,
		0x39C0,
		0x3B00,
		0x3C00,
		0x0000,
		0x51c0,
		0x5200,
		0xFF14
		};

static uint16 Mic_Headphone[] = { 0x0000, 0x0101, 0x0001, 0x0108, 0x0200, 0x0000, 0x1B00, 0x0407, 0x0620, 0x0700,
		0x0800,
		0x0592,
		0x0D00,
		0x0E80,
		0x1480,
		0x0B84,
		0x0C82,
		0x1284,
		0x1382,
		0x0001,
		0x0C08,
		0x0D08,
		0x0000,
		0x4002,
		0x4100,
		0x3FD4,
		0x0001,
		0x1006,
		0x1106,
		0x0930,
		0x0000,
		0xFF32,
		0x0001,
		0x3340,
		0x34c0,
		0x37C0,
		0x3603,
		0x49C0,
		0x3B5F,
		0x3C5F,
		0x0000,
		0x51C0,
		0x5200,
		0x0000,
		0xFF14
		};

static uint16 Stereo1_Headphone[] = { 0x0000, // Select page 0
		0x0101, // Reset codec
		0x0001, // Select page 1
		0x0108, // Disable crude AVDD from DVDD
		0x0200, // Enable Analog Blocks
		0x0000, // Select page 0
		0x2700, // BCLK and WCLK is set as Slave
		0x0407, // PLL: PLLCLK, CODEC_CLKIN
		0x0620, // PLL: J = 32
		0x0700, // PLL: HI_BYTE(D)
		0x0800, // PLL: LO_BYTE(D)
		0x0592, // PLL: Power up PLL, P=1 and R=2
		0x0D00, // Hi DOSR for DOSR = 128
		0x0E80, // Lo DOSR for DOSR = 128
		0x2480, // AOSR for AOSR = 128
		0x0B84, // Power up NDAC and set to 4
		0x0C82, // Power up MDAC and set to 2
		0x1284, // Power up NADC and set to 4
		0x1382, // Power up MADC and set to 2
		0x0001, // Select page 1
		0x0C08, // LDAC AFIR routed to HPL
		0x0D08, // RDAC AFIR routed to HPR
		0x0000, // Select page 0
		0x4002, // Left vol=right vol
		0x5100, // Left DAC gain to 0dB VOL
		0x3FD4, // Power up left, right data paths
		0x0001, // Select page 1
		0x1000, // Unmute HPL, 0dB gain
		0x1200, // Unmute HPR, 0dB gain
		0x0930, // Power up HPL,HPR
		0x0000, // Select page 0
		0xFF32, // Wait 500
		0x0001, // Select page 1
		0x3430, // STEREO 1 Jack
		0x3730, // IN2_R to RADC_P through 40 k
		0x3603, // CM_1 to LADC_M through 40 k
		0x39C0, // CM_1 to RADC_M through 40 k
		0x3B0F, // MIC_PGA_L unmute
		0x3C0F, // MIC_PGA_R unmute
		0x0000, // Select page 0
		0x51C0, // Power up Left and Right ADC
		0x5200, // Unmute Left and Right ADC
		0x0000, // Select page 0
		0xFF14 // Wait 200
		};

uint16 aic3204_open(void);
uint16 aic3204_close(void);
uint16 aic3204_get(uint16 regnum, uint16* regval);
uint16 aic3204_set(uint16 regnum, uint16 regval);
uint16 aic3204_config(uint16* tab, uint16 len);
uint16 aic3204_read(int16* left_input, int16* right_input);
uint16 aic3204_write(int16* left_output, int16* right_output);
#endif
