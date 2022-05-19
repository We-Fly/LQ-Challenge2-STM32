/**
 * @file oled.h
 * @author discodyer (cody23333@gmail.com)
 * @brief 0.69寸OLED 接口演示例程(STM32F103ZE系列IIC)
 *            说明: 
 *           ----------------------------------------------------------------
 *           GND   电源地
 *           VCC   接5V或3.3v电源
 *           SCL   接PC13（SCL）
 *           SDA   接PC0（SDA）
 *           ----------------------------------------------------------------
 * @version v2.1
 * @date 2022-05-18
 * 
 * GNU General Public License v3.0
 * 
 */

#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stdlib.h"
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    		


//-----------------OLED IIC端口定义----------------  					   

#define OLED_SCL_PIN            GPIO_PIN_13                 //SCL IIC接口的时钟信号
#define OLED_SCL_GPIO_PORT      GPIOC                       //SCL IIC接口的GPIO通道
#define OLED_SDA_PIN            GPIO_PIN_0                  //SDA IIC接口的数据信号
#define OLED_SDA_GPIO_PORT      GPIOC                       //SDA IIC接口的GPIO通道
#define OLED_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()//初始化GPIO通道时钟

#define OLED_SCLK_Clr() HAL_GPIO_WritePin(OLED_SCL_GPIO_PORT,OLED_SCL_PIN,GPIO_PIN_RESET)
#define OLED_SCLK_Set() HAL_GPIO_WritePin(OLED_SCL_GPIO_PORT,OLED_SCL_PIN,GPIO_PIN_SET)

#define OLED_SDIN_Clr() HAL_GPIO_WritePin(OLED_SDA_GPIO_PORT,OLED_SDA_PIN,GPIO_PIN_RESET)
#define OLED_SDIN_Set() HAL_GPIO_WritePin(OLED_SDA_GPIO_PORT,OLED_SDA_PIN,GPIO_PIN_SET)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define u8 uint8_t
#define u32 uint32_t


/**
 * @brief 在对应的位置写数据
 * 
 * @param dat 
 * @param cmd 
 */
void OLED_WR_Byte(unsigned dat,unsigned cmd);  

/**
 * @brief 开启OLED显示
 * 
 */
void OLED_Display_On(void);

/**
 * @brief 关闭OLED显示
 * 
 */
void OLED_Display_Off(void);	   	

/**
 * @brief 初始化SSD1306
 * 
 */
void OLED_Init(void);

/**
 * @brief 清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	 
 * 
 */
void OLED_Clear(void);

// /**
//  * @brief 
//  * 
//  * @param x 
//  * @param y 
//  * @param t 
//  */
// void OLED_DrawPoint(u8 x,u8 y,u8 t);

// /**
//  * @brief 
//  * 
//  * @param x1 
//  * @param y1 
//  * @param x2 
//  * @param y2 
//  * @param dot 
//  */
// void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);

/**
 * @brief 
 * 
 * @param x x:0~127
 * @param y y:0~63
 * @param chr chr：是字符数组的某个元素
 * @param Char_Size Char_Size：是选择字体，这里字体有8x16和6x8两种类型 
 */
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);

/**
 * @brief 显示2个数字
 * 
 * @param x 起点坐标
 * @param y 起点坐标
 * @param num 数值(0~4294967295)
 * @param len 数字的位数
 * @param size2 字体大小
 */
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);

/**
 * @brief 显示一个字符号串
 * 
 * @param x 
 * @param y 
 * @param chr chr：是字符数组的某个元素
 * @param Char_Size Char_Size：是选择字体，这里字体有8x16和6x8两种类型 
 */
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 

/**
 * @brief 设置坐标函数 
 * 
 * @param x x是列（0-63，也就是列地址最多为0x3F，SH1107最多可达0x7F）
 * @param y y是页（0-15，也就是页地址最多为0x0F）
 */
void OLED_Set_Pos(unsigned char x, unsigned char y);

/**
 * @brief 显示汉字
 * 
 * @param x 左上角位置
 * @param y 0-3
 * @param no 字符在字典中的序号
 */
void OLED_ShowCHinese(u8 x,u8 y,u8 no);

/**
 * @brief 显示BMP图片,分辨率为64×128,显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
 * 
 * @param x0 x0：为起始的列数
 * @param y0 y0：为起始的页数
 * @param x1 x1：为终点列数
 * @param y1 y1：为终点页数
 * @param BMP BMP[]：为BMP图片的取模数组
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

/**
 * @brief 延迟50ms，直接用HAL_Delay()
 * 
 * @param Del_50ms 
 */
void Delay_50ms(unsigned int Del_50ms);

/**
 * @brief 延迟1ms，直接用HAL_Delay()
 * 
 * @param Del_1ms 
 */
void Delay_1ms(unsigned int Del_1ms);

/**
 * @brief 显示图片
 * 
 * @param fill_Data 
 */
void fill_picture(unsigned char fill_Data);

// /**
//  * @brief 
//  * 
//  */
// void Picture();

/**
 * @brief IIC 开始
 * 
 */
void IIC_Start();

/**
 * @brief IIC 关闭
 * 
 */
void IIC_Stop();

/**
 * @brief IIC 指令
 * (0xAE) 关闭显示
 * (0xD5) 设置时钟分频因子,震荡频率
 * (0x50) [3:0],分频因子;[7:4],震荡频率
 * (0xA8) 设置驱动路数
 * (0X3F) 默认0X3F(1/64) 
 * (0xD3) 设置显示偏移
 * (0X00) 默认为0
 * (0x40) 设置显示开始行 [5:0],行数.									    
 * (0x8D) 电荷泵设置
 * (0x14) bit2，开启/关闭
 * (0x20) 设置内存地址模式
 * (0x02) [1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
 * (0xA1) 段重定义设置,bit0:0,0->0;1,0->127; 
 * (0xC8) 设置COM扫描方向; 
 * (0xDA) 设置COM硬件引脚配置
 * (0x12) [5:4]配置
 * (0x81) 对比度设置
 * (0xEF) 1~255;默认0X7F (亮度设置,越大越亮)
 * (0xD9) 设置预充电周期
 * (0xf1) [3:0],PHASE 1;[7:4],PHASE 2;
 * (0xDB) 设置VCOMH 电压倍率
 * (0x30) [6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
 * (0xA4) 全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
 * (0xA6) 设置显示方式;bit0:1,反相显示;0,正常显示						   
 * (0xAF) 开启显示	 
 * 
 * @param IIC_Command 
 */
void Write_IIC_Command(unsigned char IIC_Command);

/**
 * @brief IIC 发送数据
 * 
 * @param IIC_Data 
 */
void Write_IIC_Data(unsigned char IIC_Data);

/**
 * @brief IIC 发送数据
 * 
 * @param IIC_Byte 
 */
void Write_IIC_Byte(unsigned char IIC_Byte);

/**
 * @brief IIC总线应答信号
 * 
 */
void IIC_Wait_Ack();
#endif  
	 



