////////////////////////////////////////////////
void delay(void);
void pinWrite(int pinNr, int pinValue);
void portWrite(int portNr, int portValue);
int  pinRead (int pinNr);
int  portRead (int portNr);
void pinSelect(int pinNr, int spFunction);

////////////////////////////////////////////////
void portWriteNew(int portNr, unsigned int portValue);
////////////////////////////////////////////////
void pinSelect(int pinNr, int spFunction)
{   
	////////////// pinNr = 0 to 31 for P0, 100 t 131 for P1
	/////////////  spFunction = 0,1,2,3
	int bit0;
    int bit1;
	
	int dummy;
	// pinNr = 5
	// spFunction = 2
	if (spFunction==0)
	{ bit1 = 0; bit0 = 0;}
    else if (spFunction==1)
	{ bit1 = 0; bit0 = 1;}
    else if (spFunction==2)
	{ bit1 = 1; bit0 = 0;}  // 
    else if (spFunction==3)
	{ bit1 = 1; bit0 = 1;}
    else
	dummy=0;	

	if (pinNr >=0 && pinNr <=15)
	{
		// Configue PINSEL0 ==> P0.0 to P0.15
		// Writing a 1
		if (bit0==1)
		PINSEL0 = PINSEL0 | (0x01 << pinNr*2);
		else 
		// Writing a 0
		PINSEL0 = PINSEL0 & ~(0x01 << pinNr*2);
		
		if (bit1==1)
		PINSEL0 = PINSEL0 | (0x01 << (pinNr*2)+1);
		else
		PINSEL0 = PINSEL0 & ~(0x01 << (pinNr*2)+1);
	}
	else if (pinNr >=16 && pinNr <=31)
		
	{
		pinNr = pinNr-16;
		// Configure PINSEL1 ==> P0.16 to P0.31
	
		// Writing a 1
		if (bit0==1)
		PINSEL1 = PINSEL1 | (0x01 << pinNr*2);
		else 
		// Writing a 0
		PINSEL1 = PINSEL1 & ~(0x01 << pinNr*2);
		
		if (bit1==1)
		PINSEL1 = PINSEL1 | (0x01 << (pinNr*2)+1);
		else
		PINSEL1 = PINSEL1 & ~(0x01 << (pinNr*2)+1);
		
		
	}
	else if (pinNr >=116 && pinNr <=131)
	{
		// Configure PINSEL2 ==> P1.16 to P1.31
     pinNr = pinNr - 116;
		
		// Writing a 1
		if (bit0==1)
		PINSEL2 = PINSEL2 | (0x01 << pinNr*2);
		else 
		// Writing a 0
		PINSEL2 = PINSEL2 & ~(0x01 << pinNr*2);
		
		if (bit1==1)
		PINSEL2 = PINSEL2 | (0x01 << (pinNr*2)+1);
		else
		PINSEL2 = PINSEL2 & (~(0x01 << (pinNr*2)+1));

		
	}
	else
	{// do nothing
		dummy = 0;
	}
	
	
}
//////////////////////////////////////////////
int pinRead (int pinNr)
{
	unsigned int mydata;
	
if (pinNr < 100)
{// Port0 Pin  Eg pinNr= 14
// Set the Direction
IODIR0 = (IODIR0 & (~(0x01 << pinNr)));
// Read the Entire Port0
mydata = IOPIN0 ;
// Check for the target bit, return 0 or 1
if ((mydata & (0x01<< pinNr))==0)
	return 0;
else
	return 1;
	
}
else
{// Port1 Pin
pinNr = pinNr-100;
// Set the direction of Port1 as intput
IODIR1 = IODIR1 & (~(0x01 << pinNr)) ;
// read the entire port
mydata = IOPIN1;
if (((mydata & (0x01 << pinNr))==0))
	return 0;
else
	return 1;


	
	
	
}	
	
	
	
}


//////////////////////////////////////////////

