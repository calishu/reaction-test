#include <stdio.h>

#include "led.h"
#include "rng.h"

#include "driver/gpio.h"
#include "esp_log.h"

#define RED_LED GPIO_NUM_6
#define GREEN_LED GPIO_NUM_5
#define BUTTON GPIO_NUM_3
#define STOP_BUTTON GPIO_NUM_4

gpio_config_t get_config(gpio_num_t gpio_num)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << gpio_num),
        .mode         = GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type    = GPIO_INTR_DISABLE};
    return io_conf;
}

void app_main()
{
    gpio_config_t red_led     = get_config(RED_LED);
    gpio_config_t green_led   = get_config(GREEN_LED);
    gpio_config_t button      = get_config(BUTTON);
    gpio_config_t stop_button = get_config(STOP_BUTTON);

    gpio_config(&red_led);
    gpio_config(&green_led);
    gpio_config(&button);
    gpio_config(&stop_button);
}
