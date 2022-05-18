/**
 * @file main.c
 * @author discodyer (cody23333@gmail.com)
 * @brief 接受串口消息，并显示在OLED屏幕上
 * @version v0.1
 * @date 2022-05-18
 * 
 * GNU General Public License v3.0
 * 
 */

#include "main.h"
#include "bmp.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "stdio.h"
#include <string.h>
 
uint8_t aRxBuffer;			//接收中断缓冲
uint8_t Uart1_Rx_Cnt = 0;		//接收缓冲计数
#define RXBUFFERSIZE  256

char RxBuffer[RXBUFFERSIZE]; 

void SystemClock_Config(void);

uint16_t number = 0;

uint8_t SentData[14] = "hello,world!\r\n";

uint8_t buffData;

int main(void)
{

    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_TIM1_Init();
    /* USER CODE BEGIN 2 */
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_TIM1_Init();
    /* USER CODE BEGIN 2 */
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);


	/* Initialize all configured peripherals */
	// MX_GPIO_Init();
	// MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */
	// HAL_UART_Receive_IT(&huart1, (uint8_t *)&buffData, 1);   //再开启接收中断
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&buffData, 1);

	// LED_GPIO_CLK_ENABLE();

	// GPIO_InitTypeDef GPIO_InitStruct;

	// GPIO_InitStruct.Pin = LED_PIN;
	// GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	// GPIO_InitStruct.Pull = GPIO_PULLUP;
	// GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	// HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct); 

	// u8 t;
	// delay_init();	    	 //延时函数初始化	  
	// NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 

	// while (1)
	// {
	//   HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);

	//   HAL_Delay(1000);
	// }

	// t=' ';
	while(1) 
	{		
		OLED_Clear();
		// LED_ON;
		// OLED_ShowCHinese(0,0,0);//红
		// OLED_ShowCHinese(18,0,1);//绿
		// OLED_ShowCHinese(36,0,2);//蓝
		// OLED_ShowCHinese(54,0,3);//色
		// OLED_ShowCHinese(72,0,4);//正
		// OLED_ShowCHinese(90,0,5);//方
		// OLED_ShowCHinese(108,0,6);//矩
		// OLED_ShowCHinese(0,2,7);//三
		// OLED_ShowCHinese(18,2,8);//角
		// OLED_ShowCHinese(36,2,9);//圆
		// OLED_ShowCHinese(54,2,10);//形
		// OLED_ShowCHinese(72,2,11);//未
		// OLED_ShowCHinese(90,2,12);//知
		// OLED_ShowCHinese(108,2,13);//状
		// OLED_ShowCHinese(90,2,14);//颜
		
		OLED_ShowCHinese(0,0,14);//颜
		OLED_ShowCHinese(18,0,3);//色
		OLED_ShowChar(36,1,':',1);
		OLED_ShowCHinese(54,0,11);//未
		OLED_ShowCHinese(72,0,12);//知
		OLED_ShowCHinese(0,2,10);//形
		OLED_ShowCHinese(18,2,13);//状
		OLED_ShowChar(36,3,':',1);
		OLED_ShowCHinese(54,2,11);//未
		OLED_ShowCHinese(72,2,12);//知
		//红(0) 绿(1) 蓝(2) 色(3) 正(4) 方(5) 矩(6) 三(7) 角(8) 圆(9) 形(10) 未(11) 知(12) 状(13) 颜(14)
		// OLED_ShowString(0,2,"0.91' OLED TEST",15);
		// OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	    // OLED_ShowString(20,4,"2014/05/01");  
		// OLED_ShowString(0,6,"ASCII:",6);  
		// OLED_ShowString(63,6,"CODE:",5);  
		// OLED_ShowChar(48,6,t,1);//显示ASCII字符	   
		// t++;
		// if(t>'~')t=' ';
		// OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值
		HAL_Delay(2000);
		// OLED_Clear();
		// OLED_DrawBMP(0,0,128,4,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		HAL_UART_Transmit(&huart1, SentData, 14, 500);
	}	  
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_2)
    {
        number = number + 1;
        printf("%d    \r\n",number);
    }
}


#pragma import(__use_no_semihosting)
void _sys_exit(int x) {
    x = x;
}
struct __FILE {
    int handle;
};
FILE __stdout;


// /**
//  * @brief 重定向c库函数printf到DEBUG_USARTx
//  * 
//  */
// int fputc(int ch, FILE *f)
// {
// 	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
// 	return ch;
// }
 
// /**
//  * @brief 重定向c库函数getchar,scanf到DEBUG_USARTx
//  * 
//  */
// int fgetc(FILE *f)
// {
// 	uint8_t ch = 0;
// 	HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
// 	return ch;
// }


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//   /* Prevent unused argument(s) compilation warning */
//   UNUSED(huart);
//   /* NOTE: This function Should not be modified, when the callback is needed,
//            the HAL_UART_TxCpltCallback could be implemented in the user file
//    */
 
// 	if(Uart1_Rx_Cnt >= 255)  //溢出判断
// 	{
// 		Uart1_Rx_Cnt = 0;
// 		memset(RxBuffer,0x00,sizeof(RxBuffer));
// 		HAL_UART_Transmit(&huart1, (uint8_t *)"数据溢出", 10,0xFFFF); 	
        
// 	}
// 	else
// 	{
// 		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //接收数据转存
	
// 		if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //判断结束位
// 		{
// 			HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt,0xFFFF); //将收到的信息发送出去
//             while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
// 			Uart1_Rx_Cnt = 0;
// 			memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
// 		}
// 	}
	
	    //发送
        HAL_UART_Transmit(&huart1,&buffData,1,100);
        //开启一次中断
        HAL_UART_Receive_IT(&huart1,&buffData,1);
	// HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //再开启接收中断
}

#endif /* USE_FULL_ASSERT */


// void SysTick_Handler(void)
// {
//   HAL_IncTick();
// }

// void NMI_Handler(void)
// {
// }

// void HardFault_Handler(void)
// {
//   while (1) {}
// }


// void MemManage_Handler(void)
// {
//   while (1) {}
// }

// void BusFault_Handler(void)
// {
//   while (1) {}
// }

// void UsageFault_Handler(void)
// {
//   while (1) {}
// }

// void SVC_Handler(void)
// {
// }


// void DebugMon_Handler(void)
// {
// }

// void PendSV_Handler(void)
// {
// }