/*
 * Adc_cfg.h
 *
 *  Created on: Mar 31, 2022
 *      Author: fady
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_



/*this define can be initialize with one of this parameter
 *
 * @ ADC_VOLTAGE_REFERENCE_EXTERNAL
 * @ ADC_VOLTAGE_AVCC
 * @ ADC_VOLTAGE_INTERNAL
 *
 *
 * */
#define ADC_u8VOLTAGE_REFERENCE		ADC_VOLTAGE_AVCC


/*this define can be initialize with one of this parameter
 *
 * @ ADC_RIGHT_SHIFT
 * @ ADC_LEFT_SHIFT
 *
 * */
#define ADC_u8ADLAR					ADC_RIGHT_SHIFT



/*this define can be initialize with one of this parameter
 *
 * @ ADC_DEVISION_2
 * @ ADC_DEVISION_4
 * @ ADC_DEVISION_8
 * @ ADC_DEVISION_16
 * @ ADC_DEVISION_32
 * @ ADC_DEVISION_64
 * @ ADC_DEVISION_128
 *
 * */
#define ADC_u8PRESCALER				ADC_DEVISION_2



/*this define can be initialize with one of this parameter
 *
 * @ ADC_ON
 * @ ADC_OFF
 *
 * */
#define ADC_STATUS					ADC_ON
#endif /* ADC_CFG_H_ */
