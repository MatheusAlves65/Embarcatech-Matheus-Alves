#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

// Definindo os pinos UART
#define UART0_TX_PIN 0
#define UART0_RX_PIN 1
#define UART1_TX_PIN 4
#define UART1_RX_PIN 5

int main() {
    // Inicializando o stdio
    stdio_init_all();

    // Inicializando a UART0
    uart_init(uart0, 9600);
    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);

    // Inicializando a UART1
    uart_init(uart1, 9600);
    gpio_set_function(UART1_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART1_RX_PIN, GPIO_FUNC_UART);

    // Mensagem inicial
    //printf("Digite um dado para enviar:\n");

    char input;

    while (1) {
        // Lê um caractere do console usando scanf
        scanf(" %c", &input);
            // Limpa o terminal
            //printf("\033[2J\033[H");

            // Envia o caractere lido para a UART1
            uart_putc(uart0, input);

            // Imprime o dado enviado no console
            printf("Dado enviado para UART1: %c\n", input);
        

        // Verifica se há dados disponíveis na UART1
        if (uart_is_readable(uart0)) {
            // Lê o dado da UART1
            char receivedData = uart_getc(uart1);

            // Envia o dado de volta para a UART0 (Serial)
            printf("Dado recebido da UART1: %c\n", receivedData);
        }
    }

    return 0;
}