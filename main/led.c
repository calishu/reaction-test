#include "led.h"
#include "freertos/idf_additions.h"

#include <driver/gpio.h>

void led_blink(gpio_num_t gpio_led, int amount, int delay_ms)
{
    if (delay_ms == -1) delay_ms = 500;

    for (size_t i = 0; i < amount; ++i)
    {
        if (gpio_get_level(gpio_led) == 1)
        {
            gpio_set_level(gpio_led, 0);
            vTaskDelay(pdMS_TO_TICKS(delay_ms));
        }

        gpio_set_level(gpio_led, 1);
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
}
