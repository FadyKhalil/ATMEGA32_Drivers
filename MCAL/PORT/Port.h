/*
 * Port.h
 *
 *  Created on: Mar 5, 2022
 *      Author: fady
 */

#ifndef PORT_H_
#define PORT_H_


#define PORT_u8OUTPUT 1
#define PORT_u8INPUT 0

#define PORT_u8OUTPUT_HIGH 		2
#define PORT_u8OUTPUT_LOW 		3
#define PORT_u8INPUT_PULLUP 	4
#define PORT_u8INPUT_IMPEDENCE 	5


typedef enum {

	Port_enuPinError = 0,
	Port_enuDirError,
	Port_enuModeError,
	Port_enuOK

}Port_tenuErrorStatus;


void PORT_vidInit(void);
Port_tenuErrorStatus Port_enuSetPinDirection(u8 Copy_u8PinNum, u8 Copy_u8PinDirection);
Port_tenuErrorStatus Port_enuSetPinMode(u8 Copy_u8PinNum, u8 Copy_u8PinMode);

#endif /* PORT_H_ */
