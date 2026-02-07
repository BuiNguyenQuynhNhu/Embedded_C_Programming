#include "stm32f1xx.h"


void ADC1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_ADC1EN;

    GPIOA->CRL &= ~(0xF << 0); 
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SMPR2 |= (7 << 0); 
    ADC1->CR2 |= ADC_CR2_ADON;
    for (volatile int i = 0; i < 10000; i++);

    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC1_Read(void)
{
    ADC1->SQR3 = 0;
    ADC1->CR2 |= ADC_CR2_ADON;

    while (!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

void PWM_TIM3_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    GPIOA->CRL &= ~(0xF << 24);
    GPIOA->CRL |=  (0xB << 24);

    TIM3->PSC = 72 - 1; 
    TIM3->ARR = 1000 - 1;
    TIM3->CCR1 = 0;

    TIM3->CCMR1 |= (6 << 4);
    TIM3->CCER |= TIM_CCER_CC1E;
    TIM3->CR1 |= TIM_CR1_CEN;
}

void PWM_SetDuty(uint16_t duty)
{
    if (duty > 1000) duty = 1000;
    TIM3->CCR1 = duty;
}