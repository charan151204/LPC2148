#include <lpc214x.h>
#include "interrupt.h"
#include "timer.h"


int main(void)
{
    IODIR0 |= (1 << 15);     // P0.15 as output
    initInterrupt();         // Initialize EINT0

    while (1)
    {
        IOSET0 |= (1 << 15); // Blink P0.15
        delayms(500);
        IOCLR0 |= (1 << 15);
        delayms(500);
    }
}