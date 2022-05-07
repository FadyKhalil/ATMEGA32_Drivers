/*
 * Icu.h
 *
 *  Created on: May 1, 2022
 *      Author: fady
 */

#ifndef MCAL_ICU_ICU_H_
#define MCAL_ICU_ICU_H_

typedef void(*Icu_CallFunc)(void);

typedef enum
{
	Icu_Edge_Falling = 0,
	Icu_Edge_Rising = 1

}Icu_Edge;




void Icu_vidInit(void);

void Icu_vidRegisterCallBack(Icu_CallFunc Cbf);

void Icu_vidEnableInterrupt(void);

void Icu_vidDisableInterrupt(void);

void Icu_vidChangeTrigger(Icu_Edge Copy_u8TriggerSource);

void Icu_vidReadValue(pu16 Add_pu16Value);



#endif /* MCAL_ICU_ICU_H_ */
