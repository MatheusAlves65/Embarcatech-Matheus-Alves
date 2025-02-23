### Explicação do Código

#### CMakeLists.txt
Este arquivo configura o ambiente de desenvolvimento para o projeto. Ele especifica o uso do SDK do Raspberry Pi Pico e define as configurações do compilador e do projeto.

#### Gpios_init.c
Este arquivo contém funções para inicializar o hardware do projeto, como ADC, I2C, botões, PWM e LEDs. Também inclui funções para ler valores do joystick e controlar buzzer e LEDs.

#### Gpios_init.h
Cabeçalho que declara as funções e define os pinos utilizados no projeto.

#### main.c
O arquivo principal que contém a lógica do programa, incluindo a configuração do display OLED, manipulação do joystick para cadastro e verificação de senha, e controle do estado de bloqueio/desbloqueio.

#### pico_sdk_import.cmake
Arquivo para importar o SDK do Raspberry Pi Pico, garantindo que o SDK esteja disponível para o projeto.

#### ssd1306.c
Implementação das funções para controle do display OLED, incluindo inicialização, limpeza, desenho de texto e atualização do display.

#### ssd1306.h
Cabeçalho que declara as funções e estruturas utilizadas para controlar o display OLED.
