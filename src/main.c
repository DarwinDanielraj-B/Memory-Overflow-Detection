#include "sdk_project_config.h"
#include "peripherals_lpuart_1.h"
#include "NVM.h"
int main(void)
{
    CLOCK_DRV_Init(&clockMan1_InitConfig0);

    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0,g_pin_mux_InitConfigArr0);

    LPUART_DRV_Init(INST_LPUART_1,&lpUartState0,&lpuart_0_InitConfig0);
    NvM_Init();
    while (1)
    {
    }
}
