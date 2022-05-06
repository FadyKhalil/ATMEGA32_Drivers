/*
 * Uart.c
 *
 *  Created on: Apr 30, 2022
 *      Author: fady
 */



#include "Service/UTILITIES/Std_types.h"
#include "MCAL/UART/Uart.h"
#include "MCAL/DIO/Dio.h"
#include "MCAL/PORT/Port.h"
#include "MCAL/GIE/Gie.h"
#include "util/delay.h"


void Led(void)
{
	Dio_enuFlipChannel(11);
}

void Led1(void)
{
	Dio_enuFlipChannel(12);
}


int main(void)
{

	u16 Loc_u8Value = 'a';


	Uart_Config UartConfig = {
			.BaudRate = 9600,
			.CharacterSize = UART_CHARACTER_SIZE_8,
			.ClockPolarity = UART_RISING_EDGE,
			.EmptyDataReg_Int = UART_DATA_REG_DISABLE,
			.ModeSelect = UART_ASYNCHRONOUS,
			.Parity = UART_PARITY_DISABLE,
			.Receiver_State = UART_RECEIVE_ENABLE,
			.Rx_Int = UART_RX_ENABLE,
			.Tx_Int = UART_TX_ENABLE,
			.StopBit = UART_STOP_BIT_1,
			.Transmitter_State = UART_TRANSMIT_ENABLE
	};

	Uart_vidInit(&UartConfig);

	PORT_vidInit();

	Gie_vidEnable();

	Uart_RegisterCallBackFunction(Transmit, Led);
	Uart_RegisterCallBackFunction(Receive, Led1);



	while(1)
	{

		Uart_enuReceiveData(&Loc_u8Value);
		if(Loc_u8Value == 'A')
			Uart_enuSendData('H');


	}

}
