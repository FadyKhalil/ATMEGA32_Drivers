/*
 * Ext.c
 *
 *  Created on: Apr 16, 2022
 *      Author: fady
 */

#include "avr/io.h"
#include "avr/interrupt.h"
#include "../../Service/UTILITIES/Std_types.h"
#include "Ext.h"

static Ext_Callfunc CallFunc[3] = 0;


Ext_tenuErrorStatus Ext_vidInit(Ext_Config* ConfigPtr)
{
	Ext_tenuErrorStatus Loc_enuErrorStatus = Ext_enuOk;

	if(ConfigPtr == NULL)
	{
		Loc_enuErrorStatus = Ext_enuNullPointer;
	}
	else
	{

	MCUCR = ConfigPtr->INT0_Mode;
	MCUCR = ConfigPtr->INT1_Mode << 2;
	MCUCSR = ConfigPtr->INT2_Mode << 6;


	GICR = ConfigPtr->INT0_Int << 7 | ConfigPtr->INT1_Int << 6 | ConfigPtr->INT2_Int << 5;

	}

	return Loc_enuErrorStatus;

}

Ext_tenuErrorStatus Ext_RegisterCallFunction(Int_ID Channel, Ext_Callfunc Cbf)
{
	Ext_tenuErrorStatus Loc_enuErrorStatus = Ext_enuOk;

	if(Cbf == NULL)
	{
		Loc_enuErrorStatus = Ext_enuNullPointer;
	}
	else
	{
		CallFunc[Channel] = Cbf;
	}

	return Loc_enuErrorStatus;
}


ISR(INT0_vect)
{
	if(CallFunc[EXT_INT_0] == NULL)
	{
		//Do Nothing
	}
	else
	{
		CallFunc[EXT_INT_0]();
	}

}

ISR(INT1_vect)
{
	if(CallFunc[EXT_INT_1] == NULL)
	{
		//Do Nothing
	}
	else
	{
		CallFunc[EXT_INT_1]();
	}

}

ISR(INT2_vect)
{
	if(CallFunc[EXT_INT_2] == NULL)
	{
		//Do Nothing
	}
	else
	{
		CallFunc[EXT_INT_2]();
	}

}
