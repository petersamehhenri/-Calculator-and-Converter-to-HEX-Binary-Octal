// 
// 
// #define  MOTOR_PROG 1
// #include "StdTypes.h"
// 
// #include "DIO_Interface.h"
// #include "Motors_Interface.h"
// #include "Motor_Cfg.h"
// 
// 
// 
// void MOTOR_Init(void);
// 
// 
// void MOTOR_Stop2(MOTOR_type motor)
// {
// 	switch(motor)
// 	{
// 		case M1:
// 		DIO_WritePin(M1_IN1,LOW);
// 		DIO_WritePin(M1_IN2,LOW);
// 		break;
// 		case M2:
// 		DIO_WritePin(M2_IN1,LOW);
// 		DIO_WritePin(M2_IN2,LOW);
// 		break;
// 		case M3:
// 		DIO_WritePin(M3_IN1,LOW);
// 		DIO_WritePin(M3_IN2,LOW);
// 		break;
// 		case M4:
// 		DIO_WritePin(M4_IN1,LOW);
// 		DIO_WritePin(M4_IN2,LOW);
// 		break;
// 		
// 	}
// 	
// 	
// }
// void MOTOR_Stop(MOTOR_type motor)
// {	
// 	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
// 	DIO_WritePin(MotorPinsArray[motor][IN2],LOW);
// }
// 
// void MOTOR_Stop3(MOTOR_type motor)
// {
// 	DIO_WritePin(MotorPinsArray2[motor].IN1,LOW);
// 	DIO_WritePin(MotorPinsArray2[motor].IN2,LOW);
// }
// 
// 
// void MOTOR_CW(MOTOR_type motor)
// {
// 	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
// 	DIO_WritePin(MotorPinsArray[motor][IN2],LOW);
// }
// 
// void MOTOR_CCW(MOTOR_type motor)
// {
// 	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
// 	DIO_WritePin(MotorPinsArray[motor][IN2],LOW);
// 	
// }


