/*
 * utl_uart.h
 *
 *  Created on: Oct 14, 2020
 *      Author: S1ckret
 */

#ifndef INC_UTL_UTL_UART_H_
#define INC_UTL_UTL_UART_H_

#include <stdint.h>

#include "stm32f1xx_hal.h"

enum utl_uart_name {
  UTL_UART_ESP8266,
  UTL_UART_COUNT
};

void utl_uart_init(enum utl_uart_name me, USART_TypeDef *instance, uint32_t baud_rate);

void utl_uart_init_full(enum utl_uart_name me, USART_TypeDef *instance, UART_InitTypeDef *init);

void utl_uart_start(enum utl_uart_name me);

void utl_uart_send_blocking(enum utl_uart_name me, uint8_t *data, uint16_t len, uint32_t timeout);

void utl_uart_send(enum utl_uart_name me, uint8_t *data, uint16_t len);

void utl_uart_send_str_blocking(enum utl_uart_name me, uint8_t *str, uint32_t timeout);

void utl_uart_send_str(enum utl_uart_name me, uint8_t *str);

void utl_uart_irq_handler(enum utl_uart_name me);

void utl_uart_read(enum utl_uart_name me, uint8_t *target, uint32_t len);

#endif /* INC_UTL_UTL_UART_H_ */
