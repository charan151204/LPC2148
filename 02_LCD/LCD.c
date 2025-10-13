#include<lpc21xx.h>

#define LCD_D 0xFF


#define RS 1<<8
#define RW 1<<9
#define E 1<<10

void lcd_init(void);
void lcd_command(unsigned char );
void lcd_data(unsigned char );

void delay_ms(unsigned int n)
{
	int i,j;
	for(i=0;i<n;i++)
	for(j=0;j<12000;j++);
}

int main()
{
	unsigned char *s="WELCOME!!!";
	lcd_init();
	lcd_command(0x80);
	while(*s)
	{
		lcd_data(*s);
		s++;
	}
	
}

void lcd_init()
{
	IODIR0=LCD_D|RS|RW|E;
	IOCLR0=RW;
	lcd_command(0x01);
	lcd_command(0x02);
	lcd_command(0x0c);
	lcd_command(0x38);
	lcd_command(0x80);
	
}

void lcd_command(unsigned char cmd)
{
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
	
}

void lcd_data(unsigned char data)
{
	IOCLR0=LCD_D;
	IOSET0=data;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;

}

