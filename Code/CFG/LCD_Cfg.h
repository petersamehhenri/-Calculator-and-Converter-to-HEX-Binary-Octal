
#ifndef LCD_CFG_H_
#define LCD_CFG_H_


#define _4_Bit		0
#define _8_Bit		1

/*_8_Bit_Mode	OR _4_Bit_Mode*/
#define LCE_MODE	_4_Bit_Mode		


#define RS				PINA1
#define EN				PINA2


#define D4				PINA3
#define D5				PINA4
#define D6				PINA5
#define D7				PINA6

#define LCD_PORT		PA

#endif /* LCD_CFG_H_ */