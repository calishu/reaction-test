#ifndef RNG_H
#define RNG_H

#include <stdint.h>

static uint32_t rng_state = 0;

static uint32_t get_entropy()
{
    uint32_t ccount;
    asm volatile("rsr.ccount %0" : "=a"(ccount));
    return ccount;
}

uint32_t get_random_number(int min, int max)
{
    if (rng_state == 0) rng_state = get_entropy();
    rng_state = (1664525 * rng_state + 1013904223); // https://en.wikipedia.org/wiki/Linear_congruential_generator
    return min + (rng_state % (max - min + 1));
}

#endif
