#include <stdint.h>

#include "freertos/projdefs.h"
#include "led.h"
#include "rng.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/idf_additions.h"

#define TAG "Reaction Test"

#define RED_LED GPIO_NUM_6
#define GREEN_LED GPIO_NUM_5
#define BUTTON GPIO_NUM_8
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
        while (gpio_get_level(BUTTON) == 1)
            vTaskDelay(1);

        gpio_set_level(GREEN_LED, 0);
        gpio_set_level(RED_LED, 0);

        uint8_t stop_button_state = gpio_get_level(STOP_BUTTON);
        if (stop_button_state == 1) stop_action = true;

        gpio_set_level(RED_LED, 1);
        for (size_t i = 0; i < pdMS_TO_TICKS(get_random_number(3000, 6000)); ++i)
        {
            if (gpio_get_level(BUTTON) == 1)
            {
                led_blink(RED_LED, 3, 250);
                ESP_LOGE(TAG, "Clicked too early.");
                loop(); // reset
            }
            vTaskDelay(1);
        }
        gpio_set_level(RED_LED, 0);

        int64_t start = esp_timer_get_time();
        gpio_set_level(GREEN_LED, 1);

        while (gpio_get_level(BUTTON) == 0)
        {
            __asm__("nop");
            vTaskDelay(1);
        }

        int64_t elapsed_time = esp_timer_get_time() - start;
        ESP_LOGI(TAG, "Your reaction time was %lldms long.", elapsed_time / 1000LL);
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
