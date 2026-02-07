#ifndef UART_H_
#define UART_H_
#include "stm32f103xb.h"
#define GPIOAEN (1U<<2)
#define UARTEN   (1U << 14)
#define UART_SR_TXE    (1U << 7)
#define UART_SR_RXNE   (1U << 5)

void uart_init(void);
void uart_write(int ch);
char uart_read(void);
void uart_write_string(const char *str);

#endif /* UART1_H_ */
