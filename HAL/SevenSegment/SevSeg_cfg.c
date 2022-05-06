/*
 * SevSeg_cfg.c
 *
 *  Created on: Apr 13, 2022
 *      Author: fady
 */



#include "SevSeg.h"
#include "SevSeg_cfg.h"



SevSeg_Configuration ConfigPtr [NUMBER_OF_SEVEN_SEGMENT] = {

		[0] = {
				.Mode = ANODE,
				.PinEnable = SEVSEG_PIN_EN2
		},

		[1] = {
				.Mode = ANODE,
				.PinEnable = SEVSEG_PIN_EN1
		},
		[2] = {
				.Mode = CATHODE,
				.PinEnable = SEVSEG_PIN_EN
		},


//
//		[3] = {
//				.Mode = CATHODE
//		}


};
