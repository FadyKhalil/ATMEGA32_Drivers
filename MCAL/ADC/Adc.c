/*
 * Adc.c
 *
 *  Created on: Mar 25, 2022
 *      Author: fady
 */


#include "../../Service/UTILITIES/Std_types.h"
#include "../../Service/UTILITIES/Bit_utils.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "Adc_cfg.h"
#include "Adc.h"




#define ADC_MAGIC_CHECKING_INTERRUPT		0x100
#define	ADD_MAGIC_CHECKING_CONVERSION		0x200
#define ADC_MAGIC_CHECKING_READING_PIN		0x300


#define ADC_VOLTAGE_REFERENCE_EXTERNAL		0x00
#define ADC_VOLTAGE_AVCC 					0x40
#define ADC_VOLTAGE_INTERNAL          		0xC0

#define ADC_RIGHT_SHIFT						0x00
#define ADC_LEFT_SHIFT						0x20


#define ADC_DEVISION_2						0x00
#define ADC_DEVISION_4   					0x02
#define ADC_DEVISION_8   					0x03
#define ADC_DEVISION_16  					0x04
#define ADC_DEVISION_32  					0x05
#define ADC_DEVISION_64  					0x06
#define ADC_DEVISION_128 					0x07


#define ADC_ON								0x80
#define	ADC_OFF								0x00



/*Function like macro for synchronous conversion*/
#define  Adc_CheckConversion	do{ 	u8 Loc_u8Counter;\
										while (GET_BIT(ADCSRA, 4) == 0)\
										{\
											Loc_u8Counter++;\
										}\
									}\
									while(0)

/*private variable*/
enum
{
	BUZY,
	IDLE
};

static u8 ADC_u8BusyState = IDLE;

static Chain_t Adc_prvChain;

static u8 Adc_u8IndexConversion = 0;

/*******************/

void Adc_vidInit(void)
{
	u8 Loc_u8TempRegister = 0;

	/*Adc voltage reference*/
	Loc_u8TempRegister |= ADC_u8VOLTAGE_REFERENCE;

	/*Adc left or right adjustment*/
	Loc_u8TempRegister |= ADC_u8ADLAR;

	/*Store and initialize the ADMUX*/
	ADMUX = Loc_u8TempRegister;

	/*Store the register value in Local variable*/
	Loc_u8TempRegister = ADCSRA;

	/*Clear the Prescalerr*/
	Loc_u8TempRegister &= ~(0x07);

	/*initialize the new Prescaler*/
	Loc_u8TempRegister |= ADC_u8PRESCALER;

	/*Enbale ADC*/
	Loc_u8TempRegister |= ADC_STATUS;

	/*store the variable in register*/
	ADCSRA = Loc_u8TempRegister;

//	SET_BIT(ADCSRA, 4);

	return;
}

Adc_tenuErrorStatus Adc_enuInterruptStatus(u16 Copy_u16StatusValue)
{
	Adc_tenuErrorStatus Loc_enuErrorStatus = ADC_enuOk;
	if (Copy_u16StatusValue & ADC_MAGIC_CHECKING_INTERRUPT)
	{
		Copy_u16StatusValue = (u8)Copy_u16StatusValue;
		ADCSRA |= Copy_u16StatusValue;
	}
	else
	{
		Loc_enuErrorStatus = ADC_enuErrorValue;
	}

	return Loc_enuErrorStatus;
}


/*
 * Function name:	Adc_enuStartConversionSynch
 *
 * Descripton:		This function start conversion in synchronous way
 * 					will not return until it finsih Conversion
 *
 * Parameters:		Copy_u16PinNumber	-->		in Range{ADC_PIN00, ADC_PIN01, ADC_PIN02, ADC_PIN03, ADC_PIN04, ADC_PIN05, ADC_PIN06, ADC_PIN07}
 * 					Add_pu16Value		--> 	Value to return the Digital Value
 *
 * Return:			ErrorStatus
 *
 * */
Adc_tenuErrorStatus Adc_enuStartConversionSynch(u16 Copy_u16PinNumber, pu16 Add_pu16Value)
{
	u8 Loc_u8TempRegister = 0;
	Adc_tenuErrorStatus Loc_enuErrorStatus = ADC_enuOk;

	if (!(Copy_u16PinNumber & ADC_MAGIC_CHECKING_READING_PIN))
	{
		Loc_enuErrorStatus = ADC_enuErrorValue;
	}
	else if(Add_pu16Value == (void*)0)
	{
			Loc_enuErrorStatus = ADC_enuNullPointer;
	}
	else
	{
		/*after check with number
		 * casting the variable to u8
		 * */
		Copy_u16PinNumber = (u8)Copy_u16PinNumber;

		Loc_u8TempRegister = ADMUX;
		Loc_u8TempRegister &= 0xF8;
		Loc_u8TempRegister |= Copy_u16PinNumber;


		/*Channel usage*/
		ADMUX = Loc_u8TempRegister;

		/*Start Conversion*/
		SET_BIT(ADCSRA, 6);

		/*Function Like Macro*/
		Adc_CheckConversion;

#if ADC_u8ADLAR == ADC_RIGHT_SHIFT

		*Add_pu16Value = (ADCL) | (ADCH << 8);

#elif ADC_u8ADLAR == ADC_LEFT_SHIFT

		*Add_pu16Value = (ADCL >> 8) | (ADCH << 2);

#endif
		SET_BIT(ADCSRA, 4);

		}

	return Loc_enuErrorStatus;
}


