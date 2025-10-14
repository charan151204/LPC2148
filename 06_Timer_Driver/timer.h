void initPLL();
void delayus(unsigned int microsecond);
void delayms(unsigned int millisecond);
///////////// PLL ////////////////////////
void initPLL()
{
	PLL0CON = 0x01; // Enable PLL
	PLL0CFG = 0x24; // Msel = 5(Load-4),Psel-2
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55; // Security Key
	while((PLL0STAT & (0x01<<10))==0); // Check for PLock Bit
	PLL0CON = 0x03; // Enable & Connect
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55; // Security Key
	VPBDIV = 0x01; // Pclk = Cclk = 60Mhz
}
///////////// Timer//////////////////////
void delayms(unsigned int millisecond)
{
	T0CTCR = 0x00; // Set the Mode as Timer
	T0PR = 60000-1; // Load the prescalar for 1KHz
	T0TC = 0; // Clear Timer
	T0TCR = 0x01; // start the timer
	while(T0TC < millisecond);
	T0TCR = 0x00; // stop the Timer	
}

void delayus(unsigned int microsecond)
{
	T0CTCR = 0x00; // Set the Mode as Timer
	T0PR = 60-1; // Load the prescalar for 1KHz
	T0TC = 0; // Clear Timer
	T0TCR = 0x01; // start the timer
	while(T0TC < microsecond);
	T0TCR = 0x00; // stop the Timer	
}