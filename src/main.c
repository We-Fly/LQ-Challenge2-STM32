/**
 * @file main.c
 * @author discodyer (cody23333@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-18
 * 
 * GNU General Public License v3.0
 * 
 */

#include "main.h"
#include "bmp.h"

int main(void)
{
  HAL_Init();
  
  // LED_GPIO_CLK_ENABLE();
  
  // GPIO_InitTypeDef GPIO_InitStruct;
  
  // GPIO_InitStruct.Pin = LED_PIN;
  // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  // GPIO_InitStruct.Pull = GPIO_PULLUP;
  // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  // HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct); 

  u8 t;
	// delay_init();	    	 //延时函数初始化	  
	// NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 

  // while (1)
  // {
  //   HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    
  //   HAL_Delay(1000);
  // }

  t=' ';
  while(1) 
	{		
		OLED_Clear();
	//	LED_ON;
		OLED_ShowCHinese(0,0,0);//中
		OLED_ShowCHinese(18,0,1);//景
		OLED_ShowCHinese(36,0,2);//园
		OLED_ShowCHinese(54,0,3);//电
		OLED_ShowCHinese(72,0,4);//子
		OLED_ShowCHinese(90,0,5);//科
		OLED_ShowCHinese(108,0,6);//技
		OLED_ShowString(0,2,"0.91' OLED TEST",15);
		//OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	 //	OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:",6);  
		OLED_ShowString(63,6,"CODE:",5);  
		OLED_ShowChar(48,6,t,1);//显示ASCII字符	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
			
	
		HAL_Delay(2000);
		// HAL_Delay(8000);
		// HAL_Delay(8000);
		// HAL_Delay(8000);
		OLED_Clear();
		OLED_DrawBMP(0,0,128,4,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
		HAL_Delay(8000);
		HAL_Delay(8000);
		HAL_Delay(8000);
		HAL_Delay(8000);
		HAL_Delay(8000);
		
	}	  
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1) {}
}


void MemManage_Handler(void)
{
  while (1) {}
}

void BusFault_Handler(void)
{
  while (1) {}
}

void UsageFault_Handler(void)
{
  while (1) {}
}

void SVC_Handler(void)
{
}


void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}