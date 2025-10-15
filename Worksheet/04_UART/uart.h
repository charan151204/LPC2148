/////////////////UART/////////////////////////
void initUART(void);
void sendUART(unsigned char mydata);
unsigned char receiveUART(void);
//////////////////////////////////////////////

void initUART(void)
{
    // PINSEL0 = 0x05;
    pinSelect(0, 1); // Set P0.0 to 1st Sp Function
    pinSelect(1, 1); // Set P0.1 to 1st Sp Function
    U0LCR = 0x83;    // 8 bit Mode - DLAB = 1 -> 7th bit 1000 0011	//Pclk/(UART*16) , 60MHz/(9600*16)= 391, 0x0187
    U0DLL = 98;      // 9600 Baud rate @ 15MHz PCLK;
    U0DLM = 0x00;
    U0LCR = 0x03; // 8 bit Mode - DLAB = 0
}
void sendUART(unsigned char mydata)
{
    U0THR = mydata;
    while ((U0LSR & (0X01 << 5)) == 0)
        ; // THRE flag check
}

unsigned char receiveUART(void)
{
    unsigned char mydata;
    while ((U0LSR & (0x01 << 0)) == 0)
        ; // RBRF flag check
    mydata = U0RBR;
    return mydata;
}