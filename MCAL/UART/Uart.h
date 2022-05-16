/*
 * Uart.h
 *
 *  Created on: Apr 16, 2022
 *      Author: fady
 */

#ifndef UART_H_
#define UART_H_

typedef void(*Uart_Cbf)(void);

typedef struct
{
	u8 ModeSelect;
	u8 Parity;
	u8 StopBit;
	u8 CharacterSize;
	u8 ClockPolarity;
	u16 BaudRate;
	u8 Rx_Int;
	u8 Tx_Int;
	u8 EmptyDataReg_Int;
	u8 Receiver_State;
	u8 Transmitter_State;

}Uart_Config;

typedef enum
{
	Uart_enuDataSent = 0,
	Uart_enuBuzy,
	Uart_enuDataReceive,
	Uart_enuNullPointer,
	Uart_enuOk


}Uart_tenuErrorStatus;

typedef enum
{
	Transmit = 0,
	Receive,
	BufferEmpty

}Uart_IntChannel;


/************* DEFINE **********************/

#define F_CLCK						16000000U

/*  Mode Select  */
#define UART_ASYNCHRONOUS			0
#define UART_SYNCHRONOUS			1

/*  Parity  */
#define UART_PARITY_DISABLE			0
#define UART_PARITY_ENABLE_EVEN		2
#define UART_PARITY_ENABLE_ODD		3

/*  Stop Bit  */
#define UART_STOP_BIT_1				0
#define UART_STOP_BIT_2				0

/*  Character Size  */
#define UART_CHARACTER_SIZE_5		0
#define UART_CHARACTER_SIZE_6		1
#define UART_CHARACTER_SIZE_7		2
#define UART_CHARACTER_SIZE_8		3
#define UART_CHARACTER_SIZE_9		7

/*  Clock Polarity  */
#define UART_RISING_EDGE			0
#define UART_FALLING_EDGE			1

/*  Interupt Enable  */
#define UART_RX_DISABLE				1
#define UART_RX_ENABLE				1

#define UART_TX_DISABLE				0
#define UART_TX_ENABLE				1

#define UART_DATA_REG_DISABLE		0
#define UART_DATA_REG_ENABLE		1

#define UART_RECEIVE_DISABLE		0
#define UART_RECEIVE_ENABLE			1

#define UART_TRANSMIT_DISABLE		0
#define UART_TRANSMIT_ENABLE		1




void Uart_vidInit(const Uart_Config* ConfigPtr);

Uart_tenuErrorStatus Uart_enuSendData(const u16 Copy_u8Data);

Uart_tenuErrorStatus Uart_enuReceiveData(const pu16 Add_u8Data);

Uart_tenuErrorStatus Uart_RegisterCallBackFunction(Uart_IntChannel Int_Id, Uart_Cbf Cbf);

Uart_tenuErrorStatus Uart_enuSendBuffer(const s8* Copy_u8Data, u8 Copy_u8Size);



#endif /* UART_H_ */
