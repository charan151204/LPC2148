#include <LPC214x.h>
#include "uart.h"

int main()
{
    unsigned int mydata[10] = "Hello"
    initUART();

    while(1)
    {
        for(int i = 0; i < 10; i++)
        {
            sendUART(mydata[i]);
        }
        sendUART('\n');
        sendUART('\r');
        msec_delay(500);
    }
}