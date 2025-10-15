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
void lcd_string(unsigned char *s)
{
    while(*s)
    {
        lcd_data(*s);
        s++;
    }
}