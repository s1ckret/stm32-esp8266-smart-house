/*
 * utl_heartbeat.h
 *
 *  Created on: Oct 14, 2020
 *      Author: S1ckret
 */

#ifndef INC_UTL_UTL_HEARTBEAT_H_
#define INC_UTL_UTL_HEARTBEAT_H_

#include <stdint.h>

#include "drv/drv_led.h"

void utl_run_heartbeat(enum drv_led_name led, uint32_t duty, uint32_t period);

#endif /* INC_UTL_UTL_HEARTBEAT_H_ */
