/*
 * e_timer.c
 *
 *  Created on: 28 нояб. 2020 г.
 *      Author: S1ckret
 */

#include <stdint.h>

#include "event/e_timer.h"

void e_timer_ctor(struct e_timer *me, struct e_module *mod) {
  me->mod = mod;
  me->interval = 0U;
  me->timeout = 0U;
}

void e_timer_dtor(struct e_timer *me) {
  me->mod = 0;
  me->interval = 0U;
  me->timeout = 0U;
}

void e_timer_arm(struct e_timer *me, uint32_t timeout, uint32_t interval) {
  me->interval = interval;
  me->timeout = timeout;
}

void e_timer_disarm(struct e_timer *me) {
  me->interval = 0U;
  me->timeout = 0U;
}

uint8_t e_timer_step(struct e_timer *me) {
  /* If armed */
  if (me->timeout > 0) {
    if (--me->timeout == 0U) {
      me->timeout = me->interval;
      return 1U;
    }
  }
  return 0U;
}
