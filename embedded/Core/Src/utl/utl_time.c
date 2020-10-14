/*
 * utl_time.c
 *
 *  Created on: Oct 14, 2020
 *      Author: S1ckret
 */

#ifndef SRC_UTL_UTL_TIME_C_
#define SRC_UTL_UTL_TIME_C_

#include <stdint.h>

#include "stm32f1xx_hal.h"

#include "utl/utl_time.h"

uint32_t utl_time_get_current_time(void) {
  return HAL_GetTick();
}

uint8_t utl_time_is_it_time(uint32_t start_time, uint32_t delay) {
  uint8_t result = 0;
  uint32_t current_time = utl_time_get_current_time();
  uint32_t elapsed_time = 0;
  if (current_time < start_time)
  {
    elapsed_time = current_time + UINT32_MAX - start_time;
  }
  else
  {
    elapsed_time = current_time - start_time;
  }

  if (elapsed_time > delay)
  {
    result = 1;
  }

  return result;
}

#endif /* SRC_UTL_UTL_TIME_C_ */
