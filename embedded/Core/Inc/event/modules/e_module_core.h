/*
 * e_module_core.h
 *
 *  Created on: 13 нояб. 2020 г.
 *      Author: S1ckret
 */

#ifndef INC_EVENT_MODULES_E_MODULE_CORE_H_
#define INC_EVENT_MODULES_E_MODULE_CORE_H_

#include <stdint.h>

#include "event/modules/e_module.h"
#include "event/e_queue.h"

struct e_module_core {
  struct e_module super;
  struct e_queue events;
  struct e_module **mod_table;
  uint32_t mod_size;
  uint32_t mod_capacity;
  uint8_t *stack;
  uint32_t stack_size;
};

void e_core_ctor(struct e_module **mod_table,
                  uint32_t mod_cap,
                  uint8_t *pqueue_stack,
                  uint32_t queue_stack_size,
                  uint8_t *pstack,
                  uint32_t stack_size);

void e_core_dtor(void);

void e_core_add_module(struct e_module *mod);

void e_core_notify(struct e_event *event);

void e_core_loop(void);

#endif /* INC_EVENT_MODULES_E_MODULE_CORE_H_ */
