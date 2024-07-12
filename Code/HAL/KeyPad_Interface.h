

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

typedef enum{
	FIRST_INPUT=0,
	SECOND_INPUT,
	THIRD_INPUT,
	FORTH_INPUT
}KEYPAD_Input_types;


typedef enum{
	FIRST_OUTPUT=0,
	SECOND_OUTPUT,
	THIRD_OUTPUT,
	FORTH_OUTPUT
}KEYPAD_Output_types;

#define NO_KEY	'T'

void KEYPAD_Init(void);

u8 KEYPAD_GetKey(void);



#endif /* KEYPAD_INTERFACE_H_ */