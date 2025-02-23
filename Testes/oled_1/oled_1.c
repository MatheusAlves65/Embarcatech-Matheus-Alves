#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"

#define I2C_PORT i2c0
#define SDA_PIN 14
#define SCL_PIN 15

void setup_i2c() {
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void i2c_scan() {
    printf("I2C Bus Scan:\n");
    for (int addr = 0; addr < (1 << 7); ++addr) {
        int ret = i2c_write_blocking(I2C_PORT, addr, NULL, 0, false);
        if (ret >= 0) {
            printf("Found I2C device at address 0x%02x\n", addr);
        }
    }
}

int main() {
    stdio_init_all();
    setup_i2c();
    i2c_scan();

    // Initialize the OLED display
    ssd1306_t oled;
    ssd1306_init(&oled, 128, 64, I2C_PORT, 0x3C);

    while (1) {
        ssd1306_clear(&oled);
        ssd1306_draw_string(&oled, 0, 0, 1, "Hello, World!");
        ssd1306_show(&oled);
        sleep_ms(1000);

        ssd1306_clear(&oled);
        ssd1306_draw_string(&oled, 0, 0, 1, "Raspberry Pi Pico W");
        ssd1306_show(&oled);
        sleep_ms(1000);
    }

    return 0;
}