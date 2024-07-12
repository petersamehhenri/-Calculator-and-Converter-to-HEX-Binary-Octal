#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#define F_CPU	8000000
#include <util/delay.h>
#include "Segment.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"

#define DELAY	2500

u16 power(u8 num, u8 power)
{
	u8 i=0; 
	u16 res=1;
	for(i=0; i<power; i++)
	{
		res=res*num;
	}
	return res;
}

u8 Convert_Bin_To_Dec(u8* str)
{
	s8 i;
	u8 res=0;
	for(i=7; i>=0; i--)
	{
		if(str[i]==1)
		{
			res=res+((power(2,7-i))*1);
		}
	}
	return res;
}

u8 Convert_Hex_To_Dec(u8* str)
{
	s8 i;
	u8 res=0, num;
	for(i=1; i>=0; i--)
	{
		if((str[i]>='0') && (str[i]<='9'))
		{
			num=str[i]-'0';
		}
		else if((str[i]>='A')&&(str[i]<='F'))
		{
			num=str[i]-'A'+10;
		}
			res=res+(power(16,1-i))*num;
	}
	return res;
}
	
	


int main(void)
{
DIO_Init();
LCD_Init();
KEYPAD_Init();

/*Typing on LCD(Initialization)*/
{
	u8 str1[]="Welcome";
	u8 str2[]="Converter by";
	u8 str3[]="Peter.";
	for (u8 i=0; str1[i]; i++)
	{
		LCD_SetCursor(0,i+4);
		LCD_WriteChar(str1[i]);
		_delay_ms(250);
	}
	
	_delay_ms(DELAY);
	LCD_Clear();
	for (u8 i=0; str2[i]!=0; i++)
	{
		LCD_SetCursor(0,i+2);
		LCD_WriteChar(str2[i]);
		_delay_ms(250);
	}
	
	for (u8 i=0; str3[i]!=0; i++)
	{
		LCD_SetCursor(1,i+5);
		LCD_WriteChar(str3[i]);
		_delay_ms(250);
	}
	_delay_ms(DELAY);
}/*End of typing on LCD(Initialization)*/
		
		
u8 key, from, to, num=0, num_hex=0, m=0, a=0, res=0, c=0, i=6;
u8 str_bin[8], str_hex[2];
u8 flag_start=1, flag_from=0, flag_to=0, flag_1=0, flag_receive=0, flag_hex=0, flag_res=0, flag_clear=0;
		
		
while(1)
{
	while(flag_start)
	{
		flag_clear=0;
		LCD_Clear();
		LCD_SetCursor(0,6);
		LCD_WriteString("From");

		LCD_SetCursor(1,0);
		LCD_WriteString("1-D");

		LCD_SetCursor(1,6);
		LCD_WriteString("2-B");

		LCD_SetCursor(1,13);
		LCD_WriteString("3-H");
		flag_start=0;
		flag_from=1;
	}
	
	/*Choose convert from: */		
	while(flag_from)
	{
		key=KEYPAD_GetKey();
		if(key!=NO_KEY)
		{
			if (key>='1' && key<='3')
			{
				from=key-'0';
				LCD_SetCursor(0,15);
				if(from==1)
				{	
					LCD_WriteChar('D');
				}
				if(from==2)
				{
						
					LCD_WriteChar('B');
				}
				if(from==3)
				{
					LCD_WriteChar('H');
				}
				flag_to=1;
				flag_from=0;
			}
		}
	}/*End of choosing convert from: */
			
			
	/*Choose convert to: */		
	while(flag_to)
	{
			LCD_SetCursor(0,6);
			LCD_WriteString("To    ");

			key=KEYPAD_GetKey();
			if(key!=NO_KEY)
			{
				if (key>='1' && key<='3')
				{
					to=key-'0';
					flag_to=0;
					flag_1=1;	
				}
			}
	}/*End of choosing convert to: */
		
		
	/*Process to display 'from' and 'to' on display*/
	LCD_Clear();
	_delay_ms(400);
	while(flag_1)
	{
		LCD_SetCursor(0,0);
		if(from==1)
		{
			LCD_WriteString("DEC: ");
		}
		else if(from==2)
		{
			LCD_WriteString("BIN: ");
		}
		else if(from==3)
		{	
			LCD_WriteString("HEX: ");
		}
			
		LCD_SetCursor(1,0);
			
		if(to==1)
		{
			LCD_WriteString("DEC: ");
		}
		else if(to==2)
		{
			LCD_WriteString("BIN: ");
		}
		else if(to==3)
		{
			LCD_WriteString("HEX: ");
		}
		flag_receive=1;
		flag_1=0;

	}
		/*End of the process to display 'from' and 'to' on display*/
			
			
		/*Process to receive the number from the user*/
		LCD_SetCursor(0,6);

		while(flag_receive)
		{
			key=KEYPAD_GetKey();
			if(key!=NO_KEY)
			{
				if (key=='c')
				{
					flag_clear=1;
					flag_start=1;
					flag_receive=0;
				}
					
				if((from==1) && (flag_clear==0))
				{
					if (key>='0' && key<='9')
					{
						LCD_WriteString("        ");
						LCD_SetCursor(0,i);
						num=num*10+key-'0';
						LCD_WriteChar(key);
						i++;
					}
				}
				else if((from==2) && (flag_clear==0))
				{
					if(key=='0' || key=='1')
					{
						LCD_WriteString("        ");
						LCD_SetCursor(0,i);
						str_bin[m]=key-'0';
						LCD_WriteChar(key);
						LCD_WriteString("        ");
						m++;
						i++;
						if(m>=8)
						{
							m=0;
							i=6;
						}
					}
				}
				else if((from==3) && (flag_clear==0))
				{

					if(((key>='0')&&(key<='9'))||((key=='A')||(key=='B')||(key=='E')||(key=='F')))
					{
						LCD_WriteString("          ");
						LCD_SetCursor(0,i);
						str_hex[a]=key;
						LCD_WriteChar(key);
						LCD_WriteString("          ");
						i++;
						a++;
					}
						
					if(a==2)
					{
						LCD_SetCursor(0,6);
						a=0;
						i=6;
					}
				}
				if(key=='=')
				{
					LCD_SetCursor(0,6);
					i=6;
					m=0;
					a=0;

					/*Process to show the result on LCD*/
						
					if(((from==1)&&(to==2)) && (flag_clear==0))
					{
						LCD_SetCursor(0,6);
						LCD_WriteNumber(num);
						LCD_SetCursor(1,6);
						LCD_WriteBinary(num);					
						num=0;
						LCD_SetCursor(0,6);
					}
						
					else if(((from==1)&&(to==3)) && (flag_clear==0))
					{
						LCD_SetCursor(1,6);
						LCD_WriteHex(num);
						num=0;
						LCD_SetCursor(0,6);
					}
						
					else if(((from==2)&&(to==1)) && (flag_clear==0))
					{
						LCD_SetCursor(0,6);
						LCD_WriteString(str_bin);
			
						res=Convert_Bin_To_Dec(str_bin);
							
						LCD_SetCursor(1,6);
						LCD_WriteNumber(res);
						LCD_WriteString("      ");
						str_bin[8]="00000000";
					}
						
					else if(((from==2)&&(to==3)) && (flag_clear==0))
					{
						res=Convert_Bin_To_Dec(str_bin);
						LCD_SetCursor(1,6);
						LCD_WriteHex(res);
						LCD_WriteString("      ");
						str_bin[8]="00000000";
					}
						
					else if(((from==3)&&(to==1)) && (flag_clear==0))
					{
						res=Convert_Hex_To_Dec(str_hex);
						LCD_SetCursor(1,6);
						LCD_WriteNumber(res);
						LCD_WriteString("      ");
						LCD_SetCursor(0,6);
						str_hex[2]="00";
					}
						
					else if(((from==3)&&(to==2)) && (flag_clear==0))
					{
						res=Convert_Hex_To_Dec(str_hex);
						LCD_SetCursor(1,6);
						LCD_WriteBinary(res);	
						LCD_WriteString("      ");
						LCD_SetCursor(0,6);
						str_hex[2]="00";
					}
					/*End of the process to show the result on LCD*/				
				}	
				/*End of the process to receive the number from the user*/
			}
		}
	}
}