/*
 * Uart.c
 *
 *  Created on: Apr 16, 2022
 *      Author: fady
 */


#include "avr/io.h"
//#include "avr/interrupt.h"
#include "../../Service/UTILITIES/Std_types.h"
#include "Uart.h"
#include "../DIO/Dio.h"

static u8 Uart_BuzyFlag[2] = {0};
static u8 Uart_9BitMode = 0;
static Uart_Cbf Uart_prvCallBack[3] = {NULL};

/*send buffer*/
static u8 Uart_prvIndex = 0;
static u8* Buffer;



void Uart_vidInit(const Uart_Config* ConfigPtr)
{
	u8 Loc_u8TempRegister = 0x80;
	Loc_u8TempRegister = ConfigPtr->ModeSelect << 6 | ConfigPtr->Parity << 4 | ConfigPtr->StopBit << 3;
	Loc_u8TempRegister |= (ConfigPtr->CharacterSize & 0x03) << 1;
//	UBRRH = 0x02;
	UCSRC = Loc_u8TempRegister;

	/*Check if using bit number 9*/
	Uart_9BitMode = ConfigPtr->CharacterSize == 0x07 ? 1: 0;


	Loc_u8TempRegister = 0;
	Loc_u8TempRegister = ConfigPtr->Rx_Int << 7 | ConfigPtr->Tx_Int << 6 | ConfigPtr->EmptyDataReg_Int << 5;
	Loc_u8TempRegister |= ConfigPtr->Receiver_State << 4 | ConfigPtr->Transmitter_State << 3;
	Loc_u8TempRegister |= (ConfigPtr->CharacterSize & 0x04) << 2;
	UCSRB = Loc_u8TempRegister;

	/*Calculating BaudRate For UART*/
	Loc_u8TempRegister = (F_CLCK/((u64)ConfigPtr->BaudRate * 16));
	UBRRH = 0;
	UBRRL = Loc_u8TempRegister-1;


	return;
}

Uart_tenuErrorStatus Uart_enuSendData(const u16 Copy_u8Data)
{
	Uart_tenuErrorStatus Loc_enuErrorStatus = Uart_enuDataSent;
	if(Uart_BuzyFlag[Transmit] == 0)
	{
		Uart_prvIndex = 0;
		UDR = (u8)Copy_u8Data;

		if (Uart_9BitMode == 1)
		{
			UCSRA = (Copy_u8Data & 0x0100) << 6;

		}

		Uart_BuzyFlag[Transmit] = 1;
	}
	else
	{
		Loc_enuErrorStatus = Uart_enuBuzy;
	}

	return Loc_enuErrorStatus;

}


Uart_tenuErrorStatus Uart_enuSendBuffer(const u8* Copy_u8Data, u8 Copy_u8Size)
{
	Uart_tenuErrorStatus Loc_enuErrorStatus = Uart_enuDataSent;
	if(Uart_BuzyFlag[Transmit] == 0)
	{
		Buffer = (u8*)Copy_u8Data;
		Uart_BuzyFlag[Transmit] = 1;
		Uart_prvIndex = Copy_u8Size;
		UDR = Copy_u8Data[0];
	}
	else
	{
		Loc_enuErrorStatus = Uart_enuBuzy;
	}

	return Loc_enuErrorStatus;

}



Uart_tenuErrorStatus Uart_enuReceiveData(pu16 Add_u16Data)
{
	Uart_tenuErrorStatus Loc_enuErrorStatus = Uart_enuDataReceive;

	if(Add_u16Data == NULL)
	{
		Loc_enuErrorStatus = Uart_enuNullPointer;

	}
	else
	{
		if(Uart_BuzyFlag[Receive] == 0)
		{
			*Add_u16Data = UDR;
			if(Uart_9BitMode == 1)
			{
				*Add_u16Data = (UCSRA & 0x80) << 8;
			}

			Uart_BuzyFlag[Receive] = 1;
		}
		else
		{
			Loc_enuErrorStatus = Uart_enuBuzy;
		}
	}

	return Loc_enuErrorStatus;
}

Uart_tenuErrorStatus Uart_RegisterCallBackFunction(Uart_IntChannel Int_Id, Uart_Cbf Cbf)
{
	Uart_tenuErrorStatus Loc_enuErrorStatus = Uart_enuOk;

	if(Cbf == NULL)
	{
		Loc_enuErrorStatus = Uart_enuNullPointer;
	}
	else
	{
		Uart_prvCallBack[Int_Id] = Cbf;
	}

	return Loc_enuErrorStatus;

}

//Transmit handler
void __vector_15 (void) __attribute__ ((signal, used, externally_visible));
void __vector_15 (void)
{
	static u8 Index = 0;

	if(Uart_prvCallBack[Transmit] != NULL && Index == Uart_prvIndex)
	{
		Uart_BuzyFlag[Transmit] = 0;
		Index = 0;
		Uart_prvCallBack[Transmit]();
	}
	else
	{
		Index++;
		UDR = Buffer[Index];
	}

}


//Receive handler
void __vector_13 (void) __attribute__ ((signal, used));
void __vector_13 (void)
{
	if(Uart_prvCallBack[Receive] != NULL)
	{
		Uart_prvCallBack[Receive]();
		Uart_BuzyFlag[Receive] = 0;
	}
}

//Empty Buffer
void __vector_14 (void) __attribute__ ((signal, used));
void __vector_14 (void)
{
	if(Uart_prvCallBack[BufferEmpty] != NULL)
	{
		Uart_prvCallBack[BufferEmpty]();
//		Uart_BuzyFlag[] = 0;
	}
}
