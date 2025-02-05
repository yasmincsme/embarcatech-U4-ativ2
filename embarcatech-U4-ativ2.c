#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#define LEDS 3
#define BUTTON_A 5
#define DEBOUNCE_TIME_US 200000  // 200ms
#define TIME 3000  // 3s

uint8_t led_pins[LEDS] = {13, 12, 11};

static volatile uint32_t last_press_A = 0;
static volatile bool running = false;  // Estado da sequência de LEDs
static volatile int step = 0;
static struct repeating_timer timer;

void setup_all(void) {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    for (uint8_t i = 0; i < LEDS; ++i) {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
        gpio_put(led_pins[i], 0);
    }
}

bool timer_callback(struct repeating_timer *rt) {
    if (!running) return true; // Só executa se a sequência estiver rodando

    // Define os LEDs para formar cores específicas
    switch (step) {
        case 0: // Branco (todos os LEDs ligados)
            for (uint8_t i = 0; i < LEDS; ++i) {
                gpio_put(led_pins[i], 1);
            }
            break;
        case 1: // Roxo (LEDs 1 e 3 ligados)
            gpio_put(led_pins[0], 1);
            gpio_put(led_pins[1], 1);
            gpio_put(led_pins[2], 0);
            break;
        case 2: // Vermelho (somente o primeiro LED ligado)
            gpio_put(led_pins[0], 1);
            gpio_put(led_pins[1], 0);
            gpio_put(led_pins[2], 0);
            break;
        case 3: // Desliga todos os LEDs
            for (uint8_t i = 0; i < LEDS; ++i) {
                gpio_put(led_pins[i], 0);
            }
            running = false; // Finaliza a sequência
            step = 0;
            return false; // Para o temporizador
    }
    
    step++;
    return true;
}

static void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    
    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_FALL)) {
        if (current_time - last_press_A > DEBOUNCE_TIME_US) {
            last_press_A = current_time;
            if (!running) { // Inicia a sequência apenas se não estiver rodando
                running = true;
                step = 0;
                timer_callback(NULL); // Aciona a sequência imediatamente
                add_repeating_timer_ms(TIME, timer_callback, NULL, &timer);
            }
        }
    }
}

int main() {
    stdio_init_all();
    setup_all();

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (1) {
        printf("Programa em execução\n");
        sleep_ms(1000);
    }

    return 0;
}