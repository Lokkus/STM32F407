#include "uart_test.h"

static void test_printf() __attribute__((unused));
static void get_uart_using_dma() __attribute__((unused));

static void test_printf()
{
    float x = 4.45667;
    printf("Test float: x = %.4f\r\n", x);
    
    for (uint16_t i = 0; i<10; i++)
    {
        printf("Test string nr: %d\r\n", i);
    }
}

static void get_uart_using_dma()
{
    start_uart_dma(UART_GetHandle());
}


void uart_tests()
{
    test_printf();
    //get_uart_using_dma();
}
