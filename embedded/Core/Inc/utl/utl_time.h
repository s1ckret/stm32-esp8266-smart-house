/*
 * utl_time.h
 *
 *  Created on: Oct 14, 2020
 *      Author: S1ckret
 */

#ifndef INC_UTL_UTL_TIME_H_
#define INC_UTL_UTL_TIME_H_

#include <stdint.h>

uint32_t utl_time_get_current(void);

uint8_t utl_time_is_it_time(uint32_t start_time, uint32_t delay);

#endif /* INC_UTL_UTL_TIME_H_ */
