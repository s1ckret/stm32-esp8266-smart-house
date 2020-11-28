/*
 * e_module_timers.c
 *
 *  Created on: 28 нояб. 2020 г.
 *      Author: S1ckret
 */

#include <stdint.h>

#include "event/e_signals.h"
#include "event/events/e_event_time.h"

#include "event/modules/e_module.h"
#include "event/modules/e_module_core.h"
#include "event/modules/e_module_timers.h"

#include "event/e_timer.h"

struct e_module_timers mod_timers;

static void timers_dispatch(struct e_event *e);

void e_module_timers_ctor(struct e_timer **timers, uint32_t timer_quantity_max) {
  e_module_ctor(&mod_timers, "TIM_MNG", timers_dispatch);
  mod_timers.timer_quantity = 0U;
  mod_timers.timer_quantity_max = timer_quantity_max;
  mod_timers.timers = timers;
  e_core_add_module(&mod_timers);
}

void e_module_timers_dtor(void) {
  mod_timers.timer_quantity = 0U;
  mod_timers.timer_quantity_max = 0U;
  mod_timers.timers = 0;
  e_module_dtor(&mod_timers);
}

void e_module_timers_register(struct e_timer *timer) {
  if (mod_timers.timer_quantity + 1 > mod_timers.timer_quantity_max) {
    return;
  }

  mod_timers.timers[mod_timers.timer_quantity] = timer;
  mod_timers.timer_quantity++;
}

void e_module_timers_unregister(struct e_timer *timer) {
  /* This timers version does not support this */
}

void e_module_timers_tick(void) {
  for (uint32_t i = 0; i < mod_timers.timer_quantity; ++i) {
    if (e_timer_step(mod_timers.timers[i])) {
      //generate event
      struct e_event_time e;
      e.super.mod_to = mod_timers.timers[i]->mod;
      e.super.mod_from = 0;
      e.super.sig = SIG_SYS_TIMEOUT;
      e.super.size = E_EVENT_BODY_SIZE(struct e_event_time);
      e.elapsed_time = 0U;
      e_core_notify((struct e_event*)&e);
    }
  }
}

static void timers_dispatch(struct e_event *e) {

}
