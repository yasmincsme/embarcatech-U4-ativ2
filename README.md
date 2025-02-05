# Atividade 2: Temporizador de um Disparo (One Shot)

## Descrição
Este projeto implementa um sistema de temporização para acionamento de LEDs a partir do clique em um botão (pushbutton), utilizando a função `add_alarm_in_ms()` do Pico SDK. O objetivo é controlar o acionamento progressivo e o desligamento dos LEDs conforme um temporizador configurado para 3 segundos.

## Componentes Utilizados
- **Microcontrolador**: Raspberry Pi Pico W
- **LEDs**: Azul, vermelho e verde
- **Resistores**: 3 unidades de 330 Ω
- **Botão (Pushbutton)**

## Requisitos do Projeto
1. Ao pressionar o botão, todos os LEDs são ligados simultaneamente.
2. A cada 3 segundos (3000 ms), um LED é desligado, até que todos se apaguem.
3. A lógica de controle dos LEDs deve ser implementada dentro de funções de callback do temporizador, similar à `turn_off_callback()` abordada em aula.
4. O botão deve ser desativado enquanto o ciclo de temporização estiver em execução, permitindo uma nova interação apenas quando todos os LEDs estiverem apagados.
5. Deve-se realizar um experimento prático com a ferramenta BitDogLab, utilizando:
   - **LED RGB** nos GPIOs 11, 12 e 13
   - **Botão A** na GPIO 05
6. *(Opcional)*: Implementar debounce via software para reduzir o efeito bouncing no botão.

## Ambiente de Desenvolvimento
- **Editor**: VS Code
- **Linguagem**: C
- **SDK**: Pico SDK
- **Simulador**: Wokwi, integrado ao VS Code
- **Controle de Versão**: GitHub

## Como Executar o Projeto
1. **Clonar o Repositório**:

```bash
git clone https://github.com/yasmincsme/embarcatech-U4-ativ2.git

2. **Compilar e Carregar o Código**:
   No VS Code, configure o ambiente e compile o projeto com os comandos:

```bash	
cmake -G Ninja ..
ninja
```

3. **Interação com o Sistema**:
   - Conecte a placa ao computador.
   - Clique em run usando a extensão do raspberry pi pico.


## Testes e Validação
- Verifique se os LEDs acendem e apagam na sequência correta.
- Teste se o botão não pode ser acionado durante a execução do temporizador.
- Caso tenha implementado o debounce, avalie se houve redução de falsos acionamentos.


## Autor
Yasmin Cordeiro de Souza Meira