int portRead(int portNr)
{unsigned int mydata;

	if (portNr < 10)
	{// Port-0
		if (portNr == 0)
		{// Block0 of P0-> P0.0 t0 P0.7
	    IODIR0 = IODIR0 & (0xFFFFFF00);
		mydata = IOPIN0;
		return (mydata & (0x000000FF));					
		}
		else if(portNr==1)
		{// Block 1 of P0-> P0.8 to P0.15
		IODIR0 = IODIR0 & (0xFFFF00FF);
		mydata = IOPIN0;
		return (mydata & (0x0000FF00))>>8;			
		}
		else if(portNr==2)
		{// Block 2 of P0-> P0.16 to P0.23
		IODIR0 = IODIR0 & (0xFF00FFFF);
		mydata = IOPIN0;
		return (mydata & (0x00FF0000))>>16;			
		}
		else if(portNr==3)
		{// Block 3 of P0-> P0.24 to P0.31
		IODIR0 = IODIR0 & (0x00FFFFFF);
		mydata = IOPIN0;
		return (mydata & (0xFF000000))>>24;			
		}
		else if(portNr==9)
		{// Complete P0
		IODIR0 = IODIR0 & (0x00000000);
		mydata = IOPIN0;
		return (mydata);			
		}
		else
		{
			// Invalid Port Number
		}
		
	}
	else
	{// port-1
if (portNr == 12)
{// Block-2 of P1 -> P1.16 to P1.23
        IODIR1 = IODIR1 & (0xFF00FFFF);
		mydata = IOPIN1;
		return (mydata & (0x00FF0000))>>16;		
}
else if(portNr==13)
		{// Block 3 of P1-> P1.24 to P1.31
		IODIR1 = IODIR1 & (0x00FFFFFF);
		mydata = IOPIN1;
		return (mydata & (0xFF000000))>>24;			
		}
else if(portNr==19)
		{// Complete P1
		IODIR1 = IODIR1 & (0x00000000);
		mydata = IOPIN1;
		return (mydata);			
		}
		else
		{
			// Invalid Port Number
		}
		
		
	}
	
	
}

////////////////////////////////////
void portWrite(int portNr, int portValue)
{
	int i;
	
	// portNr = 0,1,2,3 for P0
	// portNr = 10,11,12,13 for P1
	// portValue = 0x00 to 0xFF
if (portNr <10)
{
// P0
	if (portNr==0)
	{
   // Block0 (P0.0 to P0.7)
		for(i=0;i<8;i++)
		{
			if((portValue & (0x01 << i))==0)
				pinWrite(i,0);
			else
				pinWrite(i,1);
		}
  }
	
	else if (portNr==1)
	{
    // Block1 -P0.8 to P0.15
		for(i=0;i<8;i++)
		{
			if((portValue & (0x01 << i))==0)
				pinWrite(i+8,0);
			else
				pinWrite(i+8,1);
		}
		
  }
	else if (portNr==2)
	{
    // Block2
		for(i=0;i<8;i++)
		{
			if((portValue & (0x01 << i))==0)
				pinWrite(i+16,0);
			else
				pinWrite(i+16,1);
		}
  }
	else if (portNr==3)
	{
    // Block3
		for(i=0;i<8;i++)
		{
			if((portValue & (0x01 << i))==0)
				pinWrite(i+24,0);
			else
				pinWrite(i+24,1);
		}
  }
	else
	{
  }
}
else
{
// P1
	if (portNr == 12)
	{// Block2 of P1 -> P1.16 to P1.23 => 116 to 123
   
		for(i=0;i<8;i++)
		{
			if((portValue & (0x01 << i))==0)
				pinWrite(116+i,0);
			else
				pinWrite(116+i,1);
		}
		
		
  }
	else if (portNr == 13)
	{ // Block3 of P1 => P1.24 to P1.31 => 124 to 131 

		for(i=0;i<16;i++)
		{
			if((portValue & (0x01 << i))==0)
				pinWrite(124+i,0);
			else
				pinWrite(124+i,1);
		}
  }
	else
	{

  }

}




}



