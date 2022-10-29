/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

static char event_str[128];
uint count =0;

#define IrqPin 3

void gpio_IrqPinStart()
{
    gpio_init(IrqPin);
    //gpio_set_dir(3, GPIO_IN);
    gpio_pull_down(IrqPin);
}

void gpio_event_string(char *buf, uint32_t events);

void gpio_callback(uint gpio, uint32_t events)
{   
    count++;
    busy_wait_ms(500);
    // Put the GPIO event(s) that just happened into event_str
    // so we can print it
    gpio_event_string(event_str, events);
    printf("GPIO %d %s %d\n", gpio, event_str,count);
}

int main()
{
    stdio_init_all();
    gpio_IrqPinStart();

    printf("Hello GPIO IRQ34\n");
    gpio_set_irq_enabled_with_callback(IrqPin, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);    

    // Wait forever
    while (1)
        ;

    return 0;
}

static const char *gpio_irq_str[] = {
    "LEVEL_LOW",  // 0x1
    "LEVEL_HIGH", // 0x2
    "EDGE_FALL",  // 0x4
    "EDGE_RISE"   // 0x8
};

void gpio_event_string(char *buf, uint32_t events)
{
    for (uint i = 0; i < 4; i++)
    {
        uint mask = (1 << i);
        if (events & mask)
        {
            // Copy this event string into the user string
            const char *event_str = gpio_irq_str[i];
            while (*event_str != '\0')
            {
                *buf++ = *event_str++;
            }
            events &= ~mask;

            // If more events add ", "
            if (events)
            {
                *buf++ = ',';
                *buf++ = ' ';
            }
        }
    }
    *buf++ = '\0';
}