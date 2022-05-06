/*
 * SevSeg.h
 *
 *  Created on: Apr 13, 2022
 *      Author: fady
 */

#ifndef HAL_SEVENSEGMENT_SEVSEG_H_
#define HAL_SEVENSEGMENT_SEVSEG_H_

#include "../../Service/UTILITIES/Std_types.h"


typedef enum
{
	ANODE = 0,
	CATHODE

}SevSeg_Type;

typedef struct
{
	SevSeg_Type Mode;
	u8 PinEnable;

}SevSeg_Configuration;


void SevSeg_vidDisplayNumber(u16 Copy_u16Number);
void SevSeg_vidTurnOff(u8 Copy_DisplayNumber);



#endif /* HAL_SEVENSEGMENT_SEVSEG_H_ */
