
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_Init(void);

void LCD_Init_With_Shift(void);

void LCD_WriteChar(u8 ch);

void LCD_WriteString(u8*str);

void LCD_SetCursor(u8 line, u8 cell);

void LCD_Clear(void);

void LCD_WriteNumber(s32 num);

void LCD_WriteBinary(u8 num);

void LCD_WriteHex(u8 num);

void LCD_CustomChar(u8 loc, u8*pattern);

#endif /* LCD_INTERFACE_H_ */