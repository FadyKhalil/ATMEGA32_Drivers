/*
 * Port.c
 *
 *  Created on: Mar 5, 2022
 *      Author: fady
 */

#include "avr/io.h"
#include "../../Service/UTILITIES/Std_types.h"
#include "../../Service/UTILITIES/Bit_utils.h"
#include "Port.h"
#include "Port_prv.h"
#include "Port_cfg.h"


/* this function is initialization function where the user can configure all his pin mode from <Configuration file>
 * @ this function does not take any input
 * */
void PORT_vidInit(void)
{

#undef PORT_u8OUTPUT_HIGH
#undef PORT_u8INPUT_PULLUP
#undef PORT_u8OUTPUT_LOW
#undef PORT_u8INPUT_IMPEDENCE
#define PORT_u8OUTPUT_HIGH 		1
#define PORT_u8INPUT_PULLUP		0
#define PORT_u8OUTPUT_LOW		1
#define PORT_u8INPUT_IMPEDENCE	0
	DDRA = CONC(PORT_u8MODEPIN07, PORT_u8MODEPIN06, PORT_u8MODEPIN05,
			PORT_u8MODEPIN04, PORT_u8MODEPIN03, PORT_u8MODEPIN02,
			PORT_u8MODEPIN01, PORT_u8MODEPIN00);
	DDRB = CONC(PORT_u8MODEPIN15, PORT_u8MODEPIN14, PORT_u8MODEPIN13,
			PORT_u8MODEPIN12, PORT_u8MODEPIN11, PORT_u8MODEPIN10,
			PORT_u8MODEPIN09, PORT_u8MODEPIN08);
	DDRC = CONC(PORT_u8MODEPIN23, PORT_u8MODEPIN22, PORT_u8MODEPIN21,
			PORT_u8MODEPIN20, PORT_u8MODEPIN19, PORT_u8MODEPIN18,
			PORT_u8MODEPIN17, PORT_u8MODEPIN16);
	DDRD = CONC(PORT_u8MODEPIN31, PORT_u8MODEPIN30, PORT_u8MODEPIN29,
			PORT_u8MODEPIN28, PORT_u8MODEPIN27, PORT_u8MODEPIN26,
			PORT_u8MODEPIN25, PORT_u8MODEPIN24);
#undef PORT_u8OUTPUT_HIGH
#undef PORT_u8INPUT_PULLUP
#undef PORT_u8OUTPUT_LOW
#undef PORT_u8INPUT_IMPEDENCE
#define PORT_u8OUTPUT_HIGH 		1
#define PORT_u8INPUT_PULLUP		1
#define PORT_u8OUTPUT_LOW		0
#define PORT_u8INPUT_IMPEDENCE	0
	PORTA = CONC(PORT_u8MODEPIN07, PORT_u8MODEPIN06, PORT_u8MODEPIN05,
			PORT_u8MODEPIN04, PORT_u8MODEPIN03, PORT_u8MODEPIN02,
			PORT_u8MODEPIN01, PORT_u8MODEPIN00);
	PORTB = CONC(PORT_u8MODEPIN15, PORT_u8MODEPIN14, PORT_u8MODEPIN13,
			PORT_u8MODEPIN12, PORT_u8MODEPIN11, PORT_u8MODEPIN10,
			PORT_u8MODEPIN09, PORT_u8MODEPIN08);
	PORTC = CONC(PORT_u8MODEPIN23, PORT_u8MODEPIN22, PORT_u8MODEPIN21,
			PORT_u8MODEPIN20, PORT_u8MODEPIN19, PORT_u8MODEPIN18,
			PORT_u8MODEPIN17, PORT_u8MODEPIN16);
	PORTD = CONC(PORT_u8MODEPIN31, PORT_u8MODEPIN30, PORT_u8MODEPIN29,
			PORT_u8MODEPIN28, PORT_u8MODEPIN27, PORT_u8MODEPIN26,
			PORT_u8MODEPIN25, PORT_u8MODEPIN24);
#undef PORT_u8OUTPUT_HIGH
#undef PORT_u8INPUT_PULLUP
#undef PORT_u8OUTPUT_LOW
#undef PORT_u8INPUT_IMPEDENCE
#define PORT_u8OUTPUT_HIGH 		2
#define PORT_u8OUTPUT_LOW 		3
#define PORT_u8INPUT_PULLUP 	4
#define PORT_u8INPUT_IMPEDENCE 	5

}


/*!
 * @Port_enuSetPinDirection is to make the user set his pin direction during the initialization
 *
 * @This function take two input
 *
 * -> Pin number
 * -> Direction
 *
 * */

