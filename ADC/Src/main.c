#include <stdint.h>
#include "stm32f103xb.h"

volatile uint16_t adc_val[3];
volatile uint32_t voltage_mv[3];
void ADC1_Init(void);
uint16_t ADC1_Read_Channel(uint8_t channel);

void ADC1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;
    GPIOA->CRL &= ~(0xFFF << 0);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SMPR2 |= (7 << 0) | (7 << 3) | (7 << 6);

    ADC1->CR2 |= ADC_CR2_ADON;
    for (volatile int i = 0; i < 10000; i++);
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC1_Read_Channel(uint8_t channel)
{
    ADC1->SQR3 = channel;
    ADC1->CR2 |= ADC_CR2_ADON;
    while (!(ADC1->SR & ADC_SR_EOC));
    return (uint16_t)ADC1->DR;
}

int main(void)
{
    ADC1_Init();

    while(1)
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            adc_val[i] = ADC1_Read_Channel(i);
            voltage_mv[i] = (uint32_t)((adc_val[i] * 3300) / 4095);
        }

        for (volatile int i = 0; i < 500000; i++);
    }
}
