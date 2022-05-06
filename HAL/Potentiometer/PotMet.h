/*
 * PotMet.h
 *
 *  Created on: Apr 30, 2022
 *      Author: fady
 */

#ifndef HAL_POTENTIOMETER_POTMET_H_
#define HAL_POTENTIOMETER_POTMET_H_

#define POT_PIN00				0x300
#define POT_PIN01				0x301
#define POT_PIN02				0x302
#define POT_PIN03				0x303
#define POT_PIN04				0x304
#define POT_PIN05				0x305
#define POT_PIN06				0x306
#define POT_PIN07				0x307



u16 PotMet_vidReadValue(u16 Copy_u8PinNumber);


#endif /* HAL_POTENTIOMETER_POTMET_H_ */
