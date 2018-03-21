/*
 * i2c_test.c
 *
 * Created: 19.03.2018 16:14:11
 *  Author: Grout and Sanya
 */ 
#include "i2c_test.h"


void twiClockInit(void)
{
	DDRD = 0x08;
	PORTD |= (1<<PORTD3);
	_delay_ms(1);
	PORTD &= !(1<<PORTD3);
	_delay_ms(10);
	PORTD |= (1<<PORTD3);
	TWSR = 0;
	TWBR = TWBR_VALUE;
}

void twiStart(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT))); //Îæèäàíèå óñòàíîâêè TWINT
}

void twiStop(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void twiSendByte(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void ssd1306Init(uint8_t addr)
{
	unsigned char i;
	
	//ÌÀÑÑÈÂ ÄËß ÈÍÈÖÈÀËÈÇÀÖÈÈ
	//A0 - íà÷àëî â ïðàâîì óãëó; A1 - íà÷àëî â ëåâîì óãëó
	//C0 - íà÷àëî ñíèçó ýêðàíà; C8 - íà÷àëî ñâåðõó ýêðàíà
	//12 - ïðÿìàÿ ëèíèÿ, 02, 22 - ëèíèÿ ÷åðåç ñòðî÷êó
	//7F - ÿðêîñòü (ìàêñèìóì 0xFF)
	static const unsigned char PROGMEM init[18]=
	{
		0xA8,0x3F,0xD3,0x00,0x40,0xA1,0xC8,0xDA,0x12,
		0x81,0xFE,0xA4,0xA6,0xD5,0x80,0x8D,0x14,0xAF,
	};
	
	twiSendByte(addr);

	for(i = 0; i < 18; i++)
	{
		twiSendByte(COM); //Ïîñûëêà áèòà âêëþ÷àþùåãî ðåæèì êîìàíäû
		twiSendByte(pgm_read_byte(init+i));
	}
}

void clearDisplay(void)
{
	//âûáèðàåì Horizontal Addressing Mode (çàïîëíåíèå ýêðàíà ïî òèïó òîãî êàê ÷èòàåì êíèãó)
	twiSendByte(COM);
	twiSendByte(0x20);
	twiSendByte(COM);
	twiSendByte(0x00);
	
	//çàïîëíÿåì ñòðîêó ñëåâà íàïðàâî
	twiSendByte(DATS);
	for(unsigned char i = 0; i < 8; i++)
	{
		for(unsigned char k = 0; k < 128; i++)
		{
			twiSendByte(0x00);
		}
	}
}

void drawMining(void)
{
	
}
