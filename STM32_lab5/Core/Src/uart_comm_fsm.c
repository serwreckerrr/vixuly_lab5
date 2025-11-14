/*
 * uart_comm_fsm.c
 *
 *  Created on: Nov 14, 2025
 *      Author: Admin
 */

#include "main.h"
#include "uart_comm_fsm.h"
#include "command_parser_fsm.h"
#include <stdio.h>
#include <string.h>

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

#define TIMEOUT_MS 3000

uint32_t ADC_value = 0;
static uint8_t waiting_for_ack = 0;
static uint32_t last_send_time = 0;
static char tx_buffer[30];

void uart_communication_fsm(void)
{
    switch (command_flag) {
        case 1: // !RST#
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, 100);
            ADC_value = HAL_ADC_GetValue(&hadc1);

            sprintf(tx_buffer, "!ADC=%lu#\r\n", ADC_value);
            HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 1000);

            waiting_for_ack = 1;
            last_send_time = HAL_GetTick();
            command_flag = 0;
            break;

        case 2: // !OK#
            waiting_for_ack = 0;
            command_flag = 0;
            HAL_UART_Transmit(&huart2, (uint8_t*)"ACK received\r\n", 13, 100);
            break;
    }

    // Timeout resend
    if (waiting_for_ack) {
        if (HAL_GetTick() - last_send_time > TIMEOUT_MS) {
            HAL_UART_Transmit(&huart2, (uint8_t*)tx_buffer, strlen(tx_buffer), 1000);
            last_send_time = HAL_GetTick();
        }
    }
}
