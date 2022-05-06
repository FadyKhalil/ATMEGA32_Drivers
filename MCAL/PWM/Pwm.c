/*
 * Pwm.c
 *
 *  Created on: Apr 23, 2022
 *      Author: fady
 */


#include "avr/io.h"
#include "../../Service/UTILITIES/Std_types.h"
#include "Pwm.h"
#include "Pwm_prv.h"


static u8 Pwm_ClockSlection[3];

Pwm_tenuErrorStatus Pwm_Init(const Pwm_ConfigType* ConfigPtr)
{

	Pwm_tenuErrorStatus Loc_enuErrorStatus = Pwm_enuOk;

	if(ConfigPtr)
	{
		/*TIMER 0 Configuration*/
		TCCR0 = ConfigPtr->Timer0_cfg.Mode | ConfigPtr->Timer0_cfg.CompareMatch_Mode;
		Pwm_ClockSlection[TIMER_0] = ConfigPtr->Timer0_cfg.ClockSelection;

		/*TIMER 1 Configuration*/
		TCCR1A = (ConfigPtr->Timer1_cfg.Mode & (LEAST_SIGNIFICANT_BIT)) | ConfigPtr->Timer1_cfg.CompareMatch_Mode_A << 2 | ConfigPtr->Timer1_cfg.CompareMatch_Mode_B;
		TCCR1B = (ConfigPtr->Timer1_cfg.Mode & (0x0C)) << 1;
		Pwm_ClockSlection[TIMER_1] = ConfigPtr->Timer1_cfg.ClockSelection;

		/*TIMER 2 Configuration*/
		TCCR2 = ConfigPtr->Timer2_cfg.Mode | ConfigPtr->Timer2_cfg.CompareMatch_Mode;
		Pwm_ClockSlection[TIMER_2] = ConfigPtr->Timer2_cfg.ClockSelection;


	}
	else
	{
		Loc_enuErrorStatus = Pwm_enuNullPointer;
	}

	return Loc_enuErrorStatus;
}

Pwm_tenuErrorStatus Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, u16 DutyCyclePercent)
{
	Pwm_tenuErrorStatus Loc_enuErrorStatus = Pwm_enuOk;

	switch(ChannelNumber)
	{

	case TIMER_0:

		if(TCCR0 & NON_INVERTED)
		{
			OCR0 = (u8)((DutyCyclePercent * MAX_TCNTO))/100;
		}
		else if(TCCR0 & INVERTED)
		{
			OCR0 = (u8)((25500 - (DutyCyclePercent*MAX_TCNTO)) / 100);
		}
		else
		{
			Loc_enuErrorStatus = Pwm_enuNotValidNumber;
		}
		TCCR0 = Pwm_ClockSlection[TIMER_0];
		break;

	case TIMER_1:

		if((TCCR1A & NON_INVERTED_A) || (TCCR1B & NON_INVERTED_B))
		{
			OCR1A = ((DutyCyclePercent * MAX_TCNT1)) / 100;
			OCR1B = ((DutyCyclePercent * MAX_TCNT1)) / 100;
		}

		else if((TCCR1A & INVERTED_A) || (TCCR1B & INVERTED_B))
		{
			OCR1A = (u16)((6553500 - (DutyCyclePercent*MAX_TCNT1)) / 100);
			OCR1A = (u16)((6553500 - (DutyCyclePercent*MAX_TCNT1)) / 100);
		}
		else
		{
			Loc_enuErrorStatus = Pwm_enuNotValidNumber;
		}

		TCCR1B = Pwm_ClockSlection[TIMER_1];

		break;

	case TIMER_2:

		if(TCCR0 & NON_INVERTED)
		{
			OCR2 = ((DutyCyclePercent * MAX_TCNT2)) / 100;
		}
		else if(TCCR0 & INVERTED)
		{
			OCR2 = (u8)((25500 - (DutyCyclePercent*MAX_TCNT2)) / 100);
		}
		else
		{
			Loc_enuErrorStatus = Pwm_enuNotValidNumber;
		}

		/*Enable clock on PWM*/
		TCCR2 = Pwm_ClockSlection[TIMER_2];

		break;

	default:

		Loc_enuErrorStatus = Pwm_enuNotValidChannel;

		break;
	}

	return Loc_enuErrorStatus;
}

Pwm_tenuErrorStatus Pwm_SetPeriodAndDuty(Pwm_PeriodType Period_ms, f32 DutyCyclePercent)
{
	static u8 Loc_u8InitClock = 0;

	Pwm_tenuErrorStatus Loc_enuErrorStatus = Pwm_enuOk;

	u64 Loc_u64TempValue;

	switch(Pwm_ClockSlection[TIMER_1])
	{

	case PWM_PREDEF_NO_PRESCALLER:

		Loc_u64TempValue = ((u64)((F_CLOCK) * Period_ms)) / 1000;
		if(Loc_u64TempValue > 0xFFFF)
		{
			Loc_enuErrorStatus = Pwm_enuNotValidNumber;
		}
		else
		{
			ICR1 = Loc_u64TempValue;
		}

		break;

	case PWM_PREDEF_8_PRESCALLER:

		Loc_u64TempValue = ((F_CLOCK/8) * Period_ms) / 1000;
		if(Loc_u64TempValue > 0xFFFF)
		{
			Loc_enuErrorStatus = Pwm_enuNotValidNumber;
		}
		else
		{
			ICR1 = Loc_u64TempValue;
		}

		break;

	case PWM_PREDEF_64_PRESCALLER:

		Loc_u64TempValue = ((u64)((F_CLOCK/64) * Period_ms)) / 1000;
		if(Loc_u64TempValue > 0xFFFF)
		{
			Loc_enuErrorStatus = Pwm_enuNotValidNumber;
		}
		else
		{
			ICR1 = Loc_u64TempValue;

		}

		break;

	case PWM_PREDEF_256_PRESCALLER:

		Loc_u64TempValue = ((F_CLOCK/256) * Period_ms) / 1000;
		if(Loc_u64TempValue > 0xFFFF)
		{
			Loc_enuErrorStatus = Pwm_enuNotValidNumber;
		}
		else
		{
			ICR1 = Loc_u64TempValue;
		}

		break;

	case PWM_PREDEF_1024_PRESCALLER:

		Loc_u64TempValue = ((F_CLOCK/1024) * Period_ms) / 1000;
		if(Loc_u64TempValue > 0xFFFF)
		{
			Loc_enuErrorStatus = Pwm_enuNotValidNumber;
		}
		else
		{
			ICR1 = Loc_u64TempValue;
		}

		break;
	}

	if((TCCR1A & NON_INVERTED_A))
	{
		OCR1A = (u64)(DutyCyclePercent * Loc_u64TempValue) / 100;
	}
	else if((TCCR1A & INVERTED_A))
	{
		OCR1A = (u16)((6553500 - (DutyCyclePercent*ICR1)) / 100);
	}
	if((TCCR1A & NON_INVERTED_B))
	{
		OCR1B = (u64)(DutyCyclePercent * Loc_u64TempValue) / 100;
	}

	else if((TCCR1A & INVERTED_B))
	{
		OCR1B = (u16)((6553500 - (DutyCyclePercent*ICR1)) / 100);
	}

	/*Enable clock on PWM*/
	if(Loc_u8InitClock == 0)
	{
		TCCR1B |= Pwm_ClockSlection[TIMER_1];
		Loc_u8InitClock = 1;
	}

	return Loc_enuErrorStatus;

}

