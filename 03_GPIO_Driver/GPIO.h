#include<lpc21xx.h>

void pinWrite(int pinNr,int pinValue)
{
	
	if(pinNr < 100)
	{
		IODIR0 |= (1<<pinNr);
		
		if(pinValue == 0)
		{
			IOCLR0|=(1<<pinNr);
		}
		else
		{
			IOSET0|=(1<<pinNr);
		}
	}
	else
	{
		pinNr=pinNr-100;
		
		IODIR0 |= (1<<pinNr);
		
		if(pinValue == 0)
		{
			IOCLR0|=(1<<pinNr);
		}
		else
		{
			IOSET0|=(1<<pinNr);
		}
		
		
	}
		
}

int pinRead(int pinnr)
{
	if(pinnr<100)
	{
		IODIR0&=~(1<<pinnr);
		return (IOPIN0>>pinnr)&1;
	}
	else
	{
		pinnr-=100;
		IODIR1&=~(1<<pinnr);
		return (IOPIN1>>pinnr)&1;
	}
}
