#ifndef __LCD_H__
#define __LCD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// LCD default Address
#define LCD_ADDRESS 0x27

// flags for data/command mode
#define LCD_DATA_MODE 1
#define LCD_CMD_MODE 0 

// Commands
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_RETURN_HOME 0x02
#define LCD_ENTRY_MODE_SET 0x04
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_CURSOR_SHIFT 0x10
#define LCD_FUNCTION_SET 0x20
#define LCD_SET_CGRAM_ADDR 0x40
#define LCD_SET_DDRAM_ADDR 0x80

// flags for display entry mode
#define LCD_ENTRY_RIGHT 0x00
#define LCD_ENTRY_LEFT 0x02
#define LCD_ENTRY_SHIFT_INCREMENT 0x01
#define LCD_ENTRY_SHIFT_DECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAY_ON 0x04
#define LCD_DISPLAY_OFF 0x00
#define LCD_CURSOR_ON 0x02
#define LCD_CURSOR_OFF 0x00
#define LCD_BLINK_ON 0x01
#define LCD_BLINK_OFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAY_MOVE 0x08
#define LCD_CURSOR_MOVE 0x00
#define LCD_MOVE_RIGHT 0x04
#define LCD_MOVE_LEFT 0x00

// flags for function set
#define LCD_4BIT_MODE 0x00
#define LCD_8BIT_MODE 0x10  
#define LCD_1LINE 0x00
#define LCD_2LINE 0x08
#define LCD_5x10_DOTS 0x04
#define LCD_5x8_DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT_ON 0x08
#define LCD_BACKLIGHT_OFF 0x00

// flags for cursor line
#define LCD_CURSOR_LINE1 0x80
#define LCD_CURSOR_LINE2 0xC0

#define ENB 0b00000100 // Enable bit
#define RWB 0b00000010 // Read/Write bit
#define RSB 0b00000001 // Register select bit

void lcd_init(int fd);

void lcd_backlight_on();

void lcd_backlight_off();

void lcd_toggle_enable(int bits);

void lcd_byte(int bits, int mode);

void lcd_write_string(char *str);

void lcd_cursor_move(int position);

void lcd_delay(int secend);

void lcd_clear();

#endif