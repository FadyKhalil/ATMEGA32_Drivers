/*
 * Icu.c
 *
 *  Created on: May 1, 2022
 *      Author: fady
 */


#include "../../Service/UTILITIES/Std_types.h"
#include "avr/io.h"
#include "Icu.h"




/********static variable********/
static Icu_CallFunc Callfunc;


void Icu_vidInit(void)
{
	/*Initialize the input capture at rising edge*/
	TCCR1B |= (1 << 6);

	/*Enbale Interrupt*/
	TIMSK |= (1 << 5);

	/*Enable Clock*/
	TCCR1B |= 3;
}

void Icu_vidRegisterCallBack(Icu_CallFunc Cbf)
{
	if(Cbf)
	{
		Callfunc = Cbf;
	}
}

void Icu_vidEnableInterrupt(void)
{
	/*Enbale Interrupt*/
	TIMSK |= (1 << 5);
}

void Icu_vidDisableInterrupt(void)
{
	/*Disable Interrupt*/
	TIMSK &= ~(1 << 5);
}

void Icu_vidChangeTrigger(Icu_Edge Copy_u8TriggerSource)
{
	switch(Copy_u8TriggerSource)
	{
	case Icu_Edge_Falling:
		TCCR1B &= ~(1 << 6);
		break;

	case Icu_Edge_Rising:
		TCCR1B |= (1 << 6);
		break;

	}
}

void Icu_vidReadValue(pu16 Add_pu16Value)
{
	*Add_pu16Value = ICR1;
}


void __vector_6 (void) __attribute__ ((signal, used));
void __vector_6 (void)
{
	if(Callfunc)
	{
		Callfunc();
	}
	else
	{
		//return error
	}
}



