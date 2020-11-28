/*
 * e_signals.h
 *
 *  Created on: 12 нояб. 2020 г.
 *      Author: S1ckret
 */

#ifndef INC_EVENT_E_SIGNALS_H_
#define INC_EVENT_E_SIGNALS_H_

#include <stdint.h>

/**
 * @brief Signal type
 */
typedef uint16_t e_signal_t;

/**
 * @brif System reserved positions for signals
 */
enum e_signal_sys {
  SIG_SYS_MOD_ADD,
  SIG_SYS_MOD_RM,
  SIG_SYS_INIT,
  SIG_SYS_TIMEOUT,
  SIG_SYS_USER
};


/**
 * @brief Signal list
 */
enum e_signal {
  SIG_BTN_PRESSED = SIG_SYS_USER,
  SIG_BTN_RELEASED,
  /* ... */
};

#endif /* INC_EVENT_E_SIGNALS_H_ */
