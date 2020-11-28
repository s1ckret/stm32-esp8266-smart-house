/*
 * e_module_timer.h
 *
 *  Created on: 28 нояб. 2020 г.
 *      Author: S1ckret
 */

#ifndef INC_EVENT_MODULES_E_MODULE_TIMERS_H_
#define INC_EVENT_MODULES_E_MODULE_TIMERS_H_

#include <stdint.h>

#include "event/modules/e_module.h"
#include "event/e_timer.h"

struct e_module_timers {
  struct e_module super;
  struct e_timer **timers;
  uint32_t timer_quantity;
  uint32_t timer_quantity_max;
};

void e_module_timers_ctor(struct e_timer **timers, uint32_t timer_quantity_max);

void e_module_timers_dtor(void);

void e_module_timers_register(struct e_timer *timer);

void e_module_timers_unregister(struct e_timer *timer);

void e_module_timers_tick(void);

#endif /* INC_EVENT_MODULES_E_MODULE_TIMERS_H_ */
