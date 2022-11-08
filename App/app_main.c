
#include "i2s.h"
#include "main.h"
#include "usart.h"
#include <stdint.h>

#define BUF_SIZE (80000U)

static uint16_t i2s_mems_buf[BUF_SIZE];

int main(void)
{
    STM32_HAL_Init();

    const char *str = "Hello world ! \r\n";
    i2s_read(i2s_mems_buf, BUF_SIZE);
    while (1) {

        HAL_Delay(1000);

        // uart_send((uint8_t *)&i2s_mems_buf, sizeof(i2s_mems_buf) / sizeof(uint8_t));

        // uart_send(str, strlen(str));
        HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
    }
}

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    uart_send("I2S Half Complete \r\n", strlen("I2S Half Complete \r\n"));
    uart_send((uint8_t *)&i2s_mems_buf, BUF_SIZE / 2U);
    uart_send("\r\n End send ", strlen("\r\n End send "));
    HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    uart_send("I2S Complete \r\n", strlen("I2S Complete \r\n"));
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}