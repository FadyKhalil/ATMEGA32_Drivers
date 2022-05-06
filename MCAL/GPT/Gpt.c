/*
 * Timer.c
 *
 *  Created on: Apr 9, 2022
 *      Author: fady
 */

#include "../../Service/UTILITIES/Std_types.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "Gpt.h"
#include "../../MCAL/DIO/Dio.h"



#define GPT_MAX_VALUE_TIMER0 		0xFF
#define GPT_MAX_VALUE_TIMER1 		0xFFFF
#define GPT_MAX_VALUE_TIMER2 		0xFF

static CallBackFunc	Cbf;

static u8 Gpt_ClockSelection[3];

static u16 Gpt_NoOfOverflow[3] = {0};

Gpt_tenuErrorStatus Gpt_enuErrorStatus = GPT_enuOK;


void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{

	if (ConfigPtr == NULL)
	{
		Gpt_enuErrorStatus = GPT_E_PARAM_POINTER;
	}

	else
	{
		switch(ConfigPtr->Channel)
		{
			case TIMER0:
				TCCR0 = ConfigPtr->ForceOuptputCompare | ConfigPtr->WaveFormGeneration;
				TIMSK = ConfigPtr->EnableInterrupt;

				Gpt_ClockSelection[TIMER0] = ConfigPtr->ClockSelection;
				Gpt_NoOfOverflow[TIMER0] = ConfigPtr->NumberOfOverflow;
				break;

			case TIMER1:
				/*need to be edited in next version*/
				Gpt_ClockSelection[TIMER1] = ConfigPtr->ClockSelection;
				TCCR1B = ConfigPtr->ClockSelection | ConfigPtr->ForceOuptputCompare | ConfigPtr->WaveFormGeneration;
				TIMSK = ConfigPtr->EnableInterrupt << 2;
				Gpt_NoOfOverflow[TIMER1] = ConfigPtr->NumberOfOverflow;
				break;

			case TIMER2:
				Gpt_ClockSelection[TIMER2] = ConfigPtr->ClockSelection;
				TCCR2 = ConfigPtr->ClockSelection | ConfigPtr->ForceOuptputCompare | ConfigPtr->WaveFormGeneration;
				TIMSK = ConfigPtr->EnableInterrupt << 6;
				Gpt_NoOfOverflow[TIMER2] = ConfigPtr->NumberOfOverflow;
				break;

			default:

				Gpt_enuErrorStatus = GPT_E_PARAM_CHANNEL;

				break;

			}/*end of switch*/


	}/*end of else*/

}/*end of function Gpt_Init*/


Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
	u16 Value = 0;

	switch(Channel)
	{
	case TIMER0:
		Value = TCNT0;
		break;

	case TIMER1:
		Value = TCNT1H | TCNT1L;
		break;

	case TIMER2:
		Value = TCNT2;
		break;

	default:
		Gpt_enuErrorStatus =  GPT_E_PARAM_CHANNEL;
		break;

	}/*end of switch*/

	return Value;

}


Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
	u16 Value = ~(0);

		switch(Channel)
		{
		case TIMER0:
			Value = (u8)Value - TCNT0;
			break;

		case TIMER1:
			Value = (TCNT1H | TCNT1L);
			break;

		case TIMER2:
			Value = (u8)Value - TCNT2;
			break;

		default:
			Gpt_enuErrorStatus =  GPT_E_PARAM_CHANNEL;
			break;

		}/*end of switch*/

		return Value;
}

void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
	switch(Channel)
	{
	case TIMER0:
		if(Value > GPT_MAX_VALUE_TIMER0)
		{
			Gpt_enuErrorStatus = GPT_E_PARAM_VALUE;
		}/*end of if*/
		else
		{
			TCNT0 = Value;
			TCCR0 |= Gpt_ClockSelection[TIMER0];

		}/*end of else*/
		break;

	case TIMER1:
		if(Value > GPT_MAX_VALUE_TIMER1)
		{
			Gpt_enuErrorStatus = GPT_E_PARAM_VALUE;
		}/*end of if*/
		else
		{
			TCNT1 = Value;
			TCCR0 |= Gpt_ClockSelection[TIMER1];
		}/*end of else*/
		break;

	case TIMER2:
		if(Value > GPT_MAX_VALUE_TIMER2)
		{
			Gpt_enuErrorStatus = GPT_E_PARAM_VALUE;
		}/*end of if*/
		else
		{
			TCNT2 = Value;
			TCCR0 |= Gpt_ClockSelection[TIMER2];
		}/*end of else*/
		break;

	default:

		break;
	}/*end of switch*/

	/*enable General Interrupt*/
	SREG |= (1 << 7);

}/*end of function Gpt_StartTimer*/


void Gpt_Notification_TIMR0(CallBackFunc Caller)
{
	if(Caller == NULL)
	{
		Gpt_enuErrorStatus = GPT_E_PARAM_POINTER;
	}
	else
	{
		Cbf = Caller;

	}
}


ISR(TIMER0_OVF_vect)
{
	static u16 Loc_prvCounter = 0;

	if (Cbf == NULL)
	{
		Gpt_enuErrorStatus = GPT_E_PARAM_POINTER;
	}
	else
	{
		if(Loc_prvCounter == Gpt_NoOfOverflow[TIMER0])
		{
			Cbf();
			Loc_prvCounter = 0;
		}
		else
		{
			Loc_prvCounter++;
		}
	}
}


