#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos das linhas e colunas do teclado
#define LIN_1 8
#define LIN_2 7
#define LIN_3 6
#define LIN_4 5
#define COL_1 4
#define COL_2 3
#define COL_3 2
#define COL_4 1

// Definição dos pinos dos LEDs/Buzzer
#define LED_VERMELHO 13 // LED vermelho
#define LED_AZUL 12     // LED ciano
#define LED_VERDE 11    // LED verde
#define Buzzer 10       // Buzzer

// Mapeamento do teclado matricial
const char key_map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Declaração de funções
void control_ledsebuzz(char key);
char get_key();
void keypad_init();
void output_init();

int main()
{
    stdio_init_all();

    // Inicializa o teclado e os LEDs
    keypad_init();
    output_init();
    printf("Teclado Matricial 4x4 - Controle de LEDs\n");

    while (true)
    {
        char key = get_key(); // Lê a tecla pressionada
        printf("Tecla pressionada: %c\n", key);

        // Se a tecla pressionada for '0', sair do loop
        if (key == '0')
        {
            printf("Loop interrompido.\n");
            break; // Sai do loop
        }

        control_ledsebuzz(key); // Controla os LEDs e o buzzer com base na tecla

        sleep_ms(100); // Pequena pausa para evitar leituras repetidas
    }

    return 0;
}

// Inicializa os leds e buzzer
void output_init()
{
    gpio_init(LED_VERMELHO);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERDE);
    gpio_init(Buzzer);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(Buzzer, GPIO_OUT);
    gpio_put(LED_VERMELHO, false);
    gpio_put(LED_AZUL, false);
    gpio_put(LED_VERDE, false);
    gpio_put(Buzzer, false);
}

// Função para controlar os LEDs e buzzer
void control_ledsebuzz(char key)
{
    // Acender o LED vermelho por 3 segundos
    if (key == '1')
    {
        gpio_put(LED_VERMELHO, true);
        sleep_ms(3000);
        gpio_put(LED_VERMELHO, false);
    }
// 2 para pulsos luminosos vermelhos
// Acender o LED azul por 3 segundos
    if(key == '3'){
        gpio_put(LED_AZUL, true);
        sleep_ms(3000);
        gpio_put(LED_AZUL, false);
    }

 // Acender o LED azul por 3 segundos, apagar, esperar 2 segundos e acender novamente por 3 segundos
    else if (key == '4')
    {
        gpio_put(LED_AZUL, true);  // Acende o LED azul
        sleep_ms(3000);            // Aguarda 3 segundos

        gpio_put(LED_AZUL, false); // Apaga o LED azul
        sleep_ms(2000);            // Espera 2 segundos

        gpio_put(LED_AZUL, true);  // Acende novamente o LED azul
        sleep_ms(3000);            // Aguarda mais 3 segundos

        gpio_put(LED_AZUL, false); // Apaga o LED azul novamente
    }

    // Acender o LED verde por 3 segundos
    else if (key == '5')
    {
        gpio_put(LED_VERDE, true);  // Acende o LED verde
        sleep_ms(3000);             // Aguarda 3 segundos
        gpio_put(LED_VERDE, false); // Apaga o LED verde
    }

// Acende LED verde por 3 segundos, apaga por um segundo, pisca 4 vezes com intervalo de 1 segundo para aceso e apagado
    else if (key == '6')
    {
        gpio_put(LED_VERDE, true);
        sleep_ms(3000);
        gpio_put(LED_VERDE, false);
        sleep_ms(1000);
         
        int blink_count = 0;
        while(blink_count < 4)
        {
            gpio_put(LED_VERDE, true);
            sleep_ms(1000);
            gpio_put(LED_VERDE, false);
            sleep_ms(1000);

            blink_count ++;
        }
    }
    else if (key == '8') // Acender os 3 leds por 3 segundos e esperar 2 segundos x8
    {
        for (int i = 0; i < 8; i++) // Repetir 8 vezes
        {
            // Acender os LEDs por 3 segundos
            gpio_put(LED_VERMELHO, true);
            gpio_put(LED_AZUL, true);
            gpio_put(LED_VERDE, true);
            sleep_ms(3000);

            // Apagar os LEDs
            gpio_put(LED_VERMELHO, false);
            gpio_put(LED_AZUL, false);
            gpio_put(LED_VERDE, false);
            sleep_ms(2000);
        }
    }

    // Acionar o buzzer quando a tecla '9' for pressionada
    else if (key == '9')
    {
        int i = 0;
        while (i < 60)
        {
            gpio_put(Buzzer, true);
            sleep_ms(50); 
            gpio_put(Buzzer, false);
            i++;
        }
    }
}


// Função para ler a tecla pressionada
char get_key()
{
    int linhas[] = {LIN_1, LIN_2, LIN_3, LIN_4};
    int colunas[] = {COL_1, COL_2, COL_3, COL_4};

    for (int l = 0; l < 4; l++)
    {
        gpio_put(linhas[l], false); // Ativa a linha atual
        for (int c = 0; c < 4; c++)
        {
            if (!gpio_get(colunas[c]))
            {                 // Verifica se a coluna está em nível baixo
                sleep_ms(10); // Debounce
                if (!gpio_get(colunas[c]))
                {                              // Confirma o pressionamento
                    gpio_put(linhas[l], true); // Desativa a linha
                    return key_map[l][c];
                }
            }
        }
        gpio_put(linhas[l], true); // Desativa a linha atual
    }
    return '\0'; // Nenhuma tecla pressionada
}

// Inicializa os pinos do teclado
void keypad_init()
{
    // Arrays com os pinos das linhas e colunas
    int linhas[] = {LIN_1, LIN_2, LIN_3, LIN_4};
    int colunas[] = {COL_1, COL_2, COL_3, COL_4};

    // Configura as linhas como saída e inicializa em nível alto
    for (int i = 0; i < 4; i++)
    {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], true); // Nível alto
    }

    // Configura as colunas como entrada com pull-up
    for (int i = 0; i < 4; i++)
    {
        gpio_init(colunas[i]);
        gpio_set_dir(colunas[i], GPIO_IN);
        gpio_pull_up(colunas[i]); // Ativa pull-up
    }
}
