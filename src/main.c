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