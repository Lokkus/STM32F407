#include "main.h"

void tests()
{
    timer_tests();
}

int main(void)
{
    /* Hardware init */
    peripheral_init();
    tests();
    while (1)
    {
  
    }
}
