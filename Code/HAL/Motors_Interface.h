

#ifndef MOTORS_INTERFACE_H_
#define MOTORS_INTERFACE_H_

#define  MOTOR_PIN_NUMBERS   3
#define  IN1   0
#define  IN2   1
#define  EN    2

typedef enum{
	M1,
	M2,
	M3,
	M4,
	NUMBER_MOTORS
	}MOTOR_type;




void MOTOR_Init(void);


void MOTOR_Stop(MOTOR_type motor);

void MOTOR_CW(MOTOR_type motor);

void MOTOR_CCW(MOTOR_type motor);


// typedef enum{
// 	NOT_PRESSED=0,
// 	PRESSED=1
// 	}Button_type;
// 
// Button_type get_button_read(DIO_PinStatus_type pin)
// {
// 	switch(pin)
// 	{
// 		case INPULL:
// 		
// 	}
}
#endif /* MOTORS_INTERFACE_H_ */