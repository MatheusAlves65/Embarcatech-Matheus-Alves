#include "Gpios_init.h"
#include <string.h>


void initialize_hardware() {
    // Inicializa o ADC
    adc_init();
    adc_gpio_init(X_AXIS_PIN);
    adc_gpio_init(Y_AXIS_PIN);
    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Inicializa os botões
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    init_pwm(BUZEER1);
    init_pwm(BUZEER2);
    init_pwm(led_red);
    init_pwm(led_green);


}


void init_pwm(uint gpiopin) {
    uint slice_num = pwm_gpio_to_slice_num(gpiopin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f); // Ajuste o divisor de clock conforme necessário
    pwm_init(slice_num, &config, true);
    gpio_set_function(gpiopin, GPIO_FUNC_PWM);
}

void beep(uint buzzer_pin, uint duration_ms, uint16_t duty_cycle) {
    uint slice_num = pwm_gpio_to_slice_num(buzzer_pin);
    pwm_set_gpio_level(buzzer_pin, duty_cycle); // Define o duty cycle
    sleep_ms(duration_ms);                      // Mantém o buzzer ligado por 'duration_ms' milissegundos
    pwm_set_gpio_level(buzzer_pin, 0);          // Desliga o buzzer
    sleep_ms(duration_ms);                      // Espera o mesmo tempo com o buzzer desligado
}

void beep_and_blink(uint buzzer_pin,uint led_pin, uint duration_ms, uint16_t buzzer_duty_cycle, uint16_t red_duty, uint16_t green_duty, uint16_t blue_duty) {
    pwm_set_gpio_level(buzzer_pin, buzzer_duty_cycle); // Define o duty cycle do buzzer
    pwm_set_gpio_level(led_pin, red_duty);   // Define o duty cycle para o vermelho
    sleep_ms(duration_ms);                   // Mantém o buzzer e o LED RGB ligados por 'duration_ms' milissegundos
    pwm_set_gpio_level(buzzer_pin, 0);       // Desliga o buzzer
    pwm_set_gpio_level(led_pin, 0);
}


// Função para ler os valores do joystick
void read_joystick(uint16_t* x_value, uint16_t* y_value) {
    adc_select_input(0);
    *x_value = adc_read();
    adc_select_input(1);
    *y_value = adc_read();
}
