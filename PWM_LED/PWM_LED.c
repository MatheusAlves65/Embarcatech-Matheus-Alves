#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

//Led Vermelho - 1kHz
const int LED_red = 12;            // Pino do LED conectado

//Led azul - 1kHz
const int LED_blue = 13;            // Pino do LED conectado

//configuração do Duty cicle
const uint16_t LED_STEP = 200;  // Passo de incremento/decremento para o duty cycle do LED
uint16_t led_level = 10000;       // Nível inicial do PWM (duty cycle) para 5%
//Configuração para Frequência de 1Khz
const uint16_t PERIOD_1khz = 60000;   // Período do PWM (valor máximo do contador)
const float DIVIDER_PWM_1khz = 250; // Divisor fracional do clock para o PWM
const uint16_t PERIOD_1khz_red = 12500;   // Período do PWM (valor máximo do contador)
const float DIVIDER_PWM_1khz_red = 10; // Divisor fracional do clock para o PWM

void setup_pwm_red()
{
    int slice_red;
    gpio_set_function(LED_red, GPIO_FUNC_PWM); // Configura o pino do LED para função PWM
    slice_red = pwm_gpio_to_slice_num(LED_red);    // Obtém o slice do PWM associado ao pino do LED
    pwm_set_clkdiv(slice_red, DIVIDER_PWM_1khz_red);    // Define o divisor de clock do PWM
    pwm_set_wrap(slice_red, PERIOD_1khz_red);           // Configura o valor máximo do contador (período do PWM)
    pwm_set_gpio_level(LED_red, led_level);    // Define o nível inicial do PWM para o pino do LED
    pwm_set_enabled(slice_red, true);          // Habilita o PWM no slice correspondente
}
void setup_pwm_blue()
{
    int slice_blue;
    gpio_set_function(LED_blue, GPIO_FUNC_PWM); // Configura o pino do LED para função PWM
    slice_blue = pwm_gpio_to_slice_num(LED_blue);    // Obtém o slice do PWM associado ao pino do LED
    pwm_set_clkdiv(slice_blue, DIVIDER_PWM_1khz);    // Define o divisor de clock do PWM
    pwm_set_wrap(slice_blue, PERIOD_1khz);           // Configura o valor máximo do contador (período do PWM)
    pwm_set_gpio_level(LED_blue, led_level);    // Define o nível inicial do PWM para o pino do LED
    pwm_set_enabled(slice_blue, true);          // Habilita o PWM no slice correspondente
}



int main() {
  stdio_init_all();
  setup_pwm_blue();
  setup_pwm_red();
  //uint up_down = 1; // Variável para controlar se o nível do LED aumenta ou diminui

  while (true) {
    uint up_down = 1; // Variável para controlar se o nível do LED aumenta ou diminui
     // Configura o PWM

        /*pwm_set_gpio_level(LED_blue, led_level); // Define o nível atual do PWM (duty cycle)
        pwm_set_gpio_level(LED_red, led_level); // Define o nível atual do PWM (duty cycle)
        sleep_ms(50);                     // Atraso de 1 segundo
        if (up_down)
        {
            led_level += LED_STEP; // Incrementa o nível do LED
            if (led_level >= PERIOD_1khz)
                up_down = 0; // Muda direção para diminuir quando atingir o período máximo
        }
        else
        {
            led_level -= LED_STEP; // Decrementa o nível do LED
            if (led_level <= LED_STEP)
                up_down = 1; // Muda direção para aumentar quando atingir o mínimo*/
        
    }


  }