Port_tenuErrorStatus Port_enuSetPinDirection(u8 Copy_u8PinNum,
		u8 Copy_u8PinDirection)
{
	Port_tenuErrorStatus Loc_enuReturnStatus = Port_enuOK;

	u8 Loc_u8Port;
	u8 Loc_u8Pin;

	if (Copy_u8PinNum > PORT_PINCOUNT)
	{
		Loc_enuReturnStatus = Port_enuPinError;
	}
	else if ((Copy_u8PinDirection != PORT_u8OUTPUT)
			&& (Copy_u8PinDirection != PORT_u8INPUT))
	{
		Loc_enuReturnStatus = Port_enuDirError;
	}
	else
	{
		Loc_u8Port = Copy_u8PinNum / PORT_PORTSIZE;
		Loc_u8Pin = Copy_u8PinNum % PORT_PORTSIZE;

		switch (Loc_u8Port)
		{
		/*Port A*/
		case PORT_PORTA:
			if (Copy_u8PinDirection == PORT_u8OUTPUT)
			{
				SET_BIT(DDRA, Loc_u8Pin);
			}
			else
			{
				CLR_BIT(DDRA, Loc_u8Pin);
			}
			break;
			/*Port B*/
		case PORT_PORTB:
			if (Copy_u8PinDirection == PORT_u8OUTPUT)
			{
				SET_BIT(DDRB, Loc_u8Pin);
			}
			else
			{
				CLR_BIT(DDRB, Loc_u8Pin);
			}
			break;
			/*Port C*/
		case PORT_PORTC:
			if (Copy_u8PinDirection == PORT_u8OUTPUT)
			{
				SET_BIT(DDRC, Loc_u8Pin);
			}
			else
			{
				CLR_BIT(DDRC, Loc_u8Pin);
			}
			break;
			/*Port D*/
		case PORT_PORTD:
			if (Copy_u8PinDirection == PORT_u8OUTPUT)
			{
				SET_BIT(DDRD, Loc_u8Pin);
			}
			else
			{
				CLR_BIT(DDRD, Loc_u8Pin);
			}
			break;

		default:
			break;
		}
	}

	return Loc_enuReturnStatus;
}

/*SET PIN MODE FUNCTION
 *
 * @ Pin NUMBER
 * @ Pin MODE (Direction && Mode)
 * */
Port_tenuErrorStatus Port_enuSetPinMode(u8 Copy_u8PinNum, u8 Copy_u8PinMode)
{
	Port_tenuErrorStatus Loc_enuReturnStatus = Port_enuOK;

	u8 Loc_u8Port;
	u8 Loc_u8Pin;

	if (Copy_u8PinNum > PORT_PINCOUNT)
	{
		Loc_enuReturnStatus = Port_enuPinError;
	}
	else if ((Copy_u8PinMode > 5) && (Copy_u8PinMode < 2))
	{
		Loc_enuReturnStatus = Port_enuModeError;
	}
	else
	{
		Loc_u8Port = Copy_u8PinNum / 8;
		Loc_u8Pin = Copy_u8PinNum % 8;

		switch (Loc_u8Port)
		{
		/*Port A*/
		case PORT_PORTA:
			switch (Loc_u8Pin)
			{
			case PORT_u8OUTPUT_HIGH:
				SET_BIT(DDRA, Loc_u8Pin);
				SET_BIT(PORTA, Loc_u8Pin);
				break;

			case PORT_u8OUTPUT_LOW:
				SET_BIT(DDRA, Loc_u8Pin);
				CLR_BIT(PORTA, Loc_u8Pin);
				break;

			case PORT_u8INPUT_PULLUP:
				CLR_BIT(DDRA, Loc_u8Pin);
				SET_BIT(PORTA, Loc_u8Pin);
				break;

			case PORT_u8INPUT_IMPEDENCE:
				CLR_BIT(DDRA, Loc_u8Pin);
				CLR_BIT(PORTA, Loc_u8Pin);
				break;

			default:
				break;
			}
			break;
			/*Port B*/
		case PORT_PORTB:
			switch (Loc_u8Pin)
			{
			case PORT_u8OUTPUT_HIGH:
				SET_BIT(DDRB, Loc_u8Pin);
				SET_BIT(PORTB, Loc_u8Pin);
				break;

			case PORT_u8OUTPUT_LOW:
				SET_BIT(DDRB, Loc_u8Pin);
				CLR_BIT(PORTB, Loc_u8Pin);
				break;

			case PORT_u8INPUT_PULLUP:
				CLR_BIT(DDRB, Loc_u8Pin);
				SET_BIT(PORTB, Loc_u8Pin);
				break;

			case PORT_u8INPUT_IMPEDENCE:
				CLR_BIT(DDRB, Loc_u8Pin);
				CLR_BIT(PORTB, Loc_u8Pin);
				break;

			default:
				break;
			}
			break;
			/*PORT C*/
		case PORT_PORTC:
			switch (Loc_u8Pin)
			{
			case PORT_u8OUTPUT_HIGH:
				SET_BIT(DDRC, Loc_u8Pin);
				SET_BIT(PORTC, Loc_u8Pin);
				break;

			case PORT_u8OUTPUT_LOW:
				SET_BIT(DDRC, Loc_u8Pin);
				CLR_BIT(PORTC, Loc_u8Pin);
				break;

			case PORT_u8INPUT_PULLUP:
				CLR_BIT(DDRC, Loc_u8Pin);
				SET_BIT(PORTC, Loc_u8Pin);
				break;

			case PORT_u8INPUT_IMPEDENCE:
				CLR_BIT(DDRC, Loc_u8Pin);
				CLR_BIT(PORTC, Loc_u8Pin);
				break;

			default:
				break;
			}
			break;
			/*Port D*/
		case PORT_PORTD:
			switch (Loc_u8Pin)
			{
			case PORT_u8OUTPUT_HIGH:
				SET_BIT(DDRD, Loc_u8Pin);
				SET_BIT(PORTD, Loc_u8Pin);
				break;

			case PORT_u8OUTPUT_LOW:
				SET_BIT(DDRD, Loc_u8Pin);
				CLR_BIT(PORTD, Loc_u8Pin);
				break;

			case PORT_u8INPUT_PULLUP:
				CLR_BIT(DDRD, Loc_u8Pin);
				SET_BIT(PORTD, Loc_u8Pin);
				break;

			case PORT_u8INPUT_IMPEDENCE:
				CLR_BIT(DDRD, Loc_u8Pin);
				CLR_BIT(PORTD, Loc_u8Pin);
				break;

			default:
				break;
			}
			break;

		}
	}

	return Loc_enuReturnStatus;
}

