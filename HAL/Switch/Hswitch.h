/*
 * Hswitch.h
 *
 *  Created on: Apr 13, 2022
 *      Author: fady
 */

#ifndef HAL_SWITCH_HSWITCH_H_
#define HAL_SWITCH_HSWITCH_H_

#include "../../Service/UTILITIES/Std_types.h"

typedef struct
{
	u8 SwitchNumber;

}Switch_Configuration;


void Switch_vidTask(void);

void Switch_ReadStatus(u8 Copy_u8SwitchNumber, pu8 Add_pu8Value);



#endif /* HAL_SWITCH_HSWITCH_H_ */
