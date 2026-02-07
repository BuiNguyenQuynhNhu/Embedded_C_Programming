/*
 * spi.h
 *
 *  Created on: Nov 15, 2025
 *      Author: Admin
 */

#ifndef SPI_H_
#define SPI_H_
#include "stm32f103xb.h"

#define GPIOAEN (1U<<2)
#define SPI1EN (1U<<12)

#define MSTR (1U<<2)
#define CPOL (1U<<1)
#define CPHA (1U<<0)
#define SPE (1U<<6)

#define SR_TXE	(1U<<1)
#define SR_RXNE (1U<<0)
#define SR_BSY	(1U<<7)


void SPI_Master_Init(void);
void SPI_Transmit(uint8_t *data,uint32_t size);
void SPI_Recieve(uint8_t *data,uint32_t size);
void cs_enable(void);
void cs_disable(void);


#endif /* SPI_H_ */
