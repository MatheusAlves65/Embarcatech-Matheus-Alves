#ifndef SSD1306_H_
#define SSD1306_H_

#include "hardware/i2c.h"

typedef struct {
    uint8_t width;
    uint8_t height;
    i2c_inst_t* i2c;
    uint8_t address;
    uint8_t buffer[128 * 64 / 8];
} ssd1306_t;

void ssd1306_init(ssd1306_t* oled, uint8_t width, uint8_t height, i2c_inst_t* i2c, uint8_t address);
void ssd1306_show(const ssd1306_t* oled);
void ssd1306_clear(ssd1306_t* oled);
void ssd1306_draw_string(ssd1306_t* oled, uint8_t x, uint8_t y, uint8_t size, const char* str);

#endif // SSD1306_H_