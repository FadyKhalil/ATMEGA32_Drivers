/*
 * Servo.c
 *
 *  Created on: Apr 28, 2022
 *      Author: fady
 */


#include "../../Service/UTILITIES/Std_types.h"
#include "Servo.h"
#include "../../MCAL/PWM/Pwm.h"


#define PERIOD_20_MS	20


void Servo_vidInit(void)
{
	Pwm_ConfigType PwmConfig = {
			.Timer1_cfg.CompareMatch_Mode_A = NON_INVERTED_MODE,
			.Timer1_cfg.ClockSelection = PWM_PREDEF_64_PRESCALLER,
			.Timer1_cfg.Mode = PWM_TIMER1_FAST_PWM_ICR1
	};

	Pwm_Init(&PwmConfig);

}

void Servo_vidSetAngle(u8 Copy_u8Angle)
{
	if(Copy_u8Angle > 180)
	{
		//return Error
	}
	else
	{
		f32 Loc_f32DutyCycleValue = 0;
		Loc_f32DutyCycleValue = 10 - (((180 - Copy_u8Angle) / (f32)90) * 2.5);
		Pwm_SetPeriodAndDuty(PERIOD_20_MS, Loc_f32DutyCycleValue);
	}
}



