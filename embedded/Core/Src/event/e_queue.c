/*
 * e_queue.c
 *
 *  Created on: 13 нояб. 2020 г.
 *      Author: S1ckret
 */


#include "utl/utl_circular_buf.h"

#include "event/e_queue.h"
#include "event/events/e_event.h"

void e_queue_init(struct e_queue *me, uint8_t *pstack, uint32_t stack_size) {
  utl_circular_buf_init(&me->c_buf, pstack, stack_size);
  me->size = 0U;
}

uint8_t e_queue_add(struct e_queue *me, struct e_event *event) {
  uint32_t size = e_event_calculate_size(event);
  if (size > utl_circular_buf_size_free(&me->c_buf)) {
    /* TODO: Error codes enum + description */
    return 1U;
  }

  utl_circular_buf_write(&me->c_buf, (uint8_t *)event, size);
  me->size++;
  /* TODO: Error codes enum + description */
  return 0U;
}

uint8_t e_queue_poll(struct e_queue *me, struct e_event *event) {
  if (me->size == 0U) {
    /* TODO: Error codes enum + description */
    return 1U;
  }
  uint8_t *e = (uint8_t*)event;
  utl_circular_buf_read(&me->c_buf, e, E_EVENT_HEADER_SIZE);
  uint32_t e_size = event->size;
  utl_circular_buf_read(&me->c_buf, e + E_EVENT_HEADER_SIZE, e_size);
  me->size--;

  /* TODO: Error codes enum + description */
  return 0U;
}

uint8_t e_queue_is_empty(struct e_queue *me) {
  return me->size == 0U;
}

uint8_t e_queue_get_size(struct e_queue *me) {
  return me->size;
}

void e_queue_clear(struct e_queue *me) {
  me->size = 0;
  utl_circular_buf_reset(&me->c_buf);
}
