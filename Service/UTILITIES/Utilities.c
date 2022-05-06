/*
 * Utilities.c
 *
 *  Created on: Apr 30, 2022
 *      Author: fady
 */

#include "Std_types.h"

s32 Map(s32 Input_Min, s32 Output_Min, s32 Input_Max, s32 Output_Max, s32 Value_Input)
{
	s32 Loc_s32TempValue;
	s32 Loc_s32DiffrenceInput = Input_Max - Input_Min;
	s32 Loc_s32DiffrenceOutput = Output_Max - Output_Min;
	Loc_s32DiffrenceOutput *= (Input_Max - Value_Input);
	Loc_s32TempValue = Loc_s32DiffrenceOutput / Loc_s32DiffrenceInput;
	Loc_s32TempValue -= Output_Max;
	Loc_s32TempValue = ~Loc_s32TempValue;

	return Loc_s32TempValue;
}
