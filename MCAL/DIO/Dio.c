/*
 * Dio.c
 *
 *  Created on: Mar 6, 2022
 *      Author: fady
 */

#include "avr/io.h"
#include "../../Service/UTILITIES/Bit_utils.h"
#include "../../Service/UTILITIES/Std_types.h"
#include "Dio.h"
#include "Dio_prv.h"

Dio_tenuErrorStatus Dio_enuWriteChannel(u8 Copy_u8ChannelId, u8 Copy_u8Level)
{

	u8 Loc_u8Port;
	u8 Loc_u8Pin;

	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;

	if (Copy_u8ChannelId > DIO_PINSIZENUMBER)
	{
		Loc_enuReturnStatus = Dio_enuChanneIdlError;

	}
	else if ((Copy_u8Level != DIO_u8HIGH) && (Copy_u8Level != DIO_u8LOW))
	{
		Loc_enuReturnStatus = Dio_enuLevelError;
	}
	else
	{
		Loc_u8Port = Copy_u8ChannelId / DIO_PORTREGISTERSIZE;
		Loc_u8Pin = Copy_u8ChannelId % DIO_PORTREGISTERSIZE;

		switch (Loc_u8Port)
		{
		/*PORT A*/
		case DIO_PORTA:
			if (Copy_u8Level == DIO_u8HIGH)
			{
				SET_BIT(PORTA, Loc_u8Pin);
			}

			else if(Copy_u8Level == DIO_u8LOW)
			{
				CLR_BIT(PORTA, Loc_u8Pin);
			}
			break;
			/*PORT B*/
		case DIO_PORTB:
			if (Copy_u8Level == DIO_u8HIGH)
			{
				SET_BIT(PORTB, Loc_u8Pin);
			}
			else
			{
				CLR_BIT(PORTB, Loc_u8Pin);
			}
			break;
			/*PORT C*/
		case DIO_PORTC:
			if (Copy_u8Level == DIO_u8HIGH)
			{
				SET_BIT(PORTC, Loc_u8Pin);
			}
			else
			{
				CLR_BIT(PORTC, Loc_u8Pin);
			}
			break;
			/*PORT D*/
		case DIO_PORTD:
			if (Copy_u8Level == DIO_u8HIGH)
			{
				SET_BIT(PORTD, Loc_u8Pin);
			}
			else
			{
				CLR_BIT(PORTD, Loc_u8Pin);
			}
			break;
		default:
			break;
		}
	}
	return Loc_enuReturnStatus;
}

Dio_tenuErrorStatus Dio_enuReadChannel(u8 Copy_u8ChannelId,
		pu8 Add_pu8ChannelLevel)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;
	u8 Loc_u8Port;
	u8 Loc_u8Pin;

	if (Copy_u8ChannelId > DIO_PINSIZENUMBER)
	{
		Loc_enuReturnStatus = Dio_enuChanneIdlError;
	}

	/*NULL ERORR PLEASE CHECK*/
	else if (Add_pu8ChannelLevel == 0)
	{
		Loc_enuReturnStatus = Dio_enuLevelError;
	}
	else
	{
		Loc_u8Port = Copy_u8ChannelId / DIO_PORTREGISTERSIZE;
		Loc_u8Pin = Copy_u8ChannelId % DIO_PORTREGISTERSIZE;

		switch (Loc_u8Port)
		{
		/*PORT A*/
		case DIO_PORTA:
			*Add_pu8ChannelLevel = GET_BIT(PINA, Loc_u8Pin);
			break;

		case DIO_PORTB:
			*Add_pu8ChannelLevel = GET_BIT(PINB, Loc_u8Pin);
			break;

		case DIO_PORTC:
			*Add_pu8ChannelLevel = GET_BIT(PINC, Loc_u8Pin);
			break;

		case DIO_PORTD:
			*Add_pu8ChannelLevel = GET_BIT(PIND, Loc_u8Pin);
			break;

		default:
			break;

		}

	}
	return Loc_enuReturnStatus;
}

Dio_tenuErrorStatus Dio_enuWritePort(u8 Copy_u8PortId, u8 Copy_u8Value)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;

	if (Copy_u8PortId > 3)
	{
		Loc_enuReturnStatus = Dio_enuPortIdlError;
	}
	else
	{
		switch (Copy_u8PortId)
		{
		case DIO_PORTA:
			ASSIGN_REG(PORTA, Copy_u8Value);
			break;

		case DIO_PORTB:
			ASSIGN_REG(PORTB, Copy_u8Value);
			break;

		case DIO_PORTC:
			ASSIGN_REG(PORTC, Copy_u8Value);
			break;

		case DIO_PORTD:
			ASSIGN_REG(PORTD, Copy_u8Value);
			break;

		default:
			break;
		}
	}

	return Loc_enuReturnStatus;
}

Dio_tenuErrorStatus Dio_enuReadPort(u8 Copy_u8PortId, pu8 Add_pu8Level)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;

	if (Copy_u8PortId > 3)
	{
		Loc_enuReturnStatus = Dio_enuChanneIdlError;
	}
	else if (Add_pu8Level == 0)
	{
		Loc_enuReturnStatus = Dio_enuLevelError;
	}
	else
	{

		switch (Copy_u8PortId)
		{
		case DIO_PORTA:
			*Add_pu8Level = PORTA;
			break;
		case DIO_PORTB:
			*Add_pu8Level = PORTB;
			break;
		case DIO_PORTC:
			*Add_pu8Level = PORTC;
			break;
		case DIO_PORTD:
			*Add_pu8Level = PORTD;
			break;
		}

	}

	return Loc_enuReturnStatus;

}

Dio_tenuErrorStatus Dio_enuFlipChannel(u8 Copy_u8ChannelId)
{
	Dio_tenuErrorStatus Loc_enuReturnStatus = Dio_enuOK;
	u8 Loc_u8Port;
	u8 Loc_u8Pin;

	if (Copy_u8ChannelId > DIO_PINSIZENUMBER)
	{
		Loc_enuReturnStatus = Dio_enuChanneIdlError;
	}
	else
	{
		Loc_u8Port = Copy_u8ChannelId / DIO_PORTREGISTERSIZE;
		Loc_u8Pin = Copy_u8ChannelId % DIO_PORTREGISTERSIZE;

		switch(Loc_u8Port)
		{
		case DIO_PORTA:
			TGL_BIT(PORTA, Loc_u8Pin);
			break;
		case DIO_PORTB:
			TGL_BIT(PORTB, Loc_u8Pin);
			break;
		case DIO_PORTC:
			TGL_BIT(PORTC, Loc_u8Pin);
			break;
		case DIO_PORTD:
			TGL_BIT(PORTD, Loc_u8Pin);
			break;
		}
	}

	return Loc_enuReturnStatus;
}

