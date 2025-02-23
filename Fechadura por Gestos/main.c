#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "Gpios_init.h"

// Instância do display OLED
SSD1306_t oled;

// Função para configurar o display OLED
void setup_oled() {
    oled.external_vcc = false;
    ssd1306_init(&oled, 128, 64, OLED_ADDRESS, I2C_PORT);
}

// Função para armazenar um número no buffer
void store_number_in_buffer(char buffer[], char number, int position) {
    if (position < 0 || position >= BUFFER_SIZE) {
        printf("Invalid position. Must be between 0 and %d.\n", BUFFER_SIZE - 1);
        return;
    }
    buffer[position] = number;
}

// Função para exibir uma mensagem no display
void display_message(const char* message, int x, int y, uint8_t size) {
    ssd1306_draw_string(&oled, x, y, message, size); // Desenha a mensagem no display na posição especificada
    ssd1306_show(&oled); // Atualiza o display com a nova mensagem
}

// Função para exibir a senha cadastrada no display
void display_password(const char* password) {
    char buffer[30];
    ssd1306_draw_string(&oled, 0, 0, "CADASTRE SUA SENHA:", 1); // Desenha a mensagem no display
    snprintf(buffer, sizeof(buffer), "Senha: %s", password);
    ssd1306_draw_string(&oled, 0, 20, buffer, 1); // Desenha a senha no display com tamanho de fonte maior
    ssd1306_show(&oled); // Atualiza o display com a nova mensagem
}

// Função para exibir a tela de confirmação
void display_confirmation_screen() {
    display_message("Confirmar ?", 0, 0, 2);
    display_message("Press A ", 0, 30, 2);
    ssd1306_show(&oled); // Atualiza o display com a nova mensagem
}

// Função para exibir a mensagem de bloqueio
void display_confirmation_lock() {
    display_message("Fechado", 20, 20, 2);
    beep_and_blink(BUZEER1,led_red, 1000, 0x7FFF, 0x7FFF, 0x0000, 0x0000); // Toca o buzzer no pino 10 e acende o LED vermelho por 500ms

    ssd1306_show(&oled); // Atualiza o display com a nova mensagem
}

// Função para exibir a mensagem de abertura
void display_confirmation_open() {
    display_message("Aberto", 20, 20, 2);
    beep_and_blink(BUZEER1,led_green, 1000, 0x7FFF, 0x7FFF, 0x0000, 0x0000); // Toca o buzzer no pino 10 e acende o LED vermelho por 500ms
    ssd1306_show(&oled); // Atualiza o display com a nova mensagem
}

// Função para exibir a tela de digitação da senha
void display_password_digite(const char* password) {
    char buffer[30];
    snprintf(buffer, sizeof(buffer), "Senha: %s", password);
    ssd1306_draw_string(&oled, 0, 20, buffer, 1); // Desenha a senha no display com tamanho de fonte maior
    ssd1306_show(&oled); // Atualiza o display com a nova mensagem
}

// Função para exibir a tela de digitação da senha sem mostrar a senha
void display_password_digite_hidden(int length) {
    char buffer[30];
    memset(buffer, '*', length);
    buffer[length] = '\0';
    ssd1306_draw_string(&oled, 0, 20, buffer, 1); // Desenha asteriscos no display
    ssd1306_show(&oled); // Atualiza o display com a nova mensagem
}

// Função para lidar com o movimento do joystick
void Cadastro_senha(char* buffer, int* i, bool* in_center, uint16_t x_value, uint16_t y_value) {
    
    if (*in_center) {
        if (x_value <= 100) {
            store_number_in_buffer(buffer, '1', *i);
            display_password(buffer);
            (*i)++;
            *in_center = false;
        } else if (x_value >= 4000) {
            store_number_in_buffer(buffer, '2', *i);
            display_password(buffer);
            (*i)++;
            *in_center = false;
        } else if (y_value <= 100) {
            store_number_in_buffer(buffer, '3', *i);
            display_password(buffer);
            (*i)++;
            *in_center = false;
        } else if (y_value >= 4000) {
            store_number_in_buffer(buffer, '4', *i);
            display_password(buffer);
            (*i)++;
            *in_center = false;
        }
    }

    // Verifica se o joystick voltou para o centro
    if (x_value > 100 && x_value < 4000 && y_value > 100 && y_value < 4000) {
        *in_center = true;
    }
}

void Verificacao_senha(char* buffer, int* i, bool* in_center, uint16_t x_value, uint16_t y_value) {
    printf("Verificacao_senha \n");
    if (*in_center) {
        if (x_value <= 100) {
            store_number_in_buffer(buffer, '1', *i);
            display_password_digite_hidden(*i + 1);
            (*i)++;
            *in_center = false;
        } else if (x_value >= 4000) {
            store_number_in_buffer(buffer, '2', *i);
            display_password_digite_hidden(*i + 1);
            (*i)++;
            *in_center = false;
        } else if (y_value <= 100) {
            store_number_in_buffer(buffer, '3', *i);
            display_password_digite_hidden(*i + 1);
            (*i)++;
            *in_center = false;
        } else if (y_value >= 4000) {
            store_number_in_buffer(buffer, '4', *i);
            display_password_digite_hidden(*i + 1);
            (*i)++;
            *in_center = false;
        }
    }

    // Verifica se o joystick voltou para o centro
    if (x_value > 100 && x_value < 4000 && y_value > 100 && y_value < 4000) {
        *in_center = true;
    }
}

