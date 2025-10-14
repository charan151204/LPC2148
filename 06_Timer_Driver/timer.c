#include <LPC214x.h>
#include "timer.h"
#include "gpio.h"

int main()
{
    initPLL();
    while(1)
    {
        pinWrite(1,1);
        delayms(1000);
        pinWrite(1,0);
        delayus(1000);
        delayms(1000);
    }
}