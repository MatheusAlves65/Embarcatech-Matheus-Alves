#include "ssd1306.h"
#include <string.h>

static void ssd1306_command(const ssd1306_t* oled, uint8_t cmd) {
    uint8_t buffer[2] = {0x00, cmd};
    i2c_write_blocking(oled->i2c, oled->address, buffer, 2, false);
}

void ssd1306_init(ssd1306_t* oled, uint8_t width, uint8_t height, i2c_inst_t* i2c, uint8_t address) {
    oled->width = width;
    oled->height = height;
    oled->i2c = i2c;
    oled->address = address;
    memset(oled->buffer, 0, sizeof(oled->buffer));

    static const uint8_t init_sequence[] = {
        0xAE,          // Display OFF
        0x20, 0x00,    // Memory addressing mode
        0xB0,          // Page start address
        0xC8,          // COM scan direction
        0x00, 0x10,    // Set low and high column addresses
        0x40,          // Set start line address
        0x81, 0xFF,    // Contrast control
        0xA1,          // Segment re-map
        0xA6,          // Normal display
        0xA8, 0x3F,    // Multiplex ratio
        0xA4,          // Output follows RAM content
        0xD3, 0x00,    // Display offset
        0xD5, 0xF0,    // Display clock divide ratio/oscillator frequency
        0xD9, 0x22,    // Pre-charge period
        0xDA, 0x12,    // COM pins hardware configuration
        0xDB, 0x20,    // VCOMH deselect level
        0x8D, 0x14,    // Enable charge pump regulator
        0xAF           // Display ON
    };

    for (size_t i = 0; i < sizeof(init_sequence); ++i) {
        ssd1306_command(oled, init_sequence[i]);
    }
}

void ssd1306_show(const ssd1306_t* oled) {
    for (uint8_t page = 0; page < (oled->height / 8); ++page) {
        ssd1306_command(oled, 0xB0 + page);
        ssd1306_command(oled, 0x00);
        ssd1306_command(oled, 0x10);
        i2c_write_blocking(oled->i2c, oled->address, oled->buffer + (page * oled->width), oled->width, false);
    }
}

void ssd1306_clear(ssd1306_t* oled) {
    memset(oled->buffer, 0, sizeof(oled->buffer));
}

void ssd1306_draw_string(ssd1306_t* oled, uint8_t x, uint8_t y, uint8_t size, const char* str) {
    // Simple example function to draw a string
    // You would need to implement this function to draw characters from a font
    // Here we just draw a simple placeholder
    while (*str) {
        if (x + 6 >= oled->width) {
            x = 0;
            y += 8;
            if (y >= oled->height) {
                break;
            }
        }
        for (uint8_t i = 0; i < 6; ++i) {
            oled->buffer[x + (y / 8) * oled->width + i] = 0xFF; // Placeholder for demonstration
        }
        x += 6;
        str++;
    }
}