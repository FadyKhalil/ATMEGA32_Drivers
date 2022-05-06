/*
 * Lcd.h
 *
 *  Created on: Mar 14, 2022
 *      Author: fady
 */

#ifndef LCD_H_
#define LCD_H_


//#include "../../../AVR_WorkSpace/Services/Std_types.h"


/*------------------------------DEFINES----------------------------------*/


/*This Variables are used for function
 * @Lcd_vidSendCommand()
 * */
#define CLEAR			0x01
#define RETURN_HOME		0x02
#define HOME_POSITION	0x80
#define LINE2			0xC0


/*------------------------------FUNCTION PROTOTYPES--------------------*/



/*
 * Public Function			:	Lcd_vidInit
 *
 * Description				:	To initialize the Lcd to 8 bit Mode
 *
 * Input Parameter			:	Not Applicable
 *
 * Return 					:	-> the Function return void
 *
 * Input/Output 			:	-> Not applicable
 * */
void Lcd_vidInit(void);


/*
 * Public Function			:	Lcd_vidSendCommand
 *
 * Description				:	This function used to send command to the LCD
 *
 * Input Parameter			:	Copy_u8Command
 * 								@ CLEAR 		-> 	To Clear Screen and go to main (0,0)
 * 								@ RETURN_HOME 	->	To Return the cursor to main (0,0) without deleting
 * 													the contents
 * 								@ HOME_POSITION	->	To go to line 1
 * 								@ LINE2			->	To go to line 2
 *
 * Return 					:	-> the Function return void
 *
 * Input/Output 			:	-> Not applicable
 * */
void Lcd_vidSendCommand(u8 Copy_u8Command);



/*
 * Public Function			:	Lcd_vidDisplayCharacter
 *
 * Description				:	This function to print on the lcd
 *
 * Input Parameter			:	Copy_u8Character
 * 								@ You can add the ascii character as display character
 * 								@ However to print special character you have to create Custom
 * 								  character using function
 * 								  --> Lcd_vidCreateCustomCharacter
 *
 * Return 					:	-> the Function return void
 *
 * Input/Output 			:	-> Not applicable
 * */
void Lcd_vidDisplayCharacter(u8 Copy_u8Character);



/*
 * Public Function			:	Lcd_vidCreateCustomCharacter
 *
 * Description				:	This function used to send command to the LCD
 *
 * Input Parameter			:	=> Copy_u8CustomeCharacter
 * 								@ the input of the address of CGRAM
 * 									in range (0 -> 7)
 * 								=> Add_pu8CustomCharacter
 * 								@ the input of the custom character size of 8 Byte
 * 									in range {7 in row, 5 in colon}
 * 									example:
 *
 * 										0bXXX10101 ->> Only access in the first 5 bit
 * 										0bXXX10101
 * 										0bXXX10101
 * 										0bXXX10101
 * 										0bXXX10101
 * 										0bXXX10101
 * 										0bXXX10101
 * 										0bXXX10101
 * 										0bXXX10101
 *
 *
 * Return 					:	-> the Function return void
 *
 * Input/Output 			:	-> Not applicable
 * */
void Lcd_vidCreateCustomCharacter(u8 Copy_u8CgramAddress, pu8 Add_pu8CustomCharacter);



/*
 * Public Function			:	Lcd_vidDisplayString
 *
 * Description				:	This function to print string on lcd
 *
 * Input Parameter			:	Copy_u8String
 * 								@ To print array of character
 *
 * Return 					:	-> the Function return void
 *
 * Input/Output 			:	-> Not applicable
 * */
void Lcd_vidDisplayString(pu8 add_pu8String);



/*
 * Public Function			:	Lcd_vidGoto
 *
 * Description				:	This function to jump the cursor
 *
 * Input Parameter			:	=> Copy_u8Line
 * 								@ To chose the line
 * 								=> Copy_u8Colon
 * 								@ To chose the colon
 *
 * Return 					:	-> the Function return void
 *
 * Input/Output 			:	-> Not applicable
 * */
void Lcd_vidGoto(u8 copy_u8Line, u8 copy_u8Colon);


#endif /* LCD_H_ */
