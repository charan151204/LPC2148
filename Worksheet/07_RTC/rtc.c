
#include <lpc214x.h>
#include <stdio.h>
#include <stdint.h>
#include "lcd_driver.h"

typedef struct 
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day_of_month;
    uint8_t day_of_week;
    uint16_t day_of_year;
    uint8_t month;
    uint16_t year;
} RTC;


void RTC_Set_Time(RTC set_time) 
{
    SEC   = set_time.seconds;
    MIN   = set_time.minutes;
    HOUR  = set_time.hours;
    DOM   = set_time.day_of_month;
    DOW   = set_time.day_of_week;
    DOY   = set_time.day_of_year;
    MONTH = set_time.month;
    YEAR  = set_time.year;
}

RTC RTC_Get_Time(void) 
{
    RTC time;
    time.seconds      = SEC;
    time.minutes      = MIN;
    time.hours        = HOUR;
    time.day_of_month = DOM;
    time.day_of_week  = DOW;
    time.day_of_year  = DOY;
    time.month        = MONTH;
    time.year         = YEAR;
    return time;
}

int main(void) 
{
    char time_str[17];
    RTC set_time, current_time;

    // Initialize LCD
    lcd_init();

    // Set time: (seconds, minutes, hours, day, weekday, doy, month, year)
    set_time.seconds = 0;
    set_time.minutes = 30;
    set_time.hours   = 02;
    set_time.day_of_month = 23;
    set_time.day_of_week  = 2;
    set_time.day_of_year  = 204;
    set_time.month        = 7;
    set_time.year         = 2025;

    // RTC setup
    CCR = 0x02;  			// Reset clock
    PREINT = 0x01C8;  // For 15MHz PCLK
    PREFRAC = 0x61C0;
    RTC_Set_Time(set_time);
    CCR = 0x01;  			// Enable RTC

    while (1) {
        current_time = RTC_Get_Time();

        sprintf(time_str, "Time: %02d:%02d:%02d", 
                current_time.hours, 
                current_time.minutes, 
                current_time.seconds);

        lcd_command(0x80);       // First line
        lcd_string("Current Time:");
        lcd_command(0xC0);       // Second line
        lcd_string(time_str);

        delay_ms(1000);
    }
}


