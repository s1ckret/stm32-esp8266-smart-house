/*
 * e_event.h
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: S1ckret
 */

#ifndef INC_EVENT_E_EVENT_H_
#define INC_EVENT_E_EVENT_H_

#include <stdint.h>

#include "event/e_signals.h"

/* Forward declaring */
struct e_module;

/**
 * @brief Basic event structure
 * @param sig Signal number
 * @param mod_to Pointer to the module, to which the event is sent
 * @param size Event payload size in bytes (without sig, mod and size variables)
 */
struct e_event {
  e_signal_t sig;
  struct e_module *mod_to;
  struct e_module *mod_from;
  uint32_t size;
};

/**
 * @brief Basic event structure (i.e. event header) size in bytes
 */
#define E_EVENT_HEADER_SIZE (sizeof(struct e_event))

#define E_EVENT_BODY_SIZE(x) (sizeof(x) - sizeof(struct e_event))

/**
 * @brief Calculate event size
 * @param event Base event structure
 * @return Event size in bytes, including header
 */
uint32_t e_event_calculate_size(struct e_event *event);

#endif /* INC_EVENT_E_EVENT_H_ */
