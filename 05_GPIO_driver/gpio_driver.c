#include "gpio_header.h"
/*
* Function Name : void delay(unsigned int ms)
* Decription    : This Function software delay
*/
void delay(unsigned int ms)
{
	// Loop to generate the software delay
	for(unsigned int i=0;i<ms;i++);
}
/*
* Function Name :  void pinWrite(int pinNo, int pinVal)
* Decription    : This Function set or clear port pin  
*/
void pinWrite(int pinNo, int pinVal)
{
	
	// if pinNo is in between 0 to 31 then PORT 0
	if(0<= pinNo && 31>= pinNo)
	{
		// Select output direction of pin
		IODIR0 |= 1<<pinNo;		
		// if pinVal is 0 then clear pin 
		if(0 == pinVal)
		{
            // Clear the state of pin
			IOCLR0 |= 1<<pinNo;
		}
		// if pinVal is 1 then set pin 
		else if (1 == pinVal)
		{
			// Set the state of pin
			IOSET0 |= 1<<pinNo;
		}
	}
	// if pinNo is in between 100 to 131 then PORT 1
	else if(100<= pinNo && 131>= pinNo)
	{
		// substract 100 to get pin no
		pinNo -= 100;
		// Check if pin no is betwee 16 to 31
		if(16<= pinNo && 31>=pinNo)
		{
			// Select output direction of pin
			IODIR1 |= set <<pinNo;
			// if pinVal is 0 then clear pin 
			if(0 == pinVal)
			{
				 // Clear the state of pin
				IOCLR1 |= 1<<pinNo;
			}
			// if pinVal is 1 then set pin 
			else if (1 == pinVal)
			{
    				// Set the state of pin
				IOSET1 |= 1<<pinNo;
			}
		}
	}
}
/*
* Function Name : void portWrite(int portNo, unsigned char portVal) 
* Decription    : This Function  select port all pins
*/
void portWrite(int portNo, unsigned char portVal)
{
    // Varrriable to iterate for pin 0 to 7
	int i;
    // checking port no is zero 
	if(0 <= portNo && 9>= portNo)
	{
        // checking for P0.0 to P0.7 pin
		if(0 == portNo)
		{
            // iterate to write value for p0.0 - p0.7 pin
			for(i=0; i<8;i++)
			{
				// check i-th bit of portVal is 1
				if(portVal>>i&1)
				{
                    // Function call to write 1 on pin
					pinWrite(i,1);
				}	
				else
				{
                    // Function call to write 0 on pin
					pinWrite(i,0);
				}
			}
		}
		// checking for P0.8 to P0.15 pin
		else if(1== portNo)
		{
			 // iterate to write value for p0.8 - p0.15 pin
			for(i=0; i<8;i++)
			{
				// check i-th bit of portVal is 1
				if(portVal>>i&1)
				{
				  	// Function call to write 1 on pin
					pinWrite(8+i,1);
				}
				else
				{
                    // Function call to write 0 on pin
					pinWrite(8+i,0);
				}
			}
		}
		// checking for P0.16 to P0.23 pin
		else if(2== portNo)
		{
			 // iterate to write value for p0.16 - p0.23 pin
			for(i=0; i<8;i++)
			{
				// check i-th bit of portVal is 1
				if(portVal>>i&1)
				{
					// Function call to write 1 on pin
					pinWrite(16+i,1);
				}
				else
				{
					// Function call to write 0 on pin
					pinWrite(16+i,0);
				}
			}
		}
		// checking for P0.24 to P0.31 pin
		else if(3== portNo)
		{
			// iterate to write value for p0.24 - p0.31 pin
			for(i=0; i<8;i++)
			{
				// check i-th bit of portVal is 1
				if(portVal>>i&1)
				{
					// Function call to write 1 on pin
					pinWrite(24+i,1);
				}
				else
				{
					// Function call to write 0 on pin
					pinWrite(24+i,0);
				}
			}
		}
		else
		{
			
		}
	}
	// checking port no is one
	else if(10 <= portNo && 19>= portNo)
	{
		// checking for P1.16 to P1.23 pin
		if(12== portNo)
		{
			// iterate to write value for P1.16 - P1.23 pin
			for(i=0; i<8;i++)
			{
				// check i-th bit of portVal is 1
				if(portVal>>i&1)
				{
					// Function call to write 1 on pin
					pinWrite(116+i,1);
				}
				else
				{
					// Function call to write 0 on pin
					pinWrite(116+i,0);
				}
			}
		}
		// checking for P1.24 to P1.31 pin
		else if(13== portNo)
		{
			// iterate to write value for P1.24 - P1.31 pin
			for(i=0; i<8;i++)
			{
				// check i-th bit of portVal is 1
				if(portVal>>i&1)
				{
					// Function call to write 1 on pin
					pinWrite(124+i,1);
				}
				else
				{
					// Function call to write 0 on pin
					pinWrite(124+i,0);
				}
			}
		}
		else 
		{
		}
	}
}
/*
* Function Name :  int pinRead(int pinNo)
* Decription    : This Function to read the digital state of specific pin *                 number                 
*/
int pinRead(int pinNo)
{
	// Check if the pin number is between P0.0 and P0.31
	if(0<= pinNo && 31>= pinNo)
	{
		 // Configure the pin as input by clearing
		IODIR0&=~(1<<pinNo);
		 // Read the state of the pin from IOPIN0
		return IOPIN0>>pinNo&1;
	}
	// Check if the pin number is between P1.0 and P1.31
	else if(100<= pinNo && 131>= pinNo)
	{
			pinNo -= 100;
			// Check if the pin number is between P1.16 and P1.31
			if(16<= pinNo && 31>=pinNo)
			{
				// Configure the pin as input by clearing
				IODIR1&=~(1<<pinNo);
				// Read the state of the pin from IOPIN1
				return IOPIN1>>pinNo&1;
			}
	}		
}

