/*
 * e_module_heartbeat.c
 *
 *  Created on: 28 нояб. 2020 г.
 *      Author: S1ckret
 */
#include "event/modules/e_module.h"
#include "event/modules/e_module_heartbeat.h"
#include "event/modules/e_module_timers.h"

#include "drv/drv_led.h"

static void heartbeat_dispatch(struct e_event *e);

void e_module_heartbeat_ctor(struct e_module_heartbeat *me,
                              uint8_t *name,
                              enum drv_led_name led,
                              uint32_t period,
                              uint32_t duty) {
  e_module_ctor((struct e_module *)me, name, heartbeat_dispatch);
  me->led = led;
  me->period = period;
  me->duty = duty;
}

void e_module_heartbeat_dtor(struct e_module_heartbeat *me) {
  e_module_dtor((struct e_module *)me);
  me->period = 0;
  me->duty = 0;
}

void e_module_heartbeat_set_led(struct e_module_heartbeat *me,
                                  enum drv_led_name led) {
  // create event
}

void e_module_heartbeat_set_period(struct e_module_heartbeat *me,
                                  uint32_t period) {
  // create event
}

void e_module_heartbeat_set_duty(struct e_module_heartbeat *me,
                                  uint32_t duty) {
  // create event
}

static void heartbeat_dispatch(struct e_event *e) {
  struct e_module_heartbeat *me = (struct e_module_heartbeat *)e->mod_to;
  switch(e->sig) {
  case SIG_SYS_INIT:
    drv_led_off(me->led);
    e_timer_ctor(&me->timer, e->mod_to);
    e_module_timers_register(&me->timer);
    e_timer_arm(&me->timer, me->period - me->duty, 0U);
    break;
  case SIG_SYS_TIMEOUT:
    switch (drv_led_get_state(me->led)) {
    case DRV_LED_STATE_OFF:
      drv_led_on(me->led);
      e_timer_arm(&me->timer, me->duty, 0U);
      break;
    case DRV_LED_STATE_ON:
      drv_led_off(me->led);
      e_timer_arm(&me->timer, me->period - me->duty, 0U);
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}
