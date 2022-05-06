


#include "Service/UTILITIES/Std_types.h"
#include "MCAL/ICU/Icu.h"
#include "MCAL/DIO/Dio.h"
#include "MCAL/PORT/Port.h"
#include "MCAL/PWM/Pwm.h"
#include "MCAL/GIE/Gie.h"



void Led(void)
{
	Dio_enuFlipChannel(10);
}


int main(void)
{
	u8 Loc_u8Value;

	Pwm_ConfigType PwmConfig = {
			.Timer1_cfg.Mode = PWM_TIMER1_FAST_PWM_ICR1,
			.Timer1_cfg.CompareMatch_Mode_A = NON_INVERTED_MODE,
			.Timer1_cfg.ClockSelection = PWM_PREDEF_64_PRESCALLER
	};

	PORT_vidInit();
	Icu_vidInit();

	Gie_vidEnable();

	Pwm_Init(&PwmConfig);
	Pwm_SetPeriodAndDuty(20, 20);

	Icu_vidRegisterCallBack(Led);

	Icu_vidReadValue(&Loc_u8Value);

	while(1)
	{

	}

	return 0;
}
