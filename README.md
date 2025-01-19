# Resumo do Funcionamento do Código

Este código em C é projetado para controlar LEDs e um buzzer utilizando um teclado matricial 4x4 em conjunto com a Raspberry Pi Pico. Ele permite que o usuário interaja com o sistema pressionando teclas no teclado matricial, onde cada tecla executa uma ação específica, como acender LEDs ou ativar o buzzer. Abaixo estão os principais pontos de funcionamento:

## 1. Mapeamento do Teclado Matricial
O teclado matricial possui 4 linhas e 4 colunas, totalizando 16 teclas.
Cada tecla é mapeada para um caractere específico (ex.: '1', '2', '3', 'A', etc.).
A matriz key_map define o layout do teclado.
## 2. Ações Baseadas em Teclas Pressionadas
As ações realizadas pelo sistema são:

- **Tecla '1'**: Acende o LED vermelho por 3 segundos.
- **Tecla '2'**: Acende LED vermelho por 3 segundos, apaga por um segundo, pisca 6 vezes com intervalo de 1 segundo para aceso e apagado.
- **Tecla '3'**: Acende o LED azul por 3 segundos.
- **Tecla '4'**: Acende o LED azul por 3 segundos, apaga, espera 2 segundos e acende novamente por 3 segundos.
- **Tecla '5'**: Acende o LED verde por 3 segundos.
- **Tecla '6'**: Acende LED verde por 3 segundos, apaga por um segundo, pisca 4 vezes com intervalo de 1 segundo para aceso e apagado.
- **Tecla '9'**: Ativa o buzzer, emitindo um som intermitente por 3 segundos.
- **Tecla '0'**: Encerra o programa.

## 3. Leitura do Teclado
A função get_key() verifica qual tecla foi pressionada.
As linhas do teclado são ativadas uma por vez, enquanto as colunas são verificadas para detectar o pressionamento.
Para evitar leituras falsas, um mecanismo de debounce é implementado.
## 4. Controle dos LEDs e do Buzzer
Os LEDs (vermelho, azul, e verde) e o buzzer são controlados individualmente com base na tecla pressionada.
O controle é realizado através da função control_ledsebuzz(), que aciona ou desliga os dispositivos conforme o caractere recebido.
## 5. Configuração Inicial
A função keypad_init() configura os pinos das linhas do teclado como saídas e os pinos das colunas como entradas com pull-up.
A função output_init() inicializa os pinos dos LEDs e do buzzer como saídas e garante que todos comecem apagados/desligados.
## 6. Loop Principal
No loop principal (main()), o programa lê continuamente as teclas pressionadas.
Dependendo da tecla pressionada, o programa executa a ação correspondente até que a tecla '0' seja pressionada, encerrando o programa.
