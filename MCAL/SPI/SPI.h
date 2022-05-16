/*
 * SPI.h
 *
 *  Created on: May 16, 2022
 *      Author: fady
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

typedef void(*CallFunc)(void);

typedef struct
{
	u8 Interrupt_State;
	u8 Spi_State;
	u8 Data_Order;
	u8 Clock_Polarity;
	u8 Clock_Phase;
	u8 Clk_Frequency;

}Spi_Config;


/***************Define*****************/
#define SPI_ENABLE						1
#define SPI_DISABLE						0

#define SPI_INTERRUPT_ENABLE			1
#define SPI_INTERRUPT_DISABLE			0

#define SPI_DATAORDER_LSB				1
#define SPI_DATAORDER_MSB				0

#define SPI_CLOCK_POLARITY_RISING		0
#define SPI_CLOCK_POLARITY_FALLING		1

#define SPI_CLOCK_PHASE_SAMPLE			0
#define SPI_CLOCK_PHASE_SETUP			1

#define SPI_FREQ_DEVIDE_4				0
#define SPI_FREQ_DEVIDE_16				1
#define SPI_FREQ_DEVIDE_64				2
#define SPI_FREQ_DEVIDE_128				3
#define SPI_FREQ_DEVIDE_2				4
#define SPI_FREQ_DEVIDE_8				5
#define SPI_FREQ_DEVIDE_32				6
//#define SPI_FREQ_DEVIDE_64				7

#define SPI_MASTER						1
#define SPI_SLAVE						0


void Spi_vidInit(const Spi_Config* ConfigPtr);

u8 Spi_u8Transfer(u8 Data);

void Spi_vidSelectSlave(u8 Slave);

void Spi_vidRegisterCallFunction(CallFunc Cbf);




#endif /* MCAL_SPI_SPI_H_ */
