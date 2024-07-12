#include "Utils.h"
#include "StdTypes.h"

#define F_CPU	8000000
#include <util/delay.h>

void segment_display(unsigned char num)
{
	unsigned char segmentArr[]={0B00111111,0B00000110,0B01011011,0B01001111,0B01100110,0B01101101,0B01111101,0B00000111,0B01111111,0B01101111,0B01110111,0B01111100,0B00111001,0B01011110,0B01111001,0B01110001};
	unsigned char d0,d1;
	d0=num/10;
	d1=num%10;
	PORTD=segmentArr[d1];
	PORTC=segmentArr[d0];
}


/*FUNCTION TO DISPLAY ANY NUMBER IN HEX:*/
void segment_display_Hex(unsigned char num)
{
	unsigned char segmentArr[]={0B00111111,0B00000110,0B01011011,0B01001111,0B01100110,0B01101101,0B01111101,0B00000111,0B01111111,0B01101111,0B01110111,0B01111100,0B00111001,0B01011110,0B01111001,0B01110001};
	unsigned char d0,d1;
	d0=num&0x0f;
	d1=num>>4;
	PORTD=segmentArr[d0];
	PORTC=segmentArr[d1];
}


void segment_display_BCD(int num)
{
	unsigned char d0,d1;
	d0=num%10;
	d1=(num/10)<<4;

	PORTC=(d1|d0);
}


void segment_display_kit(int num)
{
	unsigned char segmentArr[]={0B00111111,0B00000110,0B01011011,0B01001111,0B01100110,0B01101101,0B01111101,0B00000111,0B01111111,0B01101111};
	unsigned char d0,d1;
	d0=num%10;
	d1=num/10;
	
	SET_BIT(PORTC,6);
	PORTA=segmentArr[d0]<<1;
	CLR_BIT(PORTC,7);
	_delay_ms(1);

	SET_BIT(PORTC,7);	
	PORTA=segmentArr[d1]<<1;
	CLR_BIT(PORTC,6);
	_delay_ms(1);
}
