/*
 * command_parser_fsm.h
 *
 *  Created on: Nov 14, 2025
 *      Author: Admin
 */

#ifndef INC_COMMAND_PARSER_FSM_H_
#define INC_COMMAND_PARSER_FSM_H_

#include <stdint.h>

#define MAX_BUFFER_SIZE 30

/* Shared RX buffer interface */
extern uint8_t buffer[];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

/* Command flag (1=RST,2=OK,0=none) */
extern uint8_t command_flag;

void command_parser_fsm(void);

#endif /* INC_COMMAND_PARSER_FSM_H_ */
