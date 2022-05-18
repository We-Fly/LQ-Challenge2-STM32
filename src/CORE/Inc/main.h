/**
 * @file main.h
 * @author discodyer (cody23333@gmail.com)
 * @brief 接受串口消息，并显示在OLED屏幕上
 * @version v0.1
 * @date 2022-05-18
 * 
 * 
 */
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "oled.h"

#define LED_PIN                                GPIO_PIN_2
#define LED_GPIO_PORT                          GPIOD
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOD_CLK_ENABLE()

// void SysTick_Handler(void);

// void NMI_Handler(void);

// void HardFault_Handler(void);

// void MemManage_Handler(void);

// void BusFault_Handler(void);

// void UsageFault_Handler(void);

// void SVC_Handler(void);

// void DebugMon_Handler(void);

// void PendSV_Handler(void);

extern uint16_t number;

// extern UART_HandleTypeDef huart1;

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
