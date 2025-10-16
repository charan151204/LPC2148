#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_string(unsigned char *str);

#endif
