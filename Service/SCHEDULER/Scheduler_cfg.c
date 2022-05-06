/*
 * Scheduler_cfg.c
 *
 *  Created on: Apr 12, 2022
 *      Author: fady
 */

#include "../../Service/UTILITIES/Std_types.h"
#include "Scheduler.h"
#include "Scheduler_cfg.h"
#include "../../Application/App.h"
#include "../../HAL/Switch/Hswitch.h"


Scheduler_sTaskType Task_Array[NUMBER_OF_TASK]  = {

		[0] = {
				.CallFunction = DisplayNumber,
				.FirstDelay = 0,
				.Periodicity = 10,
				.State = 1,
		},

		[1] = {
				.CallFunction = Decrement,
				.FirstDelay = 1,
				.Periodicity = 50,
				.State = 1
		},

		[2] = {
				.CallFunction = Application,
				.FirstDelay = 2,
				.Periodicity = 150,
				.State = 1
		},

		[3] = {
				.CallFunction = Switch_vidTask,
				.FirstDelay = 3,
				.Periodicity = 5,
				.State = 1
		}

};
