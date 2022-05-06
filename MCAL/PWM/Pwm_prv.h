/*
 * Pwm_prv.h
 *
 *  Created on: Apr 23, 2022
 *      Author: fady
 */

#ifndef MCAL_PWM_PWM_PRV_H_
#define MCAL_PWM_PWM_PRV_H_


#define LEAST_SIGNIFICANT_BIT	0x03
#define THREE					3


/*
 *
 * !! TIMER 0 && TIMER 2 !!
 *
 * */
#define NON_INVERTED	0x20
#define INVERTED		0x30

/*
 * !!!  TIMER 2 !!!
 *
 * */
#define NON_INVERTED_A	0x80
#define INVERTED_A		0xC0

#define NON_INVERTED_B	0x20
#define INVERTED_B		0x30




/*MAX configuration*/
#define MAX_TCNTO		255
#define MAX_TCNT2		255
#define MAX_TCNT1		65535


#define F_CLOCK			(u64)16000000U



#endif /* MCAL_PWM_PWM_PRV_H_ */
