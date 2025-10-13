#include<lpc21xx.h>
#include"GPIO.h"

void delay(int n)
{
   int i;
	for(i=0;i<n;i++);
}

int main()
{
	while(1)
	{
	  pinWrite(1,1);
	  pinWrite(2,1);
	  pinWrite(3,1);
	  pinWrite(4,1);
	  delay(10000);
	  pinWrite(1,0);
	  pinWrite(2,0);
	  pinWrite(3,0);
	  pinWrite(4,0);
		delay(10000);
	}
	
}