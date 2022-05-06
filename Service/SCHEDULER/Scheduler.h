/*
 * Scheduler.h
 *
 *  Created on: Apr 12, 2022
 *      Author: fady
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "Scheduler_cfg.h"

typedef void(*CallBack)(void);

typedef struct
{
	u16 FirstDelay;
	u16 Periodicity;
	u8 State;
	CallBack CallFunction;

}Scheduler_sTaskType;



extern void Scheduler_vidInit(void);

extern void Scheduler_vidStart(void);


#endif /* SCHEDULER_H_ */
