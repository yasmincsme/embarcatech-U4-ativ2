#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#define LEDS 3
#define BUTTON_A 5
#define DEBOUNCE_TIME_US 200000  
#define TIME 3000  

uint8_t led_pins[LEDS] = {13, 12, 11};

static volatile uint32_t last_press_A = 0;
static volatile bool running = false; 
static volatile int step = 0;

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
    if (!running) return true; 

    for (uint8_t i = 0; i < LEDS; ++i) {
        gpio_put(led_pins[i], i < (LEDS - step));
    }
    
    step++;
    if (step > LEDS) {
        running = false;
        step = 0;
    }

    return true;
}

static void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    
    if (gpio == BUTTON_A && (events & GPIO_IRQ_EDGE_FALL)) {
        if (current_time - last_press_A > DEBOUNCE_TIME_US) {
            last_press_A = current_time;
            if (!running) { 
                running = true;
                step = 0;
            }
        }
    }
}

int main() {
    stdio_init_all();
    setup_all();

    struct repeating_timer timer;
    add_repeating_timer_ms(TIME, timer_callback, NULL, &timer);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (1) {
        printf("Programa em execução\n");
        sleep_ms(1000);
    }

    return 0;
}
