/*
 * Adc.h
 *
 *  Created on: Mar 25, 2022
 *      Author: fady
 */

#ifndef ADC_H_
#define ADC_H_


typedef void(*CallNotification)(void);

typedef enum
{
	ADC_enuOk = 0,
	ADC_enuNok,
	ADC_enuErrorValue,
	ADC_enuErrorPin,
	ADC_enuNullPointer

}Adc_tenuErrorStatus;

typedef struct
{
	u8* Channel;
	u16* Result;
	u8 Size;
	CallNotification Notification;

}Chain_t;


#define ADC_PIN00				0x300
#define ADC_PIN01				0x301
#define ADC_PIN02				0x302
#define ADC_PIN03				0x303
#define ADC_PIN04				0x304
#define ADC_PIN05				0x305
#define ADC_PIN06				0x306
#define ADC_PIN07				0x307


#define ADC_ENABLE_INTERRUPT	0x104
#define ADC_DISABLE_INTERRUPT	0x100




extern void Adc_vidInit(void);


extern Adc_tenuErrorStatus Adc_enuInterruptStatus(u16 Copy_u8StatusValue);

extern Adc_tenuErrorStatus Adc_enuStartConversionSynch(u16 Copy_u16PinNumber, pu16 Add_pu16Value);

extern Adc_tenuErrorStatus Adc_tenuStartChainAsynch(Chain_t* Add_tChain);

#endif /* ADC_H_ */
