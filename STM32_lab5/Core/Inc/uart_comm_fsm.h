/*
 * uart_comm_fsm.h
 *
 *  Created on: Nov 14, 2025
 *      Author: Admin
 */

#ifndef INC_UART_COMM_FSM_H_
#define INC_UART_COMM_FSM_H_

#include <stdint.h>

void uart_communication_fsm(void);

/* Expose ADC value if user code needs it */
extern uint32_t ADC_value;


#endif /* INC_UART_COMM_FSM_H_ */
