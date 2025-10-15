#include <lpc214x.h>

unsigned int mycount = 0;

void INT0ISR(void) __irq
{
    long int temp;
    temp = EXTINT;              // Read interrupt status
    IODIR0 |= (1 << 25);        // P0.25 as output

    if ((temp & 0x01) == 1)     // Check for EINT0
    {
        if (mycount >= 10)
            IOSET0 |= (1 << 25);    // Turn ON LED
        else
        {
            mycount++;
            IOCLR0 |= (1 << 25);    // Turn OFF LED
        }
    }

    EXTINT = 0x01;              // Clear EINT0
    VICVectAddr = 0x00;         // Acknowledge ISR
}

void initInterrupt(void)
{
    VICIntEnable |= (1 << 14);                 // Enable EINT0 (Interrupt #14)
    VICVectCntl0 = (1 << 5) | 14;              // Vectored slot with EINT0
    VICVectAddr0 = (unsigned)INT0ISR;          // ISR address

    PINSEL1 |= (1 << 0);                       // P0.16 = EINT0 (01)
    PINSEL1 &= ~(1 << 1);

    EXTMODE |= 0x01;                           // Edge sensitive
    EXTPOLAR &= ~0x01;                         // Falling edge
}