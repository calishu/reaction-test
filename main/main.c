#include <stdint.h>

#include "led.h"
#include "rng.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"

#define TAG "Reaction Test"

#define RED_LED GPIO_NUM_6
#define GREEN_LED GPIO_NUM_5
#define BUTTON GPIO_NUM_7
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

void loop()
{
    bool stop_action = false;

    while (stop_action != true)
    {
        gpio_set_level(GREEN_LED, 0);
        gpio_set_level(RED_LED, 0);

        uint8_t stop_button_state = gpio_get_level(STOP_BUTTON);
        if (stop_button_state == 1) stop_action = true;

        gpio_set_level(RED_LED, 1);
        wait(get_random_number(3000, 6000));
        gpio_set_level(RED_LED, 0);

        int64_t start = esp_timer_get_time();
        gpio_set_level(GREEN_LED, 1);

        while (gpio_get_level(BUTTON) == 0 || (start * 1000) < 2500)
            __asm__("nop");

        ESP_LOGI(TAG, "You took a long time ig");
    }
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

    loop();
}
