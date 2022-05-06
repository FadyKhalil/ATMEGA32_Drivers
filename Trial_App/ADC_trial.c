/*
 * main.c
 *
 *  Created on: Apr 28, 2022
 *      Author: fady
 */

#include "Service/UTILITIES/Std_types.h"
#include "Service/UTILITIES/Bit_utils.h"
#include "MCAL/PORT/Port.h"
#include "MCAL/ADC/Adc.h"
#include "HAL/Potentiometer/PotMet.h"
#include "MCAL/DIO/Dio.h"

int main(void)
{
	u16 Loc_u16Value;

	PORT_vidInit();

	Adc_vidInit();


	while(1)
	{

		Adc_enuStartConversionSynch(ADC_PIN01, &Loc_u16Value);

		if(Loc_u16Value < 255)
		{
			Dio_enuWriteChannel(10, DIO_u8HIGH);
		}

		else if(Loc_u16Value < 755)
		{
			Dio_enuWriteChannel(11, DIO_u8HIGH);
		}

		else if(Loc_u16Value < 1200)
		{
			Dio_enuFlipChannel(12);
		}

	}

	return 0;
}
