#include "led.h"

#include "esp_timer.h"
#include <driver/gpio.h>

void wait(uint32_t ms)
{
    int64_t start = esp_timer_get_time();
    while ((esp_timer_get_time() - start) < (ms * 1000))
        __asm__("nop"); // save a few cpu cycles
}

void led_blink(gpio_num_t gpio_led, int amount, int delay)
{
    if (delay == -1) delay = 500;

    for (size_t i = 0; i < amount; ++i)
    {
        if (gpio_get_level(gpio_led) == 1)
        {
            gpio_set_level(gpio_led, 0);
            wait(delay);
        }

        gpio_set_level(gpio_led, 1);
        wait(delay);
    }
}
