/*
 * e_module_heartbeat.h
 *
 *  Created on: 28 нояб. 2020 г.
 *      Author: S1ckret
 */

#ifndef INC_EVENT_MODULES_E_MODULE_HEARTBEAT_H_
#define INC_EVENT_MODULES_E_MODULE_HEARTBEAT_H_

#include "event/modules/e_module.h"

#include "event/e_timer.h"

#include "drv/drv_led.h"

struct e_module_heartbeat {
  struct e_module super;
  enum drv_led_name led;
  uint32_t period;
  uint32_t duty;
  struct e_timer timer;
};

void e_module_heartbeat_ctor(struct e_module_heartbeat *me,
                              uint8_t *name,
                              enum drv_led_name led,
                              uint32_t period,
                              uint32_t duty);

void e_module_heartbeat_dtor(struct e_module_heartbeat *me);

void e_module_heartbeat_set_led(struct e_module_heartbeat *me,
                                  enum drv_led_name led);

void e_module_heartbeat_set_period(struct e_module_heartbeat *me,
                                  uint32_t period);

void e_module_heartbeat_set_duty(struct e_module_heartbeat *me,
                                  uint32_t duty);

#endif /* INC_EVENT_MODULES_E_MODULE_HEARTBEAT_H_ */
