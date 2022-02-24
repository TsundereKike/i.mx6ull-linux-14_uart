#include "bsp_uart.h"
/*初始化UART1,波特率为115200*/
void uart_init(void)
{
    /*初始化UART1的IO*/
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX,0);/*UART1_TX_DATA引脚复用为UART1_TX功能*/
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX,0);/*UART1_RX_DATA引脚复用为UART1_RX功能*/

    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX,0x10b0);/*设置引脚电气属性*/
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX,0x10b0);

    uart_disable(UART1);    /*关闭UART1*/
    uart_soft_reset(UART1); /*软复位UART1*/

    /*配置UART1的接收使能位、发送使能位、数据长度位、奇偶校验位、停止位*/
    UART1->UCR1  = 0;
    UART1->UCR1 &= ~(1<<14);

    UART1->UCR2 |= (1<<1) | (1<<2) | (1<<5) | (1<<14);

    /*配置UART1处于MUXED模式*/
    UART1->UCR3 |= (1<<2);

    /*设置波特率为115200*/
    UART1->UFCR &= ~(7<<7);
    UART1->UFCR |= (5<<7);  /*UART_CLK_ROOT时钟一分频 = 80MHz*/
    UART1->UBIR = 71;
    UART1->UBMR = 3124;

    /*使能UART1*/
    uart_enable(UART1);
}
/*关闭UART*/
void uart_disable(UART_Type *base)
{
    base->UCR1 &= ~(1<<0);
}
/*打开UART*/
void uart_enable(UART_Type *base)
{
    base->UCR1 |= (1<<0);
}
/*复位UART*/
void uart_soft_reset(UART_Type *base)
{
    base->UCR2 &= ~(1<<0);
    while((base->UCR2 & 0x01)==0);
}
/*通过UART1发送一个字符*/
void uart1_putc(unsigned char c)
{
    while(((UART1->USR2>>3)&0x01)==0);/*等待数据发送完成*/
    UART1->UTXD = c;
}
/*通过UART1接收一个字符*/
unsigned char uart1_getc(void)
{
    while(((UART1->USR2)&0x01)==0);/*等待有数据*/
    return UART1->URXD;
}
/*通过UART1发送一串字符*/
void uart1_puts(char *str)
{
    char *p = str;
    while(*p)
        uart1_putc(*p++);
}
