/*
 * Lcd_cfg.c
 *
 *  Created on: Mar 15, 2022
 *      Author: fady
 */
#include "../../Service/UTILITIES/Std_types.h"
#include "../../Service/UTILITIES/Bit_utils.h"
#include <avr/delay.h>
#include "../../MCAL/DIO/Dio.h"
#include "LCD_cfg.h"
#include "Lcd_prv.h"




void Lcd_EnableDelay(void)
{
	Dio_enuWriteChannel(LCD_u8EN_PIN, DIO_u8HIGH);
	_delay_ms(2);
	Dio_enuWriteChannel(LCD_u8EN_PIN, DIO_u8LOW);
}
