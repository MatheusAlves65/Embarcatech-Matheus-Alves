#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "lcd_i2c.h"

// Definindo os pinos GPIO para o joystick e o LED
#define X_PIN 26        // Pino ADC para o eixo X
#define Y_PIN 27        // Pino ADC para o eixo Y
#define BUTTON_PIN 15   // Pino digital para o botão
#define LED_PIN 25      // Pino digital para o LED (pino 25 é o LED embutido do Pico)

// Definindo os pinos GPIO para o I2C do LCD
#define I2C_SDA_PIN 14
#define I2C_SCL_PIN 15

// Endereço I2C do LCD
#define LCD_ADDR 0x27

// Função para inicializar os pinos
void init_gpio() {
    adc_init();
    adc_gpio_init(X_PIN);
    adc_gpio_init(Y_PIN);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

// Função para ler o valor do eixo X
uint16_t read_x() {
    adc_select_input(0);  // Seleciona o canal ADC 0 (X_PIN)
    return adc_read();
}

// Função para ler o valor do eixo Y
uint16_t read_y() {
    adc_select_input(1);  // Seleciona o canal ADC 1 (Y_PIN)
    return adc_read();
}

// Função para ler o estado do botão
bool read_button() {
    return !gpio_get(BUTTON_PIN);
}

int main() {
    stdio_init_all();  // Inicializa o sistema de entrada/saída padrão
    init_gpio();       // Inicializa os pinos GPIO

    // Inicializa o I2C
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicializa o LCD
    lcd_init(LCD_ADDR, 16, 2, i2c0);

    while (1) {
        uint16_t x_value = read_x();
        uint16_t y_value = read_y();
        bool button_pressed = read_button();

        // Controle do LED
        if (button_pressed) {
            gpio_put(LED_PIN, 1);  // Acende o LED
        } else {
            gpio_put(LED_PIN, 0);  // Apaga o LED
        }

        // Imprime os valores no console serial
        printf("X: %u, Y: %u, Button: %s\n", x_value, y_value, button_pressed ? "Pressed" : "Released");

        // Imprime os valores no LCD
        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_printf("X: %u", x_value);
        lcd_set_cursor(0, 1);
        lcd_printf("Y: %u Btn: %s", y_value, button_pressed ? "P" : "R");

        sleep_ms(100);  // Atraso de 100 milissegundos
    }

    return 0;
}