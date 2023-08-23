#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "lcd.h"

#define LCD_ADDRESS 0x27

#define INTERVAL 3

int main() {
    if (wiringPiSetup () == -1) exit (1);

    int fd = wiringPiI2CSetup(LCD_ADDRESS);

    lcd_init(fd, LCD_BACKLIGHT_ON);

    char line1[32] = "Hello, World!";
    char line2[32] = "Have a nice day!";

    char line3[32] = "Hello, Raspberry!";
    char line4[32] = "Welcome to System!";

    int count = 0;

    do {    
        lcd_clear(fd, LCD_BACKLIGHT_ON);
        lcd_cursor_move(fd, LCD_BACKLIGHT_ON, LCD_CURSOR_LINE1);
        lcd_write_string(fd, LCD_BACKLIGHT_ON, line1);
        lcd_cursor_move(fd, LCD_BACKLIGHT_ON, LCD_CURSOR_LINE2);
        lcd_write_string(fd, LCD_BACKLIGHT_ON, line2);
        lcd_delay(INTERVAL);

        lcd_clear(fd, LCD_BACKLIGHT_ON);
        lcd_cursor_move(fd, LCD_BACKLIGHT_ON, LCD_CURSOR_LINE1);
        lcd_write_string(fd, LCD_BACKLIGHT_ON, line3);
        lcd_cursor_move(fd, LCD_BACKLIGHT_ON, LCD_CURSOR_LINE2);
        lcd_write_string(fd, LCD_BACKLIGHT_ON, line4);
        lcd_delay(INTERVAL);
    } while (count++ < 10);


    return 0;
}