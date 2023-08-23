#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "lcd.h"

int file_descriptor;
int backlight_status = LCD_BACKLIGHT_ON;

void lcd_init(int fd) {
    file_descriptor = fd;
    
    // 디스플레이 초기화
    lcd_byte(0x33, LCD_CMD_MODE);
    lcd_byte(0x32, LCD_CMD_MODE);
    lcd_byte(0x06, LCD_CMD_MODE);
    lcd_byte(0x0C, LCD_CMD_MODE);
    lcd_byte(0x28, LCD_CMD_MODE);
    lcd_byte(0x01, LCD_CMD_MODE); 

    delayMicroseconds(500);
}

void lcd_backlight_on() {
    backlight_status = LCD_BACKLIGHT_ON;
}

void lcd_backlight_off() {
    backlight_status = LCD_BACKLIGHT_OFF, LCD_CMD_MODE;
}

void lcd_toggle_enable(int bits) {
    delayMicroseconds(500);
    wiringPiI2CReadReg8(file_descriptor, (bits | ENB));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(file_descriptor, (bits & ~ENB));
    delayMicroseconds(500);
}

void lcd_byte(int bits, int mode) {
    int bits_high;
    int bits_low;

    bits_high = mode | (bits & 0xF0) | backlight_status;
    bits_low = mode | ((bits << 4) & 0xF0) | backlight_status;

    wiringPiI2CReadReg8(file_descriptor, bits_high);
    lcd_toggle_enable(bits_high);

    wiringPiI2CReadReg8(file_descriptor, bits_low);
    lcd_toggle_enable(bits_low);
}

void lcd_write_string(char *str) {
    while (*str) {
        lcd_byte(*(str++), LCD_DATA_MODE);
    }   
}

// LINE1 = 128, LINE2 = 192
void lcd_cursor_move(int position) {
    lcd_byte(position, LCD_CMD_MODE);
}

void lcd_delay(int secend) {
    delay(secend * 1000);
}

void lcd_clear() {
    lcd_byte(0x01, LCD_CMD_MODE);
    lcd_byte(0x02, LCD_CMD_MODE);
}