/*
 * utl_heartbeat.c
 *
 *  Created on: Oct 14, 2020
 *      Author: S1ckret
 */

#include "utl/utl_heartbeat.h"

enum heartbeat_state {
  STATE_TURN_LED_ON,
  STATE_DUTYCYCLE,
  STATE_TURN_LED_OFF,
  STATE_PERIOD
};
static enum heartbeat_state utl_heartbeat_state_led_on(
    uint32_t* start_time,
    const enum drv_led_name led);

static enum heartbeat_state utl_heartbeat_state_duty(
    const enum heartbeat_state current_state,
    uint32_t start_time,
    uint32_t next_time);

static enum heartbeat_state utl_heartbeat_state_led_off(
    uint32_t* start_time,
    const enum drv_led_name led);

static enum heartbeat_state utl_heartbeat_state_period(
    const enum heartbeat_state current_state,
    uint32_t start_time,
    uint32_t next_time);

void utl_run_heartbeat(enum drv_led_name led, uint32_t duty, uint32_t period) {
  static enum heartbeat_state current_state = STATE_TURN_LED_ON;
  static enum heartbeat_state next_state = STATE_DUTYCYCLE;

  static uint32_t start_time = 0;
  switch (current_state) {
  case STATE_TURN_LED_ON :
    next_state = utl_heartbeat_state_led_on(&start_time, led);
    break;
  case STATE_DUTYCYCLE :
    next_state = utl_heartbeat_state_duty(current_state, start_time, duty);
    break;
  case STATE_TURN_LED_OFF :
    next_state = utl_heartbeat_state_led_off(&start_time, led);
    break;
  case STATE_PERIOD :
    next_state = utl_heartbeat_state_period(current_state, start_time, period - duty);
    break;
  default:
    next_state = STATE_TURN_LED_ON;
  }

  current_state = next_state;
}

static enum heartbeat_state utl_heartbeat_state_led_on(
    uint32_t* start_time,
    const enum drv_led_name led) {
  drv_led_on(led);
  *start_time = utl_time_get_current_time();
  return STATE_DUTYCYCLE;
}

static enum heartbeat_state utl_heartbeat_state_duty(
    const enum heartbeat_state current_state,
    uint32_t start_time,
    uint32_t next_time) {
  uint8_t is_it_time = utl_time_is_it_time(start_time, next_time);
  enum heartbeat_state next_state = current_state;
  if (is_it_time) {
    next_state = STATE_TURN_LED_OFF;
  }
  return next_state;
}

static enum heartbeat_state utl_heartbeat_state_led_off(
    uint32_t* start_time,
    const enum drv_led_name led) {
  drv_led_off(led);
  *start_time = utl_time_get_current_time();
  return STATE_PERIOD;
}

static enum heartbeat_state utl_heartbeat_state_period(
    const enum heartbeat_state current_state,
    uint32_t start_time,
    uint32_t next_time) {
  uint8_t is_it_time = utl_time_is_it_time(start_time, next_time);
  enum heartbeat_state next_state = current_state;
  if (is_it_time) {
    next_state = STATE_TURN_LED_ON;
  }
  return next_state;
}
