/*
 * Hswitch_cfg.c
 *
 *  Created on: Apr 14, 2022
 *      Author: fady
 */


#include "Hswitch.h"
#include "Hswitch_cfg.h"

Switch_Configuration SwitchConfig[NUMBER_OF_SWITCH] = {

		[0] = {
				.SwitchNumber = 15,
		},

		[1] = {
				.SwitchNumber = 9,
		},

		[2] = {
				.SwitchNumber = 2,
		}

};
