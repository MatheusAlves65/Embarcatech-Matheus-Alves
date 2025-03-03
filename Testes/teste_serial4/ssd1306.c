#include "ssd1306.h"
#include <string.h>

// Font data for 5x7 characters
static const uint8_t font[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, // (space)
    0x00, 0x00, 0x5F, 0x00, 0x00, // !
    0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x14, 0x7F, 0x14, 0x7F, 0x14, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
    0x23, 0x13, 0x08, 0x64, 0x62, // %
    0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, // )
    0x14, 0x08, 0x3E, 0x08, 0x14, // *
    0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x50, 0x30, 0x00, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, // /
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x06, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x08, 0x14, 0x22, 0x41, 0x00, // <
    0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x00, 0x41, 0x22, 0x14, 0x08, // >
    0x02, 0x01, 0x51, 0x09, 0x06, // ?
    0x3E, 0x41, 0x5D, 0x59, 0x4E, // @
    0x7C, 0x12, 0x11, 0x12, 0x7C, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x7F, 0x41, 0x41, 0x41, 0x3E, // D
    0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x7F, 0x09, 0x09, 0x09, 0x01, // F
    0x3E, 0x41, 0x41, 0x51, 0x32, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
    0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O
    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x26, 0x49, 0x49, 0x49, 0x32, // S
    0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x3F, 0x40, 0x38, 0x40, 0x3F, // W
    0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x07, 0x08, 0x70, 0x08, 0x07, // Y
    0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x7F, 0x41, 0x41, 0x00, // [
    0x02, 0x04, 0x08, 0x10, 0x20, // "\"
    0x00, 0x41, 0x41, 0x7F, 0x00, // ]
    0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x80, 0x80, 0x80, 0x80, 0x80, // _
    0x00, 0x03, 0x04, 0x00, 0x00, // `
    0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x7F, 0x48, 0x44, 0x44, 0x38, // b
    0x38, 0x44, 0x44, 0x44, 0x20, // c
    0x38, 0x44, 0x44, 0x48, 0x7F, // d
    0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x08, 0x7E, 0x09, 0x01, 0x02, // f
    0x0C, 0x52, 0x52, 0x52, 0x3E, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x20, 0x40, 0x44, 0x3D, 0x00, // j
    0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x7C, 0x04, 0x78, 0x04, 0x78, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x38, 0x44, 0x44, 0x44, 0x38, // o
    0x7C, 0x14, 0x14, 0x14, 0x08, // p
    0x08, 0x14, 0x14, 0x18, 0x7C, // q
    0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x04, 0x3F, 0x44, 0x40, 0x20, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x0C, 0x50, 0x50, 0x50, 0x3C, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x08, 0x36, 0x41, 0x41, // {
    0x00, 0x00, 0x7F, 0x00, 0x00, // |
    0x41, 0x41, 0x36, 0x08, 0x00, // }
    0x02, 0x01, 0x02, 0x04, 0x02  // ~
};

static const uint8_t init_cmds[] = {
    0xAE,          // Display off
    0xD5, 0x80,    // Set display clock divide ratio/oscillator frequency
    0xA8, 0x3F,    // Set multiplex ratio (1 to 64)
    0xD3, 0x00,    // Set display offset
    0x40,          // Set start line address
    0x8D, 0x14,    // Enable charge pump regulator
    0x20, 0x00,    // Set memory addressing mode
    0xA1,          // Set segment re-map (A0/A1)
    0xC8,          // Set COM output scan direction
    0xDA, 0x12,    // Set COM pins hardware configuration
    0x81, 0xCF,    // Set contrast control
    0xD9, 0xF1,    // Set pre-charge period
    0xDB, 0x40,    // Set VCOMH deselect level
    0xA4,          // Entire display ON (resume to RAM content display)
    0xA6,          // Set normal display (A6/A7)
    0xAF           // Display ON
};

static void ssd1306_write_cmd(SSD1306_t *oled, const uint8_t *cmd, size_t cmd_len) {
    uint8_t buf[cmd_len + 1];
    buf[0] = 0x00;  // Control byte: Co = 0, D/C# = 0
    memcpy(buf + 1, cmd, cmd_len);
    i2c_write_blocking(oled->i2c_port, oled->address, buf, cmd_len + 1, false);
}

void ssd1306_init(SSD1306_t *oled, uint8_t width, uint8_t height, uint8_t address, i2c_inst_t *i2c_port) {
    oled->width = width;
    oled->height = height;
    oled->pages = height / 8;
    oled->address = address;
    oled->i2c_port = i2c_port;
    memset(oled->buffer, 0, sizeof(oled->buffer));
    ssd1306_write_cmd(oled, init_cmds, sizeof(init_cmds));
}

void ssd1306_clear(SSD1306_t *oled) {
    memset(oled->buffer, 0, sizeof(oled->buffer));
}

void ssd1306_draw_string(SSD1306_t *oled, uint8_t x, uint8_t y, const char *text, uint8_t size) {
    while (*text) {
        char c = *text++;
        if (c < 32 || c > 126) c = 32;
        for (uint8_t i = 0; i < 5; i++) {
            uint8_t line = font[(c - 32) * 5 + i];
            for (uint8_t j = 0; j < 8; j++) {
                if (line & 1) {
                    for (uint8_t sx = 0; sx < size; sx++) {
                        for (uint8_t sy = 0; sy < size; sy++) {
                            oled->buffer[(x + i * size + sx) + ((y + j * size + sy) / 8) * oled->width] |= (1 << ((y + j * size + sy) % 8));
                        }
                    }
                } else {
                    for (uint8_t sx = 0; sx < size; sx++) {
                        for (uint8_t sy = 0; sy < size; sy++) {
                            oled->buffer[(x + i * size + sx) + ((y + j * size + sy) / 8) * oled->width] &= ~(1 << ((y + j * size + sy) % 8));
                        }
                    }
                }
                line >>= 1;
            }
        }
        x += 6 * size;
    }
}

void ssd1306_show(SSD1306_t *oled) {
    for (uint8_t page = 0; page < oled->pages; page++) {
        uint8_t cmd[] = { 0xB0 + page, 0x00, 0x10 };
        ssd1306_write_cmd(oled, cmd, sizeof(cmd));
        uint8_t *buf = oled->buffer + oled->width * page;
        uint8_t temp_buf[oled->width + 1];
        temp_buf[0] = 0x40;
        memcpy(temp_buf + 1, buf, oled->width);
        i2c_write_blocking(oled->i2c_port, oled->address, temp_buf, sizeof(temp_buf), false);
    }
}