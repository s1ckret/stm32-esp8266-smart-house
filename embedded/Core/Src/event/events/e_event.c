/*
 * e_event.c
 *
 *  Created on: 13 нояб. 2020 г.
 *      Author: S1ckret
 */

#include "event/events/e_event.h"

uint32_t e_event_calculate_size(struct e_event *event) {
  return E_EVENT_HEADER_SIZE + event->size;
}
