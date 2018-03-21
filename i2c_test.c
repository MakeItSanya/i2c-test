/*
 * i2c_test.c
 *
 * Created: 19.03.2018 16:14:11
 *  Author: Grout
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
	while(!(TWCR & (1<<TWINT))); //�������� ��������� TWINT
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
	
	//������ ��� �������������
	//A0 - ������ � ������ ����; A1 - ������ � ����� ����
	//C0 - ������ ����� ������; C8 - ������ ������ ������
	//12 - ������ �����, 02, 22 - ����� ����� �������
	//7F - ������� (�������� 0xFF)
	static const unsigned char PROGMEM init[18]=
	{
		0xA8,0x3F,0xD3,0x00,0x40,0xA1,0xC8,0xDA,0x12,
		0x81,0xFE,0xA4,0xA6,0xD5,0x80,0x8D,0x14,0xAF,
	};
	
	twiSendByte(addr);

	for(i = 0; i < 18; i++)
	{
		twiSendByte(COM); //������� ���� ����������� ����� �������
		twiSendByte(pgm_read_byte(init+i));
	}
}

void clearDisplay(void)
{
	//�������� Horizontal Addressing Mode (���������� ������ �� ���� ���� ��� ������ �����)
	twiSendByte(COM);
	twiSendByte(0x20);
	twiSendByte(COM);
	twiSendByte(0x00);
	
	//��������� ������ ����� �������
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