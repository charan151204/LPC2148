#include<lpc21xx.h>

#define IN ((IOPIN0) & (1<<5))

int main()
{
	
   IODIR0|=0x01;
	 IOCLR0|=0x01;
	 while(1)
	 {
		
		 if(IN)
		 {
			 IOSET0|=0x01;
		 }
		 else
		 { 
			 IOCLR0|=0x01;
		 }
		 
	 }
	
}















