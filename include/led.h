#ifndef LED_H
#define LED_H

#include "soc/gpio_num.h"
#include <stdint.h>

void wait(uint32_t ms);
void led_blink(gpio_num_t gpio_led, int amount, int delay);

#endif
