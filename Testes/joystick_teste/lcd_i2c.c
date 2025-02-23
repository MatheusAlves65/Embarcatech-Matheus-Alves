#include <stdio.h>
#include <stdarg.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lcd_i2c.h"

#define LCD_CMD 0
#define LCD_DATA 1

static uint8_t lcd_addr;
static i2c_inst_t *lcd_i2c;
static uint8_t lcd_cols;
static uint8_t lcd_rows;

static void lcd_send(uint8_t value, uint8_t mode) {
    uint8_t data[2] = {mode, value};
    i2c_write_blocking(lcd_i2c, lcd_addr, data, 2, false);
}

void lcd_init(uint8_t addr, uint8_t cols, uint8_t rows, i2c_inst_t *i2c) {
    lcd_addr = addr;
    lcd_i2c = i2c;
    lcd_cols = cols;
    lcd_rows = rows;
    
    sleep_ms(50);
    lcd_send(0x03, LCD_CMD);
    sleep_ms(5);
    lcd_send(0x03, LCD_CMD);
    sleep_ms(5);
    lcd_send(0x03, LCD_CMD);
    sleep_ms(5);
    lcd_send(0x02, LCD_CMD);
    
    lcd_send(0x28, LCD_CMD); // Function set: 4-bit mode, 2 lines, 5x8 dots
    lcd_send(0x0C, LCD_CMD); // Display on, cursor off, blink off
    lcd_send(0x06, LCD_CMD); // Entry mode set: increment automatically, no display shift
    lcd_send(0x01, LCD_CMD); // Clear display
    sleep_ms(5);
}

void lcd_clear() {
    lcd_send(0x01, LCD_CMD);
    sleep_ms(2);
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    static uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
    lcd_send(0x80 | (col + row_offsets[row]), LCD_CMD);
}

void lcd_printf(const char *format, ...) {
    char buffer[32];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    for (char *p = buffer; *p; p++) {
        lcd_send(*p, LCD_DATA);
    }
}