////////////////////////////////////////////////

void delay(void)
{
unsigned int i;
for(i=0;i< 500000;i++);
}


/////////////////////////////////////////////////////////
void pinWrite(int pinNr, int pinValue)
{
// pinNr = 0 to 31 for P0
// pinNr = 100 to 131 for P1
// pinValue = 0 or 1

// find whether the pin is in P0 or P1
// Eg pinWrite(29,1);
// Eg pinWrite(129,0);

if (pinNr < 100)
{
// Port 0
// Eg pinWrite(29,1);
// Set the Direction of PinNr as Output	
IODIR0 = IODIR0 | (0x01 << pinNr);
// Check for pinValue.	
if (pinValue == 0)
IOCLR0 = IOCLR0 | (0x01 << pinNr);
else
IOSET0 = IOSET0 | (0x01 << pinNr);	
	
}
else
{
// Port1
pinNr = pinNr - 100;
	
// Set the Direction of Port-1
	IODIR1 = IODIR1 | (0x01 << pinNr);
// Check the pin Value
if (pinValue == 0)
IOCLR1 = IOCLR1 | (0x01 << pinNr);
else
IOSET1 = IOSET1 | (0x01 << pinNr);	
	
	

	

}	
	





}



void portWriteNew(int portNr, unsigned int portValue)
{
	int i;
// check whether it is P0 or P1
if (portNr < 10)
{ // Port 0
	if (portNr == 0) // Block0-> P0.0 to P0.7
	{
    IODIR0 = IODIR0 | (0xFF);
		IOSET0 = IOSET0 | (portValue);
		IOCLR0 = IOCLR0 | ~(portValue);
// 		for(i=0;i<8;i++)
// 		{
// 		if((portValue & (0x01 << i))==0)
// 			pinWrite(i,0);
// 		else
// 			pinWrite(i,1);
// 	  }
		
  }
	
	else if(portNr==1) // Port0 B1 -> P0.8 to P0.15
	{

		IODIR0 = IODIR0 | (0xFF00);
		IOSET0 = IOSET0 | (portValue << 8);
		IOCLR0 = IOCLR0 | (~(portValue)) <<8;

  }
	else if(portNr==2) // Port0 B2 -> P0.16 to P0.23
	{

		IODIR0 = IODIR0 | (0xFF0000);
		IOSET0 = IOSET0 | (portValue << 16);
		IOCLR0 = IOCLR0 | (~(portValue)) <<16;

  }
	else if(portNr==3) // Port0 B3 -> P0.24 to P0.31
	{

		IODIR0 = IODIR0 | (0xFF000000);
		IOSET0 = IOSET0 | (portValue << 24);
		IOCLR0 = IOCLR0 | (~(portValue)) <<24;

  }
	else if(portNr==9) // Port0 -> P0.0 t0 P0.31
	{

		IODIR0 = IODIR0 | (0xFFFFFFFF);
		IOSET0 = IOSET0 | (portValue);
		IOCLR0 = IOCLR0 | ~(portValue) ;

  }
	else
	{}
		


}
else
{
// Port-1
	if(portNr==12) // Port1 B2 -> P1.16 to P1.23
	{

		IODIR1 = IODIR1 | (0x00FF0000);
		IOSET1 = IOSET1 | (portValue << 16);
		IOCLR1 = IOCLR1 | (~(portValue)) << 16;

  }
	
	else if(portNr==13) // Port1 B3 -> P1.24 to P1.31
	{

		IODIR1 = IODIR1 | (0xFF000000);
		IOSET1 = IOSET1 | (portValue << 24);
		IOCLR1 = IOCLR1 | (~(portValue)) << 24;

  }
	if(portNr== 19) // Port1 -> P1.0 to P1.31
	{

		IODIR1 = IODIR1 | (0xFFFFFFFF);
		IOSET1 = IOSET1 | (portValue);
		IOCLR1 = IOCLR1 | ~(portValue) ;

  }
	else
	{}


}



}
