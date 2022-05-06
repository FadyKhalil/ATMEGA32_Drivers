/*
 * Timer.h
 *
 *  Created on: Apr 9, 2022
 *      Author: fady
 */

#ifndef GPT_H_
#define GPT_H_

/****************Typedef*********************/

typedef void(*CallBackFunc)(void);

typedef u16 Gpt_ValueType;

/*Gpt Chose Channel type*/
typedef enum
{
	TIMER0 = 0,
	TIMER1,
	TIMER2,
	END

}Gpt_ChannelType;

/*Gpt Configuration structure parameter*/
typedef struct
{
	u8 WaveFormGeneration;
	u8 ClockSelection; // prescaller /**/
	u8 EnableInterrupt;
	u8 ForceOuptputCompare;
	u16 NumberOfOverflow;
	Gpt_ChannelType Channel;

}Gpt_ConfigType;


/*Gpt configuration */
typedef enum
{
	GPT_MODE_NORMAL = 0,
	GPT_MODE_SLEEP

}Gpt_ModeType;


typedef enum
{

	GPT_enuOK = 0,
	GPT_E_PARAM_CHANNEL,
	GPT_E_ALREADY_INITIALIZED,
	GPT_E_PARAM_POINTER,
	GPT_E_PARAM_VALUE

}Gpt_tenuErrorStatus;




/***********************Define********************/

#define GPT_PREDEF_NO_CLOCK						0x00
#define GPT_PREDEF_NO_PRESCALLER				0x01
#define GPT_PREDEF_8_PRESCALLER					0x02
#define GPT_PREDEF_64_PRESCALLER				0x03
#define GPT_PREDEF_256_PRESCALLER				0x04
#define GPT_PREDEF_1024_PRESCALLER				0x05
#define GPT_PREDEF_EXT_CLOCK_FALLING			0x06
#define GPT_PREDEF_EXT_CLOCK_RISING				0x07


#define GPT_PREDEF_FORCE_OUTPUT_COMPARE_ON		0x80
#define GPT_PREDEF_FORCE_OUTPUT_COMPARE_OFF		0x00

#define GPT_PREDEF_WAVEFORM_NORMAL				0x00
#define GPT_PREDEF_WAVEFORM_CTC					0x04

#define GPT_ENABLE_INTERRUPT					0x01
#define GPT_DISABLE_INTERRUPT					0x00



/**************************************************/


void Gpt_Init(const Gpt_ConfigType* ConfigPtr);

Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);

Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);

void Gpt_StartTimer(Gpt_ChannelType Channel,  Gpt_ValueType Value);

void Gpt_StopTimer(Gpt_ChannelType Channel);

void Gpt_SetMode(Gpt_ModeType Mode);

void Gpt_Notification_TIMR0(CallBackFunc Caller);




#endif /* GPT_H_ */
