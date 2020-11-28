/*
 * utl_circular_buf.h
 *
 *  Created on: Jul 10, 2020
 *      Author: s1ckret
 */

#ifndef CIRCULAR_BUF_GUARD
#define CIRCULAR_BUF_GUARD

#include <stdint.h>

struct utl_circular_buf {
  uint8_t* buf;
  uint32_t head;
  uint32_t tail;
  uint32_t capacity;
  uint8_t is_full;
};

typedef struct utl_circular_buf* utl_circular_buf_handle;

void utl_circular_buf_init(utl_circular_buf_handle cbuf, uint8_t* buf, uint32_t size);

void utl_circular_buf_reset(utl_circular_buf_handle cbuf);

void utl_circular_buf_put(utl_circular_buf_handle cbuf, uint8_t byte);

int8_t utl_circular_buf_get(utl_circular_buf_handle cbuf, uint8_t* data);

void utl_circular_buf_write(utl_circular_buf_handle cbuf, uint8_t* source,
                        uint32_t count);

void utl_circular_buf_read(utl_circular_buf_handle cbuf, uint8_t* target,
                       uint32_t count);

uint8_t utl_circular_buf_is_empty(utl_circular_buf_handle cbuf);

uint8_t utl_circular_buf_is_full(utl_circular_buf_handle cbuf);

uint32_t utl_circular_buf_capacity(utl_circular_buf_handle cbuf);

uint32_t utl_circular_buf_size(utl_circular_buf_handle cbuf);

uint32_t utl_circular_buf_size_free(utl_circular_buf_handle cbuf);

uint8_t *utl_circular_buf_get_tail_ptr(utl_circular_buf_handle cbuf);

uint8_t utl_circular_buf_get_avail_elem_count_with_advance(utl_circular_buf_handle cbuf);

#endif  // !CIRCULAR_BUF_GUARD
