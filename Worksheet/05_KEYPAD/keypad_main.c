#include <LPC214x.h>
#include <string.h>
#include "lcd_display_1.h"
#include "keypad_1.h"
#include "timer.h"

int main(void)
{
    char password[6]; // 5 digits + null terminator
    int i;

    lcd_init();
    lcd_command(0x01);
    delayms(2);

    lcd_command(0x80);
    lcd_string("Enter Password:");
    lcd_command(0xC0);

    for(i=0; i<5; i++)
    {
        password[i] = key_scan();  // Read keypad
        lcd_data('*'); 			// Show asterisk
			  lcd_command(0xC0 + i);
    }
    password[5] = '\0';           // Null terminate string

    // Check password
    if(strcmp(password,"12345")==0)
    {
        lcd_command(0x01); 
			delayms(2);
        lcd_command(0x80);
        lcd_string("PASSWORD CORRECT");
    }
    else
    {
        lcd_command(0x01); delayms(2);
        lcd_command(0x80);
        lcd_string("PASSWORD INVALID");
    }

    while(1); // Stop here
}