// Função para lidar com a confirmação da senha
void handle_password_confirmation(char* senha, char* senha_digitada) {
    int i = 0;
    bool in_center = true;
    uint16_t prev_x_value = 0;
    uint16_t prev_y_value = 0;
    uint16_t x_value, y_value;

    // Exibe a tela de digitação da senha
    display_password_digite_hidden(0);

    while (true) {
        read_joystick(&x_value, &y_value);

        if (x_value != prev_x_value || y_value != prev_y_value) {
            Verificacao_senha(senha_digitada, &i, &in_center, x_value, y_value);

            // Imprime o conteúdo do buffer
            printf("Senha digitada: %s\n", senha_digitada);

            prev_x_value = x_value;
            prev_y_value = y_value;

            // Verifica se a senha foi completamente digitada
            if (i >= BUFFER_SIZE) {
                if (strcmp(senha, senha_digitada) == 0) {
                    ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens
                    display_message("Senha", 20, 0, 2);
                    display_message("Correta", 200, 30, 2);
                    sleep_ms(2000); // Adiciona um pequeno delay antes de iniciar a verificação da senha digitada
                    ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens
                    printf("aberto\n");
                    return; // Sai da função após a confirmação da senha

                } else {
                    ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens
                    display_message("Senha", 30, 0, 2);
                    display_message("Errada", 30, 30, 2);
                    printf("Senha errada\n");
                    sleep_ms(1000);
                    ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens
                    memset(senha_digitada, 0, sizeof(senha_digitada)); // Limpa o buffer da senha digitada
                    i = 0;
                    display_message("Digite novamente:", 0, 0, 1);
                    display_password_digite_hidden(0); // Exibe a tela de digitação da senha novamente
                }
            }
        }

        // Mantém o programa em execução para exibir a mensagem
        sleep_ms(100);
    }
}

void handle_lock_unlock(char* senha) {
    char senha_digitada[BUFFER_SIZE + 1] = {0}; // Inicializa o buffer com zeros e espaço para o terminador nulo

    while (true) {
        // Após a confirmação da senha, o sistema está aberto
        // O usuário deve digitar a senha novamente para fechar
        ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens
        display_message("Digite sua senha ", 0, 0, 1);
        display_message("para abrir: ", 0, 10, 1);
        handle_password_confirmation(senha, senha_digitada);
        display_confirmation_open();
        // Após a confirmação da senha, o sistema está fechado
        // O usuário deve digitar a senha novamente para abrir
        ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens
        display_message("Digite sua senha ", 0, 0, 1);
        display_message("para fechar: ", 0, 10, 1);
        handle_password_confirmation(senha, senha_digitada);
        display_confirmation_lock();
    }
}

int main() {
    char senha[BUFFER_SIZE + 1] = {0}; // Inicializa o buffer com zeros e espaço para o terminador nulo

    initialize_hardware();
    setup_oled();

    while (true) {
        int i = 0;
        uint16_t prev_x_value = 0;
        uint16_t prev_y_value = 0;
        bool in_center = true;
        bool password_entered = false;

        uint16_t x_value, y_value;

        while (true) {
            read_joystick(&x_value, &y_value);

            if (!password_entered) {
                if (x_value != prev_x_value || y_value != prev_y_value) {
                    Cadastro_senha(senha, &i, &in_center, x_value, y_value);
                    ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens

                    // Imprime o conteúdo do buffer
                    printf("Stored password: %s\n", senha);

                    prev_x_value = x_value;
                    prev_y_value = y_value;

                    // Verifica se a senha foi completamente digitada
                    if (i >= BUFFER_SIZE) {
                        password_entered = true;
                        display_confirmation_screen();
                        ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens

                        // Espera até que um dos botões seja pressionado
                        while (true) {
                            printf("Aguardando confirmação...\n"); // Adiciona mensagem de depuração

                            // Imprime os estados dos botões
                            printf("Estado dos botões: A=%d, B=%d\n", gpio_get(BUTTON_A_PIN), gpio_get(BUTTON_B_PIN));

                            if (gpio_get(BUTTON_A_PIN) == 0) {
                                printf("Senha confirmada: %s\n", senha);
                                display_message("Senha", 30, 0, 2);
                                display_message("Confirmada", 5, 30, 2);
                                beep(BUZEER1, 500, 0x7FFF); // Toca o buzzer no pino 10 por 500ms com 50% de duty cycle
                                beep(BUZEER1, 500, 0x7FFF); // Toca o buzzer no pino 21
                                sleep_ms(2000); // Adiciona um pequeno delay antes de iniciar a verificação da senha digitada
                                ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens
                                display_confirmation_lock();
                                printf("fechado\n");
                                ssd1306_clear(&oled); // Limpa o display antes de desenhar novas mensagens

                                // Inicia o processo de abrir e fechar
                                handle_lock_unlock(senha);
                                break;
                                
                            } 
                            sleep_ms(100); // Adiciona um pequeno delay para evitar polling excessivo
                        }
                    }
                }
            }

            // Mantém o programa em execução para exibir a mensagem
            sleep_ms(100);
        }
    }

    return 0;
}