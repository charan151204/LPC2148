#include <lpc214x.h>

#define LCD_DATA_MASK 0xFF      // P0.0 to P0.7 for D0?D7
#define RS (1 << 8)             // P0.8
#define RW (1 << 9)             // P0.9
#define EN (1 << 10)            // P0.10

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 6000; j++);
}

void lcd_command(unsigned char cmd) {
    IOCLR0 = LCD_DATA_MASK | RS | RW | EN;  // Clear all
    IOSET0 = cmd;               // Set data pins
    IOCLR0 = RS;                // RS = 0 (command)
    IOCLR0 = RW;                // RW = 0 (write)
    IOSET0 = EN;                // EN = 1
    delay_ms(2);
    IOCLR0 = EN;                // EN = 0
}

void lcd_data(unsigned char data) {
    IOCLR0 = LCD_DATA_MASK | RS | RW | EN;
    IOSET0 = data;
    IOSET0 = RS;                // RS = 1 (data)
    IOCLR0 = RW;                // RW = 0 (write)
    IOSET0 = EN;
    delay_ms(2);
    IOCLR0 = EN;
}

void lcd_string(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void lcd_init(void) {
    IODIR0 |= LCD_DATA_MASK | RS | RW | EN;

    delay_ms(20);
    lcd_command(0x38);  // 8-bit, 2-line, 5x7 font
    lcd_command(0x0C);  // Display ON, cursor OFF
    lcd_command(0x06);  // Entry mode
    lcd_command(0x01);  // Clear display
    delay_ms(2);
}



