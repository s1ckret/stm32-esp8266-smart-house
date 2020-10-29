/*
 * utl_uart.c
 *
 *  Created on: Oct 14, 2020
 *      Author: S1ckret
 */

#include <stdint.h>
#include <string.h>

#include "stm32f1xx_hal.h"

#include "utl/utl_uart.h"
#include "utl/utl_circular_buf.h"

#define UTL_UART_C_BUF_TX_CAPACITY (512)
#define UTL_UART_C_BUF_RX_CAPACITY (64)
#define UTL_UART_IT_BUF_RX_CAPACITY (1)

struct uart {
  UART_HandleTypeDef handle;
  struct utl_circular_buf c_buf_tx;
  struct utl_circular_buf c_buf_rx;
  uint8_t c_buf_tx_raw[UTL_UART_C_BUF_TX_CAPACITY];
  uint8_t c_buf_rx_raw[UTL_UART_C_BUF_RX_CAPACITY];
  uint8_t it_buf_rx[UTL_UART_IT_BUF_RX_CAPACITY];
};

static struct uart uart_table[UTL_UART_COUNT];

static void utl_uart_init_c_buf(enum utl_uart_name me);
static void utl_uart_rx_callback(UART_HandleTypeDef *huart);

void utl_uart_init(enum utl_uart_name me, USART_TypeDef *instance, uint32_t baud_rate) {
  UART_HandleTypeDef *uart = &uart_table[me].handle;
  uart->Instance = instance;
  uart->Init.BaudRate = baud_rate;
  uart->Init.WordLength = UART_WORDLENGTH_8B;
  uart->Init.StopBits = UART_STOPBITS_1;
  uart->Init.Parity = UART_PARITY_NONE;
  uart->Init.Mode = UART_MODE_TX_RX;
  uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  uart->Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(uart);
  HAL_UART_RegisterCallback(uart, HAL_UART_RX_COMPLETE_CB_ID, utl_uart_rx_callback);

  utl_uart_init_c_buf(me);
}

void utl_uart_init_full(enum utl_uart_name me, USART_TypeDef *instance, UART_InitTypeDef *init) {
  UART_HandleTypeDef *uart = &uart_table[me].handle;
  uart->Instance = instance;
  uart->Init = *init;
  HAL_UART_Init(uart);

  utl_uart_init_c_buf(me);
}

static void utl_uart_init_c_buf(enum utl_uart_name me) {
  utl_circular_buf_handle c_buf_tx = &uart_table[me].c_buf_tx;
  utl_circular_buf_init(c_buf_tx, uart_table[me].c_buf_tx_raw, UTL_UART_C_BUF_TX_CAPACITY);
  utl_circular_buf_handle c_buf_rx = &uart_table[me].c_buf_rx;
  utl_circular_buf_init(c_buf_rx, uart_table[me].c_buf_rx_raw, UTL_UART_C_BUF_RX_CAPACITY);
}
void utl_uart_start(enum utl_uart_name me) {
  struct uart *uart = &uart_table[me];
  HAL_UART_Receive_IT(&uart->handle, &uart->it_buf_rx[0], UTL_UART_IT_BUF_RX_CAPACITY);
}

void utl_uart_send_blocking(enum utl_uart_name me, uint8_t *data, uint16_t len, uint32_t timeout) {
  HAL_UART_Transmit(&uart_table[me].handle, data, len, timeout);
}

void utl_uart_send(enum utl_uart_name me, uint8_t *data, uint16_t len) {
  utl_circular_buf_handle c_buf_tx = &uart_table[me].c_buf_tx;
  utl_circular_buf_write(c_buf_tx, data, len);
}

void utl_uart_send_str_blocking(enum utl_uart_name me, uint8_t *str, uint32_t timeout) {
  uint16_t len = (uint16_t)strlen((const char *)str);
  HAL_UART_Transmit(&uart_table[me].handle, str, len, timeout);
}

void utl_uart_send_str(enum utl_uart_name me, uint8_t *str) {
  uint16_t len = (uint16_t)strlen((const char *)str);
  utl_circular_buf_handle c_buf_tx = &uart_table[me].c_buf_tx;
  utl_circular_buf_write(c_buf_tx, str, len);
}

void utl_uart_irq_handler(enum utl_uart_name me) {
  struct uart *uart = &uart_table[me];
  HAL_UART_IRQHandler(&uart->handle);
  HAL_UART_Receive_IT(&uart->handle, &uart->it_buf_rx[0], UTL_UART_IT_BUF_RX_CAPACITY);
}

static void utl_uart_rx_callback(UART_HandleTypeDef *huart) {
  /* We can perform upcast, because the uart structure contains first element UART_HandleTypeDef.
   * And we assume that all uart instances were created via utl structure.  */
  struct uart *uart = (struct uart *)huart;
  utl_circular_buf_write(&uart->c_buf_rx, &uart->it_buf_rx[0], UTL_UART_IT_BUF_RX_CAPACITY);
}

void utl_uart_read(enum utl_uart_name me, uint8_t *target, uint32_t len) {
  utl_circular_buf_handle c_buf = &uart_table[me].c_buf_rx;
  utl_circular_buf_read(c_buf, target, len);
}

void utl_uart_read_all(enum utl_uart_name me, uint8_t *target) {
  utl_circular_buf_handle c_buf = &uart_table[me].c_buf_rx;
  uint32_t len = utl_circular_buf_size(c_buf);
  utl_circular_buf_read(c_buf, target, len);
}

void utl_uart_read_all_c(enum utl_uart_name me, uint8_t *target, uint32_t target_len) {

  utl_circular_buf_handle c_buf = &uart_table[me].c_buf_rx;
  uint32_t len = utl_circular_buf_size(c_buf);

  if (len > target_len)
    return; /* TODO: Return error code. */

  utl_circular_buf_read(c_buf, target, len);
}

void utl_uart_run(enum utl_uart_name me) {
  struct uart *uart = &uart_table[me];
  HAL_UART_StateTypeDef uart_state = HAL_UART_GetState(&uart->handle);
  if (!(uart_state == HAL_UART_STATE_READY || uart_state == HAL_UART_STATE_BUSY_RX))
    return; /* TODO: Return error code. */

  uint8_t *source = utl_circular_buf_get_tail_ptr(&uart->c_buf_tx);
  uint16_t size = (uint16_t)utl_circular_buf_get_avail_elem_count_with_advance(&uart->c_buf_tx);
  if (size) {
    HAL_UART_Transmit_IT(&uart->handle, source, size);
  }

}
