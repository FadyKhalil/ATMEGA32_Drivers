/*
 * Lcd_cfg.h
 *
 *  Created on: Mar 14, 2022
 *      Author: fady
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_


/*PIN Initialization For LCD*/
#define LCD_u8D7_PIN			23
#define LCD_u8D6_PIN		    22
#define LCD_u8D5_PIN		    21
#define LCD_u8D4_PIN		    20
#define LCD_u8D3_PIN		    19
#define LCD_u8D2_PIN		    18
#define LCD_u8D1_PIN		    17
#define LCD_u8D0_PIN		    16

#define LCD_u8EN_PIN		    24
#define LCD_u8RW_PIN		    25
#define LCD_u8RS_PIN		    26


/*Initialization Function to initialize LCD*/
#define LCD_SETON_DISPLAY	    1 //To Set the display ON
#define LCD_CURSOR_ON		    0 //To Set the cursor ON
#define	LDC_CURSOR_BLINKING		0 //To Set the cursor to Blink

/*Continue for Initialization Function*/
#define LCD_DATA_LENGTH			1 //Data Length (1) => for 8 pin initialization
								  //			(0) => for 4 pin initialization

#define LCD_NUMBER_LINES		1
#define LCD_CHARACTER_FONT		0

#define LCD_SC		0
#define LCD_RL		1

#define LCD_ID		1
#define LCD_SH		0




#endif /* LCD_CFG_H_ */
