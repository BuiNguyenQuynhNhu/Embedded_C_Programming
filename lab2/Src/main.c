#include "stm32f103xb.h"
#include <string.h>

/* UART1 - APB2
   TX = PA9
   RX = PA10
*/

#define GPIOAEN   (1U << 2)
#define UART1EN   (1U << 14)
#define SR_TXE    (1U << 7)
#define SR_RXNE   (1U << 5)

void uart1_init(void);
void uart1_write(int ch);
char uart1_read(void);
void uart1_write_str(const char *s);

#define BUF_SIZE 64
char rx_buf[BUF_SIZE];
int  rx_idx = 0;

typedef struct {
    const char *mssv;
    const char *name;
} Student;

Student students[] = {
    {"12345678", "Nguyen Van A"},
    {"20001234", "Tran Thi B"},
    {"20190001", "Le Van C"},
};

const char* find_name(const char *mssv) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(students[i].mssv, mssv) == 0) {
            return students[i].name;
        }
    }
    return NULL;
}

void uart1_init(void)
{
    RCC->APB2ENR |= GPIOAEN;
    RCC->APB2ENR |= UART1EN;

    GPIOA->CRH &= ~(0xFF << 4);
    GPIOA->CRH |=  (0xB << 4);  // PA9
    GPIOA->CRH |=  (0x4 << 8);  // PA10

    USART1->BRR = 0x0341;

    USART1->CR1 = 0;
    USART1->CR1 |= (1U << 13);
    USART1->CR1 |= (1U << 3);
    USART1->CR1 |= (1U << 2);
}

void uart1_write(int ch)
{
    while (!(USART1->SR & SR_TXE)) {}
    USART1->DR = (ch & 0xFF);
}

void uart1_write_str(const char *s)
{
    while (*s) {
        uart1_write(*s++);
    }
}

char uart1_read(void)
{
    while (!(USART1->SR & SR_RXNE)) {}
    return (char)(USART1->DR & 0xFF);
}

int main(void)
{
    uart1_init();


    while (1)
    {
        char c = uart1_read();

        if (c == '\r' || c == '\n')
        {
            rx_buf[rx_idx] = '\0';

            if (rx_idx > 0) {
                const char* name = find_name(rx_buf);

                if (name) {
                    uart1_write_str("Ho va Ten: ");
                    uart1_write_str(name);
                    uart1_write_str("\n");
                } else {
                    uart1_write_str("\rKhong tim thay MSSV!\n");
                }
            }

            rx_idx = 0;
            memset(rx_buf, 0, BUF_SIZE);
}
        else
        {
            if (rx_idx < BUF_SIZE - 1) {
                rx_buf[rx_idx++] = c;
                uart1_write(c);
            }
        }
    }
}
