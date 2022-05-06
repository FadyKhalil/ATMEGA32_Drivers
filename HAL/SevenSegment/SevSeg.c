/*
 * SevSeg.c
 *
 *  Created on: Apr 13, 2022
 *      Author: fady
 */


#include "../../Service/UTILITIES/Std_types.h"
#include "../../Service/UTILITIES/Bit_utils.h"
#include "../../MCAL/DIO/Dio.h"
#include "util/delay.h"
#include "SevSeg.h"
#include "SevSeg_cfg.h"


#define ZERO	0

extern SevSeg_Configuration ConfigPtr[];


static void SevSeg_DisplayAnode(u8 Copy_u8Number);

static void SevSeg_DisplayCathode(u8 Copy_u8Number);

static void SevSeg_vidTurnOn(u8 Copy_DisplayNumber);


u8 SevSeg_ArrayAnode [] =
{
		0x03,
		0x9f,
		0x25,
		0x0d,
		0x99,
		0x49,
		0x41,
		0x1f,
		0x01,
		0x19

};

u8 SevSeg_ArrayCathode [] =
{
		0xfc,
		0x60,
		0xda,
		0xf2,
		0x66,
		0xb6,
		0xbe,
		0xe0,
		0xfe,
		0xe6
};


void SevSeg_vidDisplayNumber(u16 Copy_u16Number)
{
	s8 Loc_u8Counter = 0;
	u8 Loc_u16TempNumber;

	while(Loc_u8Counter < NUMBER_OF_SEVEN_SEGMENT+1)
	{
		SevSeg_vidTurnOff(Loc_u8Counter - 1);
		Loc_u16TempNumber = Copy_u16Number % 10;


		if(ConfigPtr[Loc_u8Counter].Mode == ANODE)
		{
			SevSeg_DisplayAnode(Loc_u16TempNumber);

		}

		else
		{
			SevSeg_DisplayCathode(Loc_u16TempNumber);
		}

		SevSeg_vidTurnOn(Loc_u8Counter);
		Copy_u16Number = Copy_u16Number / 10;
		Loc_u8Counter++;
		_delay_us(1);

	}
}


void SevSeg_vidTurnOff(u8 Copy_DisplayNumber)
{

	if(Copy_DisplayNumber > NUMBER_OF_SEVEN_SEGMENT)
	{
		//return error
	}

	else
	{
		if(ConfigPtr[Copy_DisplayNumber].Mode == ANODE)
		{
			Dio_enuWriteChannel(ConfigPtr[Copy_DisplayNumber].PinEnable, DIO_u8LOW);
		}
		else
		{
			Dio_enuWriteChannel(ConfigPtr[Copy_DisplayNumber].PinEnable, DIO_u8HIGH);
		}
	}
}

/*************Implementation Private Function*********************/


static void SevSeg_vidTurnOn(u8 Copy_DisplayNumber)
{

	if(Copy_DisplayNumber > NUMBER_OF_SEVEN_SEGMENT)
	{
		//return error
	}

	else
	{
		if(ConfigPtr[Copy_DisplayNumber].Mode == ANODE)
		{
			Dio_enuWriteChannel(ConfigPtr[Copy_DisplayNumber].PinEnable, DIO_u8HIGH);

		}
		else
		{
			Dio_enuWriteChannel(ConfigPtr[Copy_DisplayNumber].PinEnable, DIO_u8LOW);
		}
	}
}


static void SevSeg_DisplayAnode(u8 Copy_u8Number)
{
	Dio_enuWriteChannel(SEVSEG_PINA, GET_BIT(SevSeg_ArrayAnode[Copy_u8Number], 7));
	Dio_enuWriteChannel(SEVSEG_PINB, GET_BIT(SevSeg_ArrayAnode[Copy_u8Number], 6));
	Dio_enuWriteChannel(SEVSEG_PINC, GET_BIT(SevSeg_ArrayAnode[Copy_u8Number], 5));
	Dio_enuWriteChannel(SEVSEG_PIND, GET_BIT(SevSeg_ArrayAnode[Copy_u8Number], 4));
	Dio_enuWriteChannel(SEVSEG_PINE, GET_BIT(SevSeg_ArrayAnode[Copy_u8Number], 3));
	Dio_enuWriteChannel(SEVSEG_PINF, GET_BIT(SevSeg_ArrayAnode[Copy_u8Number], 2));
	Dio_enuWriteChannel(SEVSEG_PING, GET_BIT(SevSeg_ArrayAnode[Copy_u8Number], 1));
	Dio_enuWriteChannel(SEVSEG_PINH, GET_BIT(SevSeg_ArrayAnode[Copy_u8Number], 0));
}


static void SevSeg_DisplayCathode(u8 Copy_u8Number)
{
	Dio_enuWriteChannel(SEVSEG_PINA, GET_BIT(SevSeg_ArrayCathode[Copy_u8Number], 7));
	Dio_enuWriteChannel(SEVSEG_PINB, GET_BIT(SevSeg_ArrayCathode[Copy_u8Number], 6));
	Dio_enuWriteChannel(SEVSEG_PINC, GET_BIT(SevSeg_ArrayCathode[Copy_u8Number], 5));
	Dio_enuWriteChannel(SEVSEG_PIND, GET_BIT(SevSeg_ArrayCathode[Copy_u8Number], 4));
	Dio_enuWriteChannel(SEVSEG_PINE, GET_BIT(SevSeg_ArrayCathode[Copy_u8Number], 3));
	Dio_enuWriteChannel(SEVSEG_PINF, GET_BIT(SevSeg_ArrayCathode[Copy_u8Number], 2));
	Dio_enuWriteChannel(SEVSEG_PING, GET_BIT(SevSeg_ArrayCathode[Copy_u8Number], 1));
	Dio_enuWriteChannel(SEVSEG_PINH, GET_BIT(SevSeg_ArrayCathode[Copy_u8Number], 0));
}



