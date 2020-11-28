/*
 * e_timer.h
 *
 *  Created on: 28 нояб. 2020 г.
 *      Author: S1ckret
 */

#ifndef INC_EVENT_E_TIMER_H_
#define INC_EVENT_E_TIMER_H_

#include <stdint.h>

struct e_timer {
  struct e_module *mod;
  uint32_t timeout;
  uint32_t interval;
};

void e_timer_ctor(struct e_timer *me, struct e_module *mod);

void e_timer_dtor(struct e_timer *me);

void e_timer_arm(struct e_timer *me, uint32_t timeout, uint32_t interval);

void e_timer_disarm(struct e_timer *me);

uint8_t e_timer_step(struct e_timer *me);

#endif /* INC_EVENT_E_TIMER_H_ */
