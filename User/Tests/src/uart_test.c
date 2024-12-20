#include "uart_test.h"

static void test_printf() __attribute__((unused));

static void test_printf()
{
    float x = 4.45667;
    printf("Test float: x = %.4f\r\n", x);
    
    for (uint16_t i = 0; i<10; i++)
    {
        printf("Test string nr: %d\r\n", i);
    }
}

void uart_tests()
{
    test_printf();
    enable_getting_uart_data_dma();
}