Adc_tenuErrorStatus Adc_enuStartConversionAsynch(u16 Copy_u16PinNumber, pu16 Add_pu16Value, CallNotification Cbf)
{
	u8 Loc_u8TempRegister = 0;
	Adc_tenuErrorStatus Loc_enuErrorStatus = ADC_enuOk;

	if (!(Copy_u16PinNumber & ADC_MAGIC_CHECKING_READING_PIN))
	{
		Loc_enuErrorStatus = ADC_enuErrorValue;
	}
	if(Add_pu16Value == (void*)0)
	{
			Loc_enuErrorStatus = ADC_enuNullPointer;
	}
	else
	{
		if(ADC_u8BusyState == IDLE)
		{
			ADC_u8BusyState = BUZY;
			/*after check with number
			 * casting the variable to u8
			 * */
			Copy_u16PinNumber = (u8)Copy_u16PinNumber;

			Loc_u8TempRegister = ADMUX;
			Loc_u8TempRegister &= ~(0x1F);
			Loc_u8TempRegister |= Copy_u16PinNumber;

			/*Channel usage*/
			ADMUX = Loc_u8TempRegister;

			/*Reset the Index Conversion to ZERO*/
			Adc_u8IndexConversion = 0;

			/*Store the call back function to global private value*/
			Adc_prvChain.Notification = Cbf;

			/*store the address of the value return*/
			Adc_prvChain.Result = Add_pu16Value;

			/*Store the size to 0*/
			Adc_prvChain.Size = 0;

			/*Start Conversion*/
			SET_BIT(ADCSRA, 4);

			/*Enable Interrupt*/
			Adc_enuInterruptStatus(ADC_ENABLE_INTERRUPT);


		}
		else
		{
			Loc_enuErrorStatus = BUZY;
		}
	}

	return Loc_enuErrorStatus;
}



Adc_tenuErrorStatus Adc_tenuStartChainAsynch(Chain_t* Add_tChain)
{
	Adc_tenuErrorStatus Loc_enuErrorStatus = ADC_enuOk;
	u8 Loc_u8TempRegister;

	/*check pointer to null*/
	if(Add_tChain == NULL)
	{
		Loc_enuErrorStatus = ADC_enuNullPointer;
	}
	else
	{
		if(ADC_u8BusyState == IDLE)
		{
			ADC_u8BusyState = BUZY;

			/* Register all notification
			 * 		&
			 * Channel used
			 * */
			Adc_prvChain.Channel = Add_tChain->Channel;
			Adc_prvChain.Notification = Add_tChain->Notification;
			Adc_prvChain.Size = Add_tChain->Size;
			Adc_prvChain.Result = Add_tChain->Result;

			Adc_u8IndexConversion = 0;

			Loc_u8TempRegister = ADMUX;
			Loc_u8TempRegister &= 0b11100000;
			Loc_u8TempRegister |= Adc_prvChain.Channel[0];

			/*Usage Channel*/
			ADMUX = Loc_u8TempRegister;

			/*start conversion*/
			SET_BIT(ADCSRA, ADSC);

		}

		else
		{
			Loc_enuErrorStatus = BUZY;
		}
	}


	return Loc_enuErrorStatus;
}


void __vector_16 (void) __attribute__((signal, used));
void __vector_16 (void)
{

	u8 Loc_u8TempRegister = 0;

#if ADC_u8ADLAR == ADC_RIGHT_SHIFT

	Adc_prvChain.Result[Adc_u8IndexConversion] = (ADCL) | (ADCH << 8);

#elif ADC_u8ADLAR == ADC_LEFT_SHIFT

	Adc_prvChain.Result[Adc_u8IndexConversion] = (ADCL >> 8) | (ADCH << 2);

#endif

	Adc_u8IndexConversion++;

	if(Adc_prvChain.Size == Adc_u8IndexConversion)
	{
		ADC_u8BusyState = IDLE;

		/*Call at the end*/
		Adc_prvChain.Notification();

		/*Clear conversion bit*/
		CLR_BIT(ADCSRA, ADIE);
	}
	else
	{
		Loc_u8TempRegister = ADMUX;
		Loc_u8TempRegister &= 0b11100000;
		Loc_u8TempRegister |= Adc_prvChain.Channel[0];

		ADMUX = Loc_u8TempRegister;

		/*start conversion*/
		SET_BIT(ADCSRA, ADSC);

	}

}



