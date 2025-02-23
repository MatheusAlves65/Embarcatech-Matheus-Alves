#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define DS1307_ADDR 0x68

void i2c_write_byte(uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    i2c_write_blocking(I2C_PORT, DS1307_ADDR, buf, 2, false);
}

uint8_t i2c_read_byte(uint8_t reg) {
    uint8_t data;
    i2c_write_blocking(I2C_PORT, DS1307_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, DS1307_ADDR, &data, 1, false);
    return data;
}

uint8_t dec_to_bcd(uint8_t val) {
    return ((val / 10 * 16) + (val % 10));
}

uint8_t bcd_to_dec(uint8_t val) {
    return ((val / 16 * 10) + (val % 16));
}

void set_time(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
    i2c_write_byte(0x00, dec_to_bcd(second)); // segundos
    i2c_write_byte(0x01, dec_to_bcd(minute)); // minutos
    i2c_write_byte(0x02, dec_to_bcd(hour));   // horas
    i2c_write_byte(0x04, dec_to_bcd(day));    // dia
    i2c_write_byte(0x05, dec_to_bcd(month));  // mês
    i2c_write_byte(0x06, dec_to_bcd(year));   // ano
}

void get_time(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *minute, uint8_t *second) {
    *second = bcd_to_dec(i2c_read_byte(0x00));
    *minute = bcd_to_dec(i2c_read_byte(0x01));
    *hour = bcd_to_dec(i2c_read_byte(0x02));
    *day = bcd_to_dec(i2c_read_byte(0x04));
    *month = bcd_to_dec(i2c_read_byte(0x05));
    *year = bcd_to_dec(i2c_read_byte(0x06));
}

int main() {
    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    // Configurar a data e hora: 24/09/2024 - 13:27:00
    set_time(24, 9, 24, 13, 27, 0);

    while (1) {
        uint8_t year, month, day, hour, minute, second;
        get_time(&year, &month, &day, &hour, &minute, &second);
        printf("Data e Hora: %02u/%02u/20%02u %02u:%02u:%02u\n", day, month, year, hour, minute, second);
        sleep_ms(5000);
    }

    return 0;
}