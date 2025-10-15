
#include<LPC21XX.h>


void uart_init()
{
	PINSEL0 = 0X05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;
}

void uart_tx(unsigned char ch)
{
	U0THR = ch;
	while((U0LSR>>5&1)==0);
}

unsigned char uart_rx()
{
	while((U0LSR&1)==0);
	return U0RBR;
}

void uart_str(unsigned char *str)
{
    while (*str != '\0')  
    {
        uart_tx(*str);   
        str++;
    }
}
void uart_str_rec(unsigned char *s,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		while((U0LSR&1)==0);
		s[i]=U0RBR;
		if(s[i]=='\r')
		{
			s[i]='\0';
			break;
		}
	}
}

