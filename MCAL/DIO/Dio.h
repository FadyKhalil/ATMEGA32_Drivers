/*
 * Dio.h
 *
 *  Created on: Mar 6, 2022
 *      Author: fady
 */

#ifndef DIO_H_
#define DIO_H_


#define DIO_u8HIGH 	1
#define DIO_u8LOW 	0
#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3

typedef enum
{

	Dio_enuChanneIdlError = 0,
	Dio_enuLevelError,
	Dio_enuPortIdlError,
	Dio_enuOK

}Dio_tenuErrorStatus;

Dio_tenuErrorStatus Dio_enuWriteChannel(u8 Copy_u8ChannelId, u8 Copy_u8Level);
Dio_tenuErrorStatus Dio_enuReadChannel(u8 Copy_u8ChannelId, pu8 Add_pu8ChannelLevel);
Dio_tenuErrorStatus Dio_enuWritePort(u8 Copy_u8PortId, u8 Copy_u8Value);
Dio_tenuErrorStatus Dio_enuReadPort(u8 Copy_u8ChannelId, pu8 Add_pu8Level);
Dio_tenuErrorStatus Dio_enuFlipChannel(u8 Copy_u8ChannelId);

#endif /* DIO_H_ */
