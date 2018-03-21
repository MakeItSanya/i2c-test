/*
 * i2c_test.h
 *
 * Created: 21.03.2018 10:21:55
 *  Author: Grout
 */ 
#pragma once

#define F_CPU 16000000
#define F_I2C 200000
#define TWBR_VALUE ((F_CPU/F_I2C)-16)/2
#define SSD1306_ADDR 0x78
#if ((TWBR_VALUE > 255) || (TWBR_VALUE == 0))
	#error "TWBR value is not correct"
#endif

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define NAME		0x78		    //юдпея сярпниярбю мю ьхме
#define DATS		0b01000000		//оепедювю меяйнкэйху аюир дюммшу
#define DAT			0b11000000		//оепедювю ндмнцн аюирЮ дюммшу
#define COM			0b10000000		//оепедювю ндмнцн аюирЮ йнлюмдш

void twiClockInit(void);
void twiStart(void);
void twiStop(void);
void ssd1306Init(uint8_t);
void clearDisplay(void);
void drawMining(void);
void twiSendByte(unsigned char);