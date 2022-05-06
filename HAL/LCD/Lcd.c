/*
 * Lcd.c
 *
 *  Created on: Mar 14, 2022
 *      Author: fady
 */

#include "../../Service/UTILITIES/Std_types.h"
#include "../../Service/UTILITIES/Bit_utils.h"
#include "avr/io.h"
#include "util/delay.h"
#include "../../MCAL/DIO/Dio.h"
#include "Lcd.h"
#include "Lcd_cfg.h"
#include "Lcd_prv.h"


/*------------------------------FUNCTION IMPLEMENTATION--------------------*/

void Lcd_vidInit(void) {

	Lcd_vidSendCommand(LCD_FUNCSET);
	_delay_ms(2);

	Lcd_vidSendCommand(RETURN_HOME);
	_delay_ms(2);

	Lcd_vidSendCommand(CLEAR);
	_delay_ms(2);

	Lcd_vidSendCommand(LCD_DISPLAYCONTROL);
	_delay_ms(2);

	Lcd_vidSendCommand(LCD_ENTRY_MODE);
	_delay_ms(2);

	Lcd_vidSendCommand(LCD_CURSOR_DISPLAY_SH);
	_delay_ms(2);

	Lcd_vidSendCommand(HOME_POSITION);
	_delay_ms(2);


}


void Lcd_vidSendCommand(u8 Copy_u8Command) {

	LCD_tunByteAcces	Loc_tunBitAccess;

	Loc_tunBitAccess.LCD_u8Comunication = Copy_u8Command;

	Dio_enuWriteChannel(LCD_u8RS_PIN, DIO_u8LOW);
	Dio_enuWriteChannel(LCD_u8RW_PIN, DIO_u8LOW);
	Dio_enuWriteChannel(LCD_u8EN_PIN, DIO_u8LOW);

	Dio_enuWriteChannel(LCD_u8D7_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b7);//0 //0b00111000
	Dio_enuWriteChannel(LCD_u8D6_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b6);//0
	Dio_enuWriteChannel(LCD_u8D5_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b5);//1
	Dio_enuWriteChannel(LCD_u8D4_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b4);//1
	Dio_enuWriteChannel(LCD_u8D3_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b3);//1
	Dio_enuWriteChannel(LCD_u8D2_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b2);//0
	Dio_enuWriteChannel(LCD_u8D1_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b1);//0
	Dio_enuWriteChannel(LCD_u8D0_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b0);//0

	Lcd_EnableDelay();

}



void Lcd_vidDisplayCharacter(u8 Copy_u8Character) {


	LCD_tunByteAcces	Loc_tunBitAccess;

	Loc_tunBitAccess.LCD_u8Comunication = Copy_u8Character;

	Dio_enuWriteChannel(LCD_u8RS_PIN, DIO_u8HIGH);
	Dio_enuWriteChannel(LCD_u8RW_PIN, DIO_u8LOW);
	Dio_enuWriteChannel(LCD_u8EN_PIN, DIO_u8LOW);


	Dio_enuWriteChannel(LCD_u8D7_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b7);
	Dio_enuWriteChannel(LCD_u8D6_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b6);
	Dio_enuWriteChannel(LCD_u8D5_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b5);
	Dio_enuWriteChannel(LCD_u8D4_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b4);
	Dio_enuWriteChannel(LCD_u8D3_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b3);
	Dio_enuWriteChannel(LCD_u8D2_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b2);
	Dio_enuWriteChannel(LCD_u8D1_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b1);
	Dio_enuWriteChannel(LCD_u8D0_PIN, Loc_tunBitAccess.LCD_stuBitCommunication.b0);

	Lcd_EnableDelay();
}


void Lcd_vidCreateCustomCharacter(u8 Copy_u8CgramAddress, pu8 Add_pu8CustomCharacter)
{

	u8 Loc_u8Iterator;
	Lcd_vidSendCommand(0x40 + (Copy_u8CgramAddress*8));

	for (Loc_u8Iterator = 0; Loc_u8Iterator < 8 ; Loc_u8Iterator++)
	{
		Lcd_vidDisplayCharacter(Add_pu8CustomCharacter[Loc_u8Iterator]);
	}

}


void Lcd_vidDisplayString(pu8 add_pu8String)
{
	s8 loc_u8Iterator;

	for(loc_u8Iterator = 0; add_pu8String[loc_u8Iterator] != 0; loc_u8Iterator++)
	{
		Lcd_vidDisplayCharacter(add_pu8String[loc_u8Iterator]);
	}

}


void Lcd_vidGoto(u8 copy_u8Line, u8 copy_u8Colon)
{
	if (copy_u8Line == 0 && copy_u8Colon < 16)
	{
		Lcd_vidSendCommand((copy_u8Colon & 0x0F)|HOME_POSITION);
	}
	else if (copy_u8Line == 1 && copy_u8Colon < 16)
	{
		Lcd_vidSendCommand((copy_u8Colon & 0x0F)|LINE2);
	}
}



















