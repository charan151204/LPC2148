#include "gpio_header.h"
/*
* Function Name : int main(void)
* Decription    : This Function to blink LED's Using the GPIO drivers                           
*/
int main(void)
{
	while(1)
	{
		// Set Port 0 pins 0 to 3 to High
		portWrite(0,15);
		// Set Port 1 pins 16 to 19 to HIGH
		portWrite(12,15);
		// Function call to generate delay
		delay(1000000);
		// Set Port 0 pins 0 to 3 to LOW
		portWrite(0,0);
		// Set Port 1 pins 16 to 19 to LOW
		portWrite(12,0);
		// Function call to generate delay
		delay(1000000);
		
	}
}

