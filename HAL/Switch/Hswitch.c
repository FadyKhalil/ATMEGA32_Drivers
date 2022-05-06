/*
 * Hswitch.c
 *
 *  Created on: Apr 13, 2022
 *      Author: fady
 */


#include "../../Service/UTILITIES/Std_types.h"
#include "../../MCAL/DIO/Dio.h"
#include "Hswitch.h"
#include "Hswitch_cfg.h"

static u8 ButtonStatus[NUMBER_OF_SWITCH] = {1, 1, 1};

extern Switch_Configuration SwitchConfig[];


void Switch_ReadStatus(u8 Copy_u8SwitchNumber, pu8 Add_pu8Value)
{

	if(Add_pu8Value == NULL)
	{
		//error
	}
	else
	{
		*Add_pu8Value = ButtonStatus[Copy_u8SwitchNumber];
	}

}



void Switch_vidTask(void)
{
	u8 Loc_u8Iterator = 0;
	u8 Loc_u8CurrentValue;
	static u8 Loc_u8PrvValue[NUMBER_OF_SWITCH];
	static u8 Loc_u8Counter[NUMBER_OF_SWITCH];

	for(Loc_u8Iterator = 0; Loc_u8Iterator < NUMBER_OF_SWITCH; Loc_u8Iterator++)
	{
		Dio_enuReadChannel(SwitchConfig[Loc_u8Iterator].SwitchNumber, &Loc_u8CurrentValue);

		if(Loc_u8CurrentValue == Loc_u8PrvValue[Loc_u8Iterator])
		{
			Loc_u8Counter[Loc_u8Iterator]++;
		}
		else
		{
			Loc_u8Counter[Loc_u8Iterator] = 0;
		}

		if(Loc_u8Counter[Loc_u8Iterator] == 5)
		{
			ButtonStatus[Loc_u8Iterator] = Loc_u8CurrentValue;
			Loc_u8Counter[Loc_u8Iterator] = 0;
		}

		Loc_u8PrvValue[Loc_u8Iterator] = Loc_u8CurrentValue;
	}
}
