#include <LPC214x.h>
#include "timer.h"

#define LED0  (0X01)
#define LED1 ((0X01)<<1)
#define LED2 ((0X01)<<2)
#define LED3 ((0X01)<<3)


int main()
{
	IODIR0|=0x0F;
	IOCLR0|=0X0F;
	
	while(1)
	{
		IOSET0|=LED0;
	  delayms(1000);
	  IOSET0|=LED1;
	  delayms(1000);
	  IOSET0|=LED2;
	  delayms(1000);
	  IOSET0|=LED3;
	  delayms(1000);
	  IOCLR0|=0X0F;
		delayms(1000);
	}
}

	
