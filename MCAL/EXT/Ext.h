/*
 * Ext.h
 *
 *  Created on: Apr 16, 2022
 *      Author: fady
 */

#ifndef EXT_H_
#define EXT_H_

typedef void(*Ext_Callfunc)(void);


typedef enum
{
	EXT_INT_0 = 0,
	EXT_INT_1,
	EXT_INT_2


}Int_ID;


typedef struct
{
	u8 INT0_Mode;
	u8 INT0_Int;
	u8 INT1_Mode;
	u8 INT1_Int;
	u8 INT2_Mode;
	u8 INT2_Int;

}Ext_Config;


typedef enum
{
	Ext_enuNullPointer = 0,
	Ext_enuOk

}Ext_tenuErrorStatus;

Ext_tenuErrorStatus Ext_vidInit(Ext_Config* ConfigPtr);



#endif /* EXT_H_ */
