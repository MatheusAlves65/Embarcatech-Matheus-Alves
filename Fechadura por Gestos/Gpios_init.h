#ifndef GPIOS_INIT
#define GPIOS_INIT

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define I2C_PORT i2c1
#define SDA_PIN 14
#define SCL_PIN 15
#define OLED_ADDRESS 0x3c
#define X_AXIS_PIN 27
#define Y_AXIS_PIN 26
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define BUFFER_SIZE 4
#define BUZEER1 21
#define BUZEER2 10
#define led_red 13
#define led_green 11

void initialize_hardware();
void init_pwm(uint buzzer_pin);
void beep(uint buzzer_pin, uint duration_ms, uint16_t duty_cycle);
void read_joystick(uint16_t* x_value, uint16_t* y_value);
void blink_led(uint led_pin,uint duration_ms, uint16_t duty_cycle) ;
void beep_and_blink(uint buzzer_pin,uint led_pin, uint duration_ms, uint16_t buzzer_duty_cycle, uint16_t red_duty, uint16_t green_duty, uint16_t blue_duty);





#endif // SSD1306_H