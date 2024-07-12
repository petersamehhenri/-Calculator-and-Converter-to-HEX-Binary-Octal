

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define FIRST_OUTPUT	PINB4
#define FIRST_INPUT		PIND2

// #define SECOND_OUTPUT	PINB5
// #define SECOND_INPUT	PIND3
// 
// #define THIRD_OUTPUT	PINB6
// #define THIRD_INPUT		PIND4
// 
// #define FORTH_OUTPUT	PINB7
// #define FORTH_INPUT		PIND5

#define ROWS	4
#define COLS	4

const u8 KeysArray[ROWS][COLS]={
	{'7','8','9','A'},
	{'4','5','6','B'},
	{'1','2','3','E'},
	{'c','0','=','F'},
};

#endif /* KEYPAD_CFG_H_ */