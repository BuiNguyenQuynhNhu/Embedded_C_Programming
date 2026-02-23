#include "stm32f103xb.h"

void SPI_Master_Init(void)
{
    RCC->APB2ENR |= (1U << 2);
    RCC->APB2ENR |= (1U << 12);
    GPIOA->CRL &= ~(1U << 16);
    GPIOA->CRL &= ~(1U << 17);
    GPIOA->CRL &= ~(1U << 18);
    GPIOA->CRL &= ~(1U << 19);
    GPIOA->CRL |=  (1U << 16);
    GPIOA->CRL |=  (1U << 17);
    GPIOA->CRL &= ~(1U << 18);
    GPIOA->CRL &= ~(1U << 19);
    GPIOA->CRL &= ~(1U << 20);
    GPIOA->CRL &= ~(1U << 21);
    GPIOA->CRL &= ~(1U << 22);
    GPIOA->CRL &= ~(1U << 23);
    GPIOA->CRL |=  (1U << 20);
    GPIOA->CRL |=  (1U << 21);
    GPIOA->CRL &= ~(1U << 22);
    GPIOA->CRL |=  (1U << 23);
    GPIOA->CRL &= ~(1U << 24);
    GPIOA->CRL &= ~(1U << 25);
    GPIOA->CRL &= ~(1U << 26);
    GPIOA->CRL &= ~(1U << 27);
    GPIOA->CRL &= ~(1U << 24);
    GPIOA->CRL &= ~(1U << 25);
    GPIOA->CRL |=  (1U << 26);
    GPIOA->CRL &= ~(1U << 27);
    GPIOA->CRL &= ~(1U << 28);
    GPIOA->CRL &= ~(1U << 29);
    GPIOA->CRL &= ~(1U << 30);
    GPIOA->CRL &= ~(1U << 31);
    GPIOA->CRL |=  (1U << 28);
    GPIOA->CRL |=  (1U << 29);
    GPIOA->CRL &= ~(1U << 30);
    GPIOA->CRL |=  (1U << 31);
        SPI1->CR1 = 0;
        SPI1->CR1 |= (1U << 2);
        SPI1->CR1 &= ~(1U << 1);
        SPI1->CR1 &= ~(1U << 0);
        SPI1->CR1 &= ~(1U << 5);
        SPI1->CR1 |=  (1U << 4);
        SPI1->CR1 |=  (1U << 3);
        SPI1->CR1 &= ~(1U << 10);
        SPI1->CR1 &= ~(1U << 15);
        SPI1->CR1 &= ~(1U << 7);
        SPI1->CR1 &= ~(1U << 11);
        SPI1->CR1 |= (1U << 9);
        SPI1->CR1 |= (1U << 8);
        SPI1->CR1 |= (1U << 6);
    }


void SPI_Slave_Init(void)
{
    RCC->APB2ENR |= (1U << 2);
    RCC->APB2ENR |= (1U << 12);
    GPIOA->CRL &= ~((0xFU << 16) |
                    (0xFU << 20) |
                    (0xFU << 24) |
                    (0xFU << 28));
    GPIOA->CRL |= (0x8U << 16);
    GPIOA->ODR |= (1U << 4);
    GPIOA->CRL |= (0x4U << 20);
    GPIOA->CRL |= (0xBU << 24);
    GPIOA->CRL |= (0x4U << 28);
    SPI1->CR1 = 0;
    SPI1->CR1 &= ~(1U << 2);
    SPI1->CR1 &= ~(1U << 1);
    SPI1->CR1 &= ~(1U << 0);
    SPI1->CR1 &= ~(1U << 10);
    SPI1->CR1 &= ~(1U << 15);
    SPI1->CR1 &= ~(1U << 11);
    SPI1->CR1 &= ~(1U << 7);
    SPI1->CR1 &= ~(1U << 9);
    SPI1->CR1 |= (1U << 6);
}

void master(){
	SPI_Master_Init();
	    LED_Init();

	    while (1) {

	        GPIOC->BRR = (1U << 13);
	        SPI1_Transmit(1);
	        for (volatile int i = 0; i < 2000000; i++);
	        GPIOC->BSRR = (1U << 13);
	        SPI1_Transmit(0);
	        for (volatile int i = 0; i < 2000000; i++);
	    }
}
void LED_Init(void) {
    RCC->APB2ENR |= (1U << 4);
    GPIOC->CRH &= ~(0xFU << 20);
    GPIOC->CRH |= (0x3U << 20);
}

void SPI1_Transmit(uint8_t data) {
    GPIOA->BRR = (1U << 4);

    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;

    while (!(SPI1->SR & SPI_SR_RXNE));
    (void)SPI1->DR;

    while (SPI1->SR & SPI_SR_BSY);
    GPIOA->BSRR = (1U << 4);
}
uint8_t SPI1_Receive(void) {

    if (SPI1->SR & (1U << 6)) {
        (void)SPI1->DR;
        (void)SPI1->SR;
    }

    while (!(SPI1->SR & (1U << 0)));

    return (uint8_t)SPI1->DR;
}
void slave(){
	SPI_Slave_Init();
	    LED_Init();
	    GPIOC->BSRR = (1U << 13);

	    while (1) {
	        uint8_t cmd = SPI1_Receive();
	        if (cmd == 0) {
	            GPIOC->BRR = (1U << 13);
	        } else {
	            GPIOC->BSRR = (1U << 13);
	        }
	    }
}
int main(void) {
//    slave();
}



