/*
 * command_parser_fsm.c
 *
 *  Created on: Nov 14, 2025
 *      Author: Admin
 */

#include "command_parser_fsm.h"
#include <string.h>

/* Define the shared buffer variables here (one definition only) */
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

uint8_t command_flag = 0;   // 1 = RST, 2 = OK, 0 = none

void command_parser_fsm(void)
{
    static uint8_t state = 0;
    static char cmd[10];
    static uint8_t cmd_index = 0;

    for (uint8_t i = 0; i < index_buffer; i++) {
        char c = buffer[i];

        switch (state) {
            case 0:
                if (c == '!') {
                    state = 1;
                    cmd_index = 0;
                }
                break;

            case 1:
                if (c == '#') {
                    cmd[cmd_index] = '\0';
                    if (strcmp(cmd, "RST") == 0) command_flag = 1;
                    else if (strcmp(cmd, "OK") == 0) command_flag = 2;
                    state = 0;
                } else if (cmd_index < sizeof(cmd) - 1) {
                    cmd[cmd_index++] = c;
                }
                break;
        }
    }

    /* Consume bytes */
    index_buffer = 0;
}
