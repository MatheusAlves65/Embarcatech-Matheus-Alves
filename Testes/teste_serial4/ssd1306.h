#ifndef SSD1306_H
#define SSD1306_H

#include "hardware/i2c.h"

typedef struct {
    bool external_vcc;
    uint8_t width;
    uint8_t height;
    uint8_t pages;
    uint8_t address;
    i2c_inst_t *i2c_port;
    uint8_t buffer[128 * 64 / 8];
} SSD1306_t;

void ssd1306_init(SSD1306_t *oled, uint8_t width, uint8_t height, uint8_t address, i2c_inst_t *i2c_port);
void ssd1306_clear(SSD1306_t *oled);
void ssd1306_draw_string(SSD1306_t *oled, uint8_t x, uint8_t y, const char *text, uint8_t size);
void ssd1306_show(SSD1306_t *oled);

#endif // SSD1306_H