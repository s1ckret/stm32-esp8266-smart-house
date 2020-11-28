/*
 * e_module_core.c
 *
 *  Created on: 13 нояб. 2020 г.
 *      Author: S1ckret
 */

#include "event/e_signals.h"
#include "event/e_queue.h"

#include "event/events/e_event.h"

#include "event/modules/e_module_core.h"

struct e_module_core mod_core;
static void core_dispatch(struct e_event *e);

void e_core_ctor(struct e_module **mod_table,
                  uint32_t mod_capacity,
                  uint8_t *pqueue_stack,
                  uint32_t queue_stack_size,
                  uint8_t *pstack,
                  uint32_t stack_size) {
  // assert stack_size > event header
  e_module_ctor(&mod_core, "CORE", core_dispatch);
  mod_core.mod_table = mod_table;
  mod_core.mod_size = 0;
  mod_core.mod_capacity = mod_capacity;
  mod_core.stack = pstack;
  mod_core.stack_size = stack_size;
  e_queue_init(&mod_core.events, pqueue_stack, queue_stack_size);
  e_core_add_module(&mod_core);
}

void e_core_dtor(void) {
  e_module_dtor(&mod_core);
}

void e_core_add_module(struct e_module *mod) {
  struct e_event event = {
    .sig = SIG_SYS_MOD_ADD,
    .mod_to = &mod_core,
    .mod_from = mod,
    .size = 0U
  };

  e_queue_add(&mod_core.events, &event);
}

void e_core_notify(struct e_event *event) {
  e_queue_add(&mod_core.events, event);
}

void e_core_loop() {
  /* Init loop */
  uint32_t queue_size = e_queue_get_size(&mod_core.events);
  for (uint32_t i = 0; i <  queue_size; ++i) {
    struct e_event *event = &mod_core.stack[0];
    e_queue_poll(&mod_core.events, event);

    if (&mod_core == event->mod_to) {
      e_module_dispatch(&mod_core, event);
    }
  }

  /* Main loop */
  while (1) {
    if (e_queue_is_empty(&mod_core.events)) continue;

    struct e_event *event = &mod_core.stack[0];
    e_queue_poll(&mod_core.events, event);

    for (uint32_t i = 0; i < mod_core.mod_size; ++i) {
      if (mod_core.mod_table[i] == event->mod_to) {
        e_module_dispatch(mod_core.mod_table[i], event);
      }
    }
  }
}

static void core_dispatch(struct e_event *e) {
  switch(e->sig) {
  case SIG_SYS_MOD_ADD:
    if (mod_core.mod_size + 1 > mod_core.mod_capacity) {
      // Output error
      return;
    }
    mod_core.mod_table[mod_core.mod_size] = e->mod_from;
    mod_core.mod_size++;
    struct e_event event_init = {
        .sig = SIG_SYS_INIT,
        .mod_to = e->mod_from,
        .mod_from = 0,
        .size = 0U
      };
    e_core_notify(&event_init);
    break;
  case SIG_SYS_MOD_RM:
    /* This core version does not allow mod removing */
    break;
  default:
    break;
  }
}
