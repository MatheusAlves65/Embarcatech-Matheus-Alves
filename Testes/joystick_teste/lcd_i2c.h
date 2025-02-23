#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "hardware/i2c.h"

void lcd_init(uint8_t addr, uint8_t cols, uint8_t rows, i2c_inst_t *i2c);
void lcd_clear();
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_printf(const char *format, ...);

#endif