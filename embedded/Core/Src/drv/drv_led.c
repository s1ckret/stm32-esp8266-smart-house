/*
 * drv_led.c
 *
 *  Created on: Oct 14, 2020
 *      Author: S1ckret
 */

#include <stdint.h>

#include "stm32f1xx_hal.h"

#include "drv/drv_led.h"

struct drv_led {
  GPIO_TypeDef* port;
  uint32_t pin;
};

static struct drv_led leds[DRV_LED_COUNT] = {
    {GPIOC, GPIO_PIN_13},
    {GPIOB, GPIO_PIN_10},
};

void drv_led_on(enum drv_led_name me) {
  leds[me].port->BSRR |= leds[me].pin;
}

void drv_led_off(enum drv_led_name me) {
  leds[me].port->BRR |= leds[me].pin;
}
