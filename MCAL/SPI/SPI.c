/*
 * SPI.c
 *
 *  Created on: May 16, 2022
 *      Author: fady
 */


#include "../../Service/UTILITIES/Std_types.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "SPI.h"
#include "../DIO/Dio.h"

CallFunc Spi_CallFunc = (void*)0;

void Spi_vidInit(const Spi_Config* ConfigPtr)
{
	if(ConfigPtr)
	{
		u8 Loc_u8TempRegister = 0;

		Loc_u8TempRegister = SPCR;
		Loc_u8TempRegister &= ~(0x07);

		Loc_u8TempRegister = ConfigPtr->Interrupt_State << SPIE
							| ConfigPtr->Spi_State << SPE
							| ConfigPtr->Data_Order << DORD
							| ConfigPtr->Clock_Polarity << CPOL
							| ConfigPtr->Clock_Phase << CPHA
							| ConfigPtr->Clk_Frequency << SPR0;

		SPCR = Loc_u8TempRegister;
	}
	else
	{
		// return Null
	}
}

u8 Spi_u8Transfer(u8 Data)
{
	SPDR = Data;
//	while(!((SPSR << SPIF) & 1));
	return SPDR;
}

void Spi_vidSelectSlave(u8 Slave)
{
	SPCR |= Slave << MSTR;
}

void Spi_vidRegisterCallFunction(CallFunc Cbf)
{
	if (Cbf)
	{
		Spi_CallFunc = Cbf;
	}
}


void __vector_12 (void) __attribute__((signal, used));
void __vector_12 (void)
{
	Dio_enuWriteChannel(1, DIO_u8HIGH);
	if (Spi_CallFunc)
	{
		Spi_CallFunc();
	}
}
