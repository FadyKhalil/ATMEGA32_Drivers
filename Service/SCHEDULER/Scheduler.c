/*
 * Scheduler.c
 *
 *  Created on: Apr 12, 2022
 *      Author: fady
 */


#include "../../Service/UTILITIES/Std_types.h"
#include "../../MCAL/GPT/Gpt.h"
#include "Scheduler.h"
#include "Scheduler_cfg.h"
#include "../../MCAL/DIO/Dio.h"


static u8 Scheduler_prvStartSched = 0;

extern Scheduler_sTaskType Task_Array[];

static void Scheduler_vidTickCbf(void);
static void Scheduler_vidTask(void);

void Scheduler_vidInit(void)
{
	Gpt_ConfigType GptConfig = {
			.Channel = TIMER0,
			.ClockSelection = GPT_PREDEF_64_PRESCALLER,
			.EnableInterrupt = GPT_ENABLE_INTERRUPT,
			.ForceOuptputCompare = GPT_PREDEF_FORCE_OUTPUT_COMPARE_OFF,
			.WaveFormGeneration = GPT_PREDEF_WAVEFORM_NORMAL,
			.NumberOfOverflow = NUMBER_OF_OVERFLOW
	};

	Gpt_Init(&GptConfig);
	Gpt_Notification_TIMR0(Scheduler_vidTickCbf);

}

void Scheduler_vidStart(void)
{
	Gpt_StartTimer(TIMER0, TIMER_START_VALUE);

	while(1)
	{
		if(Scheduler_prvStartSched == 1)
		{
			Scheduler_prvStartSched = 0;
			Scheduler_vidTask();
		}
		else
		{
			// do nothing
		}
	}
}


static void Scheduler_vidTickCbf(void)
{
	Scheduler_prvStartSched = 1;
	return;
}

static void Scheduler_vidTask(void)
{
	u8 Loc_u8TaskIndex;

	for(Loc_u8TaskIndex = 0; Loc_u8TaskIndex < NUMBER_OF_TASK; Loc_u8TaskIndex++)
	{
		/*check if pointer function is NULL*/
		if(Task_Array[Loc_u8TaskIndex].CallFunction)
		{
			if(Task_Array[Loc_u8TaskIndex].State == 1)
			{
				if(Task_Array[Loc_u8TaskIndex].FirstDelay == 0)
				{
					Task_Array[Loc_u8TaskIndex].CallFunction();
					Task_Array[Loc_u8TaskIndex].FirstDelay = Task_Array[Loc_u8TaskIndex].Periodicity;

				}
					Task_Array[Loc_u8TaskIndex].FirstDelay--;
			}
			else
			{
				// do nothing
			}
		}
		else
		{
			//Do nothing
		}
	}

}


