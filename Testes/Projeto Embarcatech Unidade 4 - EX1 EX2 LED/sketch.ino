#include "pico/stdlib.h"

#define PINO_LED 4
#define PINO_BOTAO 26
#define PINO_BOTAOB 18

int contagem_pressoes_botao = 0;
bool botao_ja_pressionado = false;
bool botaob_ja_pressionado = false;

void setup() {
    // Inicializa a comunicação serial
    Serial.begin(9600);

    // Configuração do LED e do botão
    gpio_init(PINO_LED);
    gpio_set_dir(PINO_LED, GPIO_OUT);
    gpio_put(PINO_LED, 0); // Garante que o LED comece apagado

    gpio_init(PINO_BOTAO);
    gpio_set_dir(PINO_BOTAO, GPIO_IN);
    gpio_pull_down(PINO_BOTAO);

    gpio_init(PINO_BOTAOB);
    gpio_set_dir(PINO_BOTAOB, GPIO_IN);
    gpio_pull_down(PINO_BOTAOB);
}

void loop() {
    // Verifica se o botão A foi pressionado
    if (gpio_get(PINO_BOTAO)) {
        if (!botao_ja_pressionado) {
            contagem_pressoes_botao++;
            botao_ja_pressionado = true;
        }
    } else {
        botao_ja_pressionado = false;
    }

    // Verifica se o botão A foi pressionado 5 vezes
    if (contagem_pressoes_botao >= 5) {
        contagem_pressoes_botao = 0;

        // Pisca o LED por 10 segundos a 10 Hz
        for (int i = 0; i < 100; i++) {
            // Verifica se o botão B foi pressionado
            if (gpio_get(PINO_BOTAOB)) {
                if (!botaob_ja_pressionado) {
                    Serial.println("Botão B pressionado! Frequência do LED: 1 Hz");
                    botaob_ja_pressionado = true;
                }
                gpio_put(PINO_LED, 1);
                sleep_ms(500);
                gpio_put(PINO_LED, 0);
                sleep_ms(500);
            } else {
                botaob_ja_pressionado = false;
                gpio_put(PINO_LED, 1);
                sleep_ms(50);
                gpio_put(PINO_LED, 0);
                sleep_ms(50);
            }
        }
    }

    // Verifica se o botão B foi pressionado fora do loop de piscar
    if (gpio_get(PINO_BOTAOB)) {
        if (!botaob_ja_pressionado) {
            Serial.println("Botão B pressionado!");
            botaob_ja_pressionado = true;
        }
    } else {
        botaob_ja_pressionado = false;
    }

    sleep_ms(10); // Pequeno delay para evitar uso excessivo da CPU
}