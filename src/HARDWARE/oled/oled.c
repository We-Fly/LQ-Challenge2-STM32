/**
 * @file oled.c
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

#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   


/**
 * @brief IIC 开始
 * 
 */
void IIC_Start()
{
	OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**
 * @brief IIC 关闭
 * 
 */
void IIC_Stop()
{
	OLED_SCLK_Set();
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

/**
 * @brief IIC总线应答信号
 * 
 */
void IIC_Wait_Ack()
{

	// GPIOB->CRH &= 0XFFF0FFFF;	//设置PB12为上拉输入模式
	// GPIOB->CRH |= 0x00080000;
	// OLED_SDA = 1;
	// delay_us(1);
	// OLED_SCL = 1;
	// delay_us(50000);
/*	while(1)
	{
		if(!OLED_SDA)				//判断是否接收到OLED 应答信号
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//设置PB12为通用推免输出模式
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}


/**
 * @brief IIC 发送数据
 * 
 * @param IIC_Byte 数据
 */
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++){
		m=da;
		// OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80){
			OLED_SDIN_Set();
		}else{
			OLED_SDIN_Clr();
		}
		da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
	}
}

/**
 * @brief IIC 指令，详见oled.h
 * 
 * @param IIC_Command 
 */
void Write_IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);           //Slave address,SA0=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
	IIC_Stop();
}

/**
 * @brief IIC 发送数据
 * 
 * @param IIC_Data 
 */
void Write_IIC_Data(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
	IIC_Stop();
}

/**
 * @brief 写数据
 * 
 * @param dat 
 * @param cmd 
 */
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd){
		Write_IIC_Data(dat);
	}else{
		Write_IIC_Command(dat);
	}
}


/**
 * @brief 显示图片
 * 
 * @param fill_Data 
 */
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,OLED_CMD);		//page0-page1设置页地址
		OLED_WR_Byte(0x00,OLED_CMD);		//low column start address设置显示的列的低地址
		OLED_WR_Byte(0x10,OLED_CMD);		//high column start address设置显示的列的高地址
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,OLED_DATA);
			}
	}
}


/**
 * @brief 延迟50ms，直接用HAL_Delay()
 * 
 * @param Del_50ms 
 */
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

/**
 * @brief 延迟1ms，直接用HAL_Delay()
 * 
 * @param Del_1ms 
 */
void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

/**
 * @brief 设置坐标函数 
 * 
 * @param x x是列（0-63，也就是列地址最多为0x3F，SH1107最多可达0x7F）
 * @param y y是页（0-15，也就是页地址最多为0x0F）
 */
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  


/**
 * @brief 开启OLED显示
 * 
 */
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}


/**
 * @brief 关闭OLED显示
 * 
 */
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 


/**
 * @brief 清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
 * 
 */
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

/**
 * @brief 开启显示器
 * 
 */
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}


/**
 * @brief 
 * 
 * @param x x:0~127
 * @param y y:0~63
 * @param chr chr：是字符数组的某个元素
 * @param Char_Size Char_Size：是选择字体，这里字体有8x16和6x8两种类型 
 */
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}


/**
 * @brief m^n函数
 * 
 * @param m 
 * @param n 
 * @return u32 
 */
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  


/**
 * @brief 显示2个数字
 * 
 * @param x 起点坐标
 * @param y 起点坐标
 * @param num 数值(0~4294967295)
 * @param len 数字的位数
 * @param size2 字体大小
 */
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

/**
 * @brief 显示一个字符号串
 * 
 * @param x 
 * @param y 
 * @param chr chr：是字符数组的某个元素
 * @param Char_Size Char_Size：是选择字体，这里字体有8x16和6x8两种类型 
 */
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}


/**
 * @brief 显示汉字
 * 
 * @param x 左上角位置
 * @param y 0-3
 * @param no 字符在字典中的序号
 */
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

/**
 * @brief 显示BMP图片,分辨率为64×128,显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
 * 
 * @param x0 x0：为起始的列数
 * @param y0 y0：为起始的页数
 * @param x1 x1：为终点列数
 * @param y1 y1：为终点页数
 * @param BMP BMP[]：为BMP图片的取模数组
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 


/**
 * @brief 初始化SSD1306
 * 
 */
void OLED_Init(void)
{ 	
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_3|GPIO_Pin_8;	 //PD3,PD6推挽输出  
 	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	// GPIO_Init(GPIOD, &GPIO_InitStructure);	  //初始化GPIOD3,6
 	// GPIO_SetBits(GPIOD,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_3|GPIO_Pin_8);	//PD3,PD6 输出高

	GPIO_InitTypeDef GPIO_InitStructure;

	OLED_GPIO_CLK_ENABLE();
	
	GPIO_InitStructure.Pin = OLED_SCL_PIN|OLED_SDA_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure); 

//  #if OLED_MODE==1
 
//  	GPIO_InitStructure.GPIO_Pin =0xFF; //PC0~7 OUT推挽输出
//  	GPIO_Init(GPIOC, &GPIO_InitStructure);
//  	GPIO_SetBits(GPIOC,0xFF); //PC0~7输出高

//  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //PG13,14,15 OUT推挽输出
//  	GPIO_Init(GPIOG, &GPIO_InitStructure);
//  	GPIO_SetBits(GPIOG,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //PG13,14,15 OUT  输出高

//  #else
//  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 //PC0,1 OUT推挽输出
//  	GPIO_Init(GPIOC, &GPIO_InitStructure);
//  	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);						 //PC0,1 OUT  输出高

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //PG15 OUT推挽输出	  RST
//  	GPIO_Init(GPIOG, &GPIO_InitStructure);
//  	GPIO_SetBits(GPIOG,GPIO_Pin_15);						 //PG15 OUT  输出高


//  #endif
	HAL_Delay(200);
	OLED_WR_Byte(0xAE,OLED_CMD);//关闭显示
	
	OLED_WR_Byte(0x40,OLED_CMD);//---set low column address
	OLED_WR_Byte(0xB0,OLED_CMD);//---set high column address

	OLED_WR_Byte(0xC8,OLED_CMD);//-not offset

	OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
	OLED_WR_Byte(0xff,OLED_CMD);

	OLED_WR_Byte(0xa1,OLED_CMD);//段重定向设置


	OLED_WR_Byte(0xa0,OLED_CMD);//显示方向
	OLED_WR_Byte(0xc0,OLED_CMD);

	OLED_WR_Byte(0xa6,OLED_CMD);//
	
	OLED_WR_Byte(0xa8,OLED_CMD);//设置驱动路数
	OLED_WR_Byte(0x1f,OLED_CMD);
	
	OLED_WR_Byte(0xd3,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	
	OLED_WR_Byte(0xd5,OLED_CMD);
	OLED_WR_Byte(0xf0,OLED_CMD);
	
	OLED_WR_Byte(0xd9,OLED_CMD);
	OLED_WR_Byte(0x22,OLED_CMD);
	
	OLED_WR_Byte(0xda,OLED_CMD);
	OLED_WR_Byte(0x02,OLED_CMD);
	
	OLED_WR_Byte(0xdb,OLED_CMD);
	OLED_WR_Byte(0x49,OLED_CMD);
	
	OLED_WR_Byte(0x8d,OLED_CMD);
	OLED_WR_Byte(0x14,OLED_CMD);
	
	OLED_WR_Byte(0xaf,OLED_CMD);
	OLED_Clear();
}  
