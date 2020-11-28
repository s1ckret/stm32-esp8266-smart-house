/*
 * e_queue.h
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: S1ckret
 */

#ifndef INC_EVENT_E_QUEUE_H_
#define INC_EVENT_E_QUEUE_H_

#include "utl/utl_circular_buf.h"

#include "event/events/e_event.h"

/**
 * @brief Event queue structure
 * @param c_buf Circular buffer structure
 * @param size Current queue element size
 */
struct e_queue {
  struct utl_circular_buf c_buf;
  uint32_t size;
};

void e_queue_init(struct e_queue *me, uint8_t *pstack, uint32_t stack_size);

uint8_t e_queue_add(struct e_queue *me, struct e_event *event);

uint8_t e_queue_poll(struct e_queue *me, struct e_event *event);

uint8_t e_queue_is_empty(struct e_queue *me);

uint8_t e_queue_get_size(struct e_queue *me);

void e_queue_clear(struct e_queue *me);

#endif /* INC_EVENT_E_QUEUE_H_ */
