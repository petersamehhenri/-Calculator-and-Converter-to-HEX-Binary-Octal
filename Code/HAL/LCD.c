#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Cfg.h"
#define F_CPU	8000000
#include <util/delay.h>



#if LCD_MODE==_8_Bit
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins); //0b00111000
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data); //0b00111000
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x38);//5*7 dots & 2 lines mode
	WriteIns(0x0C);//0x0e,0x0f cursor
	WriteIns(0x01);//Clear LCD
	_delay_ms(1);
	WriteIns(0x06);//increment DDRAM address
}

#elif LCD_MODE==_4_Bit
static void WriteIns(u8 ins)
{

	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);

	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);//5*7 dots & 2 lines mode
	WriteIns(0x0C);//0x0e,0x0f cursor
	WriteIns(0x01);//Clear LCD
	_delay_ms(1);
	WriteIns(0x06);//increment DDRAM address
}


void LCD_Init_With_Shift(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);//5*7 dots & 2 lines mode
	WriteIns(0x0C);//0x0e,0x0f cursor
	WriteIns(0x01);//Clear LCD
	_delay_ms(1);
	WriteIns(0x07);//increment DDRAM address
}

#endif

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteString(u8*str)
{
	u8 i;
	for(i=0; i<str[i]; i++)
	{
		LCD_WriteChar(str[i]);
	}
}

void LCD_SetCursor(u8 line, u8 cell)
{
	if(line==0)
	{
		WriteIns(0x80|cell);
	}
	else if(line==1)
	{
		WriteIns(0x80+0x40+cell);
	}
}

void LCD_Clear(void)
{
	WriteIns(0x01);
	_delay_ms(1);
}

void LCD_WriteNumber(s32 num)
{
	u8 str[10];
	u8 i=0, j;
	
	if(num==0)
	{
		LCD_WriteChar('0');		
		return;
	}
	
	if(num<0)
	{
		num=num*(-1);
		LCD_WriteChar('-');
	}
	
	while(num)
	{
		str[i]=num%10+'0';
		i++;
		num=num/10;
	}
	for(j=i; j>0; j--)
	{
		LCD_WriteChar(str[j-1]);
	}
}


void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7; i>=0; i--)
	{
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}

void LCD_WriteHex(u8 num)
{
	u8 res=num/16, rem=num%16;
	
	if(res<10)
	{
		LCD_WriteNumber(res);
	}
	else if(res==10)
	{
		LCD_WriteChar('A');
	}
	else if(res==11)
	{
		LCD_WriteChar('B');
	}
	else if(res==12)
	{
		LCD_WriteChar('C');
	}
	else if(res==13)
	{
		LCD_WriteChar('D');
	}
	else if(res==14)
	{
		LCD_WriteChar('E');
	}
	else if(res==15)
	{
		LCD_WriteChar('F');
	}
	
	if(rem<10)
	{
		LCD_WriteNumber(rem);
	}
	else if((num%16)==10)
	{
		LCD_WriteChar('A');
	}
	else if((num%16)==11)
	{
		LCD_WriteChar('B');
	}
	else if((num%16)==12)
	{
		LCD_WriteChar('C');
	}
	else if((num%16)==13)
	{
		LCD_WriteChar('D');
	}
	else if((num%16)==14)
	{
		LCD_WriteChar('E');
	}
	else if((num%16)==15)
	{
		LCD_WriteChar('F');
	}
}


void LCD_CustomChar(u8 loc, u8*pattern)
{
	WriteIns(0x40+ loc*8);
	for (u8 i=0; i<8; i++)
	{
		WriteData(pattern[i]);
	}
	WriteIns(0x80);
}