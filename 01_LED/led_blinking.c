#include<lpc21xx.h>

void delay(unsigned int n)
{
  unsigned int i;
  for(i=0;i<n;i++);

}

int main()
{
  IODIR0|=0XF;
  
	while(1)
	{
		IOSET0|=0XF;
  
		delay(15000000);
  
		IOCLR0|=0XF;
		
		delay(15000000);
	}

}