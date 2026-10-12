/*
 * NVM.c
 *
 *  Created on: 12-Oct-2026
 *      Author: darwi
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "NVM.h"
#include "lpuart_driver.h"
#include "peripherals_lpuart_1.h"
#define VARIABLE_COUNT  10u
#define MAX_TOTAL_SIZE  512u
#define UART_INSTANCE  INST_LPUART_1
typedef struct{
    uint16_t sizeBytes;
} VariableConfig;
static const VariableConfig variableConfig[VARIABLE_COUNT] =
{{2u},{4u},{20u},{8u},{16u},{32u},{10u},{12u},{6u},{24u}};
static void Uart_Print(const char *text){
    LPUART_DRV_SendDataBlocking(
        UART_INSTANCE,
        (uint8_t *)text,
        (uint32_t)strlen(text),
        OSIF_WAIT_FOREVER
    );
}
void Det_ReportError(uint16_t moduleId, uint8_t errorId){
    char message[80];
    (void)snprintf(message, sizeof(message),
                   "DET error: module %u, error %u\r\n",
                   (unsigned int)moduleId,
                   (unsigned int)errorId);
    Uart_Print(message);
}
void NvM_Init(void){
    uint32_t total_size = 0u;
    char message[80];
    for (uint32_t i = 0u; i < VARIABLE_COUNT; i++)
    {
        total_size += variableConfig[i].sizeBytes;
    }
    (void)snprintf(message, sizeof(message),
                   "Total configured size: %lu bytes\r\n",
                   (unsigned long)total_size);
    Uart_Print(message);
    if (total_size > MAX_TOTAL_SIZE)
    {
        Uart_Print("Overflow: configuration rejected\r\n");
        Det_ReportError(1u, 1u);
        return;
    }
    Uart_Print("Configuration accepted\r\n");
}
