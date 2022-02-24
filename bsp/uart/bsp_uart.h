#ifndef __BSP_UART_H
#define __BSP_UART_H
#include "imx6u.h"
void uart_init(void);
void uart_disable(UART_Type *base);
void uart_enable(UART_Type *base);
void uart_soft_reset(UART_Type *base);
void uart1_putc(unsigned char c);
unsigned char uart1_getc(void);
void uart1_puts(char *str);
#endif 