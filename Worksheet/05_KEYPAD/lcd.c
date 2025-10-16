#include <lpc21xx.h>

#define LCD_DATA 0xFF   // P0.0-P0.7 for data

#define RS  (1<<8)
#define RW  (1<<9)
#define EN  (1<<10)

void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_string(unsigned char *str);
void delay_ms(unsigned int n);

// Simple delay
void delay_ms(unsigned int n)
{
    int i, j;
    for(i=0; i<n; i++)
        for(j=0; j<12000; j++);
}

// Initialize LCD
void lcd_init()
{
    IODIR0 = LCD_DATA | RS | RW | EN; // Data + control pins output
    IOCLR0 = RW;                       // RW = 0 (write)

    lcd_command(0x38);  // 8-bit, 2-line, 5x7 dots
    lcd_command(0x0C);  // Display ON, Cursor OFF
    lcd_command(0x01);  // Clear display
    lcd_command(0x06);  // Increment cursor
    lcd_command(0x80);  // Move cursor to first line
}

// Send command to LCD
void lcd_command(unsigned char cmd)
{
    IOCLR0 = LCD_DATA;   // Clear data lines
    IOSET0 = cmd;        // Put command on data lines
    IOCLR0 = RS;         // RS = 0 for command
    IOSET0 = EN;         // Pulse EN
    delay_ms(2);
    IOCLR0 = EN;
}

// Send data (character) to LCD
void lcd_data(unsigned char data)
{
    IOCLR0 = LCD_DATA;  // Clear data lines
    IOSET0 = data;      // Put data on lines
    IOSET0 = RS;        // RS = 1 for data
    IOSET0 = EN;        // Pulse EN
    delay_ms(2);
    IOCLR0 = EN;
}

// Display a null-terminated string
void lcd_string(unsigned char *str)
{
    while(*str)         // Loop until null character
    {
        lcd_data(*str); // Send each character
        str++;
    }
}


