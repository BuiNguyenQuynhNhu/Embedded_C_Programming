#define RCC_BASE        0x40021000UL
#define GPIOA_BASE      0x40010800UL

#define RCC_APB2ENR     (*(volatile unsigned int *)(RCC_BASE + 0x18UL))
#define GPIOA_CRH       (*(volatile unsigned int *)(GPIOA_BASE + 0x04UL))
#define GPIOA_IDR       (*(volatile unsigned int *)(GPIOA_BASE + 0x08UL))
#define GPIOA_ODR       (*(volatile unsigned int *)(GPIOA_BASE + 0x0CUL))

#define GPIOAEN         (1U<<2)

#define SWITCH_PIN      (1U<<9)   // PA9 nút nhấn
#define LED_PIN         (1U<<11)  // PA11 LED

void delay(volatile int ms) {
    for (volatile int i = 0; i < ms * 8000; i++);
}

void GPIO_Init(void) {
    RCC_APB2ENR |= GPIOAEN;

    GPIOA_CRH &= ~(0xF << ((9 - 8) * 4));
    GPIOA_CRH |=  (0x8 << ((9 - 8) * 4));
    GPIOA_ODR |= SWITCH_PIN;


    GPIOA_CRH &= ~(0xF << ((11 - 8) * 4));
    GPIOA_CRH |=  (0x2 << ((11 - 8) * 4));
}

int main(void) {
    GPIO_Init();

    unsigned int click_count = 0;
    unsigned int last_state = 1;

    while (1) {
        unsigned int current_state = (GPIOA_IDR & SWITCH_PIN) ? 1 : 0;

        if (!current_state && last_state) {
            click_count++;

            if (click_count == 1) {
                GPIOA_ODR |= LED_PIN;
            } else if (click_count == 2) {
                GPIOA_ODR &= ~LED_PIN;
                click_count = 0;
            }

            delay(20);
        }

        last_state = current_state;
    }
}
