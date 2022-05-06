/*
 * Pwm.h
 *
 *  Created on: Apr 23, 2022
 *      Author: fady
 */

#ifndef MCAL_PWM_PWM_H_
#define MCAL_PWM_PWM_H_


typedef u16 Pwm_PeriodType;

typedef enum
{
	Pwm_enuOk = 0,
	Pwm_enuNotValidNumber,
	Pwm_enuNullPointer,
	Pwm_enuNotValidChannel

}Pwm_tenuErrorStatus;

typedef enum
{
	TIMER_0 = 0,
	TIMER_1,
	TIMER_2

}Pwm_ChannelType;


typedef struct
{
	struct
	{
		u8 Mode;
		u8 CompareMatch_Mode;
		u8 ClockSelection;

	}Timer0_cfg;

	struct
	{
		u8 Mode;
		u8 CompareMatch_Mode_A;
		u8 CompareMatch_Mode_B;
		u8 ClockSelection;
	}Timer1_cfg;

	struct
	{
		u8 Mode;
		u8 CompareMatch_Mode;
		u8 ClockSelection;

	}Timer2_cfg;

}Pwm_ConfigType;



/***************defines***********************/

/*to initialize the clock presclaler
 * @ datatype: 	Pwm_ConfigType
 *
 * ! Element --> ClockSelection
 *
 * !! TIMER 0
 * !! TIMER 1
 * !! TIMER 2
 *
 * */
#define PWM_PREDEF_NO_CLOCK						0x00
#define PWM_PREDEF_NO_PRESCALLER				0x01
#define PWM_PREDEF_8_PRESCALLER					0x02
#define PWM_PREDEF_64_PRESCALLER				0x03
#define PWM_PREDEF_256_PRESCALLER				0x04
#define PWM_PREDEF_1024_PRESCALLER				0x05
#define PWM_PREDEF_EXT_CLOCK_FALLING			0x06
#define PWM_PREDEF_EXT_CLOCK_RISING				0x07


/*to initialize which pwm mode to be chosen
 * configure to the datatype Pwm_ConfigType
 *
 * Element --> Mode
 *
 * !! TIMER 0
 * !! TIMER 2
 *
 * !! TIMER 1 HAS IT OWN MODE CONFIGURATION
 *
 * */
#define PWM_PHASE_CORRECT						0x08
#define PWM_FAST								0x48

/*to initialize Compare output Mode to be chosen in
 * configure datatype Pwm_ConfigType
 *
 * !! TIMER 0
 * !! TIMER 1
 * !! TIMER 2
 *
 * Element --> CompareMatch_Mode
 * */
#define NORMAL_PORT_OPERATION					0x00
#define NON_INVERTED_MODE						0x20
#define INVERTED_MODE							0x30


/*==============FOR TIMER1 USAGE ONLY====================*/

/*ADDITIONAL COMPARE OUTPUT MODE FOR TIMER 1*/
#define TOGLE_OC1A_DISCONECT_OC1B				0x10;


/*to initialize which pwm mode to be chosen
 * configure to the datatype Pwm_ConfigType
 *
 * !! FOR TIMER 1
 *
 * Element --> Mode
 * */

#define PWM_TIMER1_PHASE_CORRECT_8_BIT		0x01
#define PWM_TIMER1_PHASE_CORRECT_9_BIT		0x02
#define PWM_TIMER1_PHASE_CORRECT_10_BIT		0x03
#define PWM_TIMER1_FAST_PWM_8_BIT			0x05
#define PWM_TIMER1_FAST_PWM_9_BIT			0x06
#define PWM_TIMER1_FAST_PWM_10_BIT			0x07
#define PWM_TIMER1_PHASE_FREQUENCY_ICR1		0x08
#define PWM_TIMER1_PHASE_FREQUENCY_OCR1A	0x09
#define PWM_TIMER1_PHASE_CORRECT_ICR1		0x0A
#define PWM_TIMER1_PHASE_CORRECT_OCR1A		0x0B
#define PWM_TIMER1_FAST_PWM_ICR1			0x0E
#define PWM_TIMER1_FAST_PWM_OCR1A			0x0F



/*
 *	Function Name:	Pwm_Init
 *
 *	Parameter Take:	const Pwm_ConfigType*
 *					!! Use the Macros Above for the configuration of the structure
 *
 *
 * 	Description:	To configure the PWM mode
 *
 *
 *	Return:			void
 *
 *
 * */
extern Pwm_tenuErrorStatus Pwm_Init(const Pwm_ConfigType* ConfigPtr);


/*
 *	Function Name:	Pwm_SetDutyCycle
 *
 *	Parameter Take:	ChannelNumber	 --> in Range { TIMER_0, TIMER_1, TIMER_2 }
 *					DutyCyle		 --> in Range { 0 -> 100 }
 *
 *
 * 	Description:	To configure the PWM DutyCycle
 *
 *
 *	Return:			void
 *
 *
 * */
extern Pwm_tenuErrorStatus Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, u16 DutyCyclePercent);

/*
 *	Function Name:	Pwm_SetDutyCycle
 *
 *	Parameter Take:	Period_ms		--> in Range {0 -> 65355 (milliSecond) }
 *					DutyCyle		--> in Range { 0 -> 100 }
 *
 *
 * 	Description:	To configure the PWM DutyCycle
 *
 *
 *	Return:			void
 *
 *	!!!!!!!!!!!!!!!!!! Only Applicable of TIMER 1 !!!!!!!!!!!!!!!!!!!!!!
 *
 * */
extern Pwm_tenuErrorStatus Pwm_SetPeriodAndDuty(Pwm_PeriodType Period_ms, f32 DutyCyclePercent);


#endif /* MCAL_PWM_PWM_H_ */
