/*
 * e_event_time.h
 *
 *  Created on: 28 нояб. 2020 г.
 *      Author: S1ckret
 */

#ifndef INC_EVENT_EVENTS_E_EVENT_TIME_H_
#define INC_EVENT_EVENTS_E_EVENT_TIME_H_

#include "event/events/e_event.h"

struct e_event_time {
  struct e_event super;
  uint32_t elapsed_time;
};

#endif /* INC_EVENT_EVENTS_E_EVENT_TIME_H_ */
