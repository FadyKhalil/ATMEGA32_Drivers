/*
 * PotMet.c
 *
 *  Created on: Apr 30, 2022
 *      Author: fady
 */


#include "../../Service/UTILITIES/Std_types.h"
#include "PotMet.h"
#include "../../MCAL/ADC/Adc.h"
#include "../../MCAL/DIO/Dio.h"

#define POT_MAGIC_CHECKING_READING_PIN		0x300



u16 PotMet_vidReadValue(u16 Copy_u16PinNumber)
{
	u16 Loc_u16TempValue;

	if (!(Copy_u16PinNumber & POT_MAGIC_CHECKING_READING_PIN))
	{
		//Do Nothing
	}
	else
	{
		Adc_enuStartConversionSynch(Copy_u16PinNumber, &Loc_u16TempValue);
	}

	return Loc_u16TempValue;

}


