/*
 * utl_circular_buf.c
 *
 *  Created on: Jul 10, 2020
 *      Author: s1ckret
 */

#include <string.h>

#include "stm32f1xx_hal.h"

#include "utl/utl_circular_buf.h"

static void _circular_buf_advance_pointer(utl_circular_buf_handle cbuf);
static void _circular_buf_advance_pointer_by_n(utl_circular_buf_handle cbuf, uint32_t n);
static void _circular_buf_retreat_pointer(utl_circular_buf_handle cbuf);

static struct utl_circular_buf cb;

utl_circular_buf_handle circular_buffer = &cb;

void utl_circular_buf_init(utl_circular_buf_handle cbuf, uint8_t* buf, uint32_t size) {
  assert_param(cbuf && buf && size);

  cbuf->buf = buf;
  cbuf->capacity = size;

  utl_circular_buf_reset(cbuf);
}

void utl_circular_buf_reset(utl_circular_buf_handle cbuf) {
  assert_param(cbuf);
  cbuf->head = 0;
  cbuf->tail = 0;
  cbuf->is_full = 0;
}

void utl_circular_buf_put(utl_circular_buf_handle cbuf, uint8_t byte) {
  assert_param(cbuf && cbuf->buf);
  cbuf->buf[cbuf->head] = byte;

  _circular_buf_advance_pointer(cbuf);
}

int8_t utl_circular_buf_get(utl_circular_buf_handle cbuf, uint8_t* data) {
  assert_param(cbuf && data && cbuf->buf);

  int8_t status = -1;

  if (!utl_circular_buf_is_empty(cbuf)) {
    *data = cbuf->buf[cbuf->tail];
    _circular_buf_retreat_pointer(cbuf);

    status = 0;
  }
  return status;
}

void utl_circular_buf_write(utl_circular_buf_handle cbuf, uint8_t* source,
                        uint32_t count) {
  assert_param(cbuf && source);
  assert_param(count <= cbuf->capacity);

  for (uint32_t i = 0; i < count; ++i) {
    utl_circular_buf_put(cbuf, source[i]);
  }
}

void utl_circular_buf_read(utl_circular_buf_handle cbuf, uint8_t* target,
                       uint32_t count) {
  assert_param(cbuf && target);
  assert_param(count <= cbuf->capacity);

  for (uint32_t i = 0; i < count; ++i) {
    utl_circular_buf_get(cbuf, &target[i]);
  }
}

uint8_t utl_circular_buf_is_empty(utl_circular_buf_handle cbuf) {
  return (!cbuf->is_full && (cbuf->head == cbuf->tail));
}

uint8_t utl_circular_buf_is_full(utl_circular_buf_handle cbuf) {
  assert_param(cbuf);
  return cbuf->is_full;
}

uint32_t utl_circular_buf_capacity(utl_circular_buf_handle cbuf) {
  assert_param(cbuf);
  return cbuf->capacity;
}

uint32_t utl_circular_buf_size(utl_circular_buf_handle cbuf) {
  assert_param(cbuf);
  uint32_t size = cbuf->capacity;
  if (!cbuf->is_full) {
    if (cbuf->head >= cbuf->tail) {
      size = cbuf->head - cbuf->tail;
    } else {
      size = cbuf->capacity + cbuf->head - cbuf->tail;
    }
  }
  return size;
}

static void _circular_buf_advance_pointer(utl_circular_buf_handle cbuf) {
  assert_param(cbuf);

  if (cbuf->is_full) cbuf->tail = (++cbuf->tail) % cbuf->capacity;

  cbuf->head = (++cbuf->head) % cbuf->capacity;
  cbuf->is_full = (cbuf->head == cbuf->tail);
}

static void _circular_buf_advance_pointer_by_n(utl_circular_buf_handle cbuf, uint32_t n) {
  assert_param(cbuf && n);

  if (cbuf->is_full) cbuf->tail = (cbuf->tail + n) % cbuf->capacity;

  cbuf->head = (cbuf->head + n) % cbuf->capacity;
  cbuf->is_full = (cbuf->head == cbuf->tail);
}

static void _circular_buf_retreat_pointer(utl_circular_buf_handle cbuf) {
  assert_param(cbuf);
  cbuf->is_full = 0;
  cbuf->tail = (++cbuf->tail) % cbuf->capacity;
}

