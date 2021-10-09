//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2018-10-31
//  最近修改   : 
//  功能描述   : OLED I2C接口演示例程(STM32F103系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND  电源地
//              VCC  3.3v电源
//              D0   PA0（SCL）
//              D1   PA1（SDA）
//              RES  PA2（SPI模块改成IIC模块需要接此引脚，IIC模块用户请忽略）
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "oled.h"
#include "led.h"
#include "bmp.h"
#include "ds18b20.h"
//////////////////////////////////////////////////////温度测试///////////////////////////////////////////////////////////////////
int main()
{
	u8 t;
	short temp;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);
	LED_Init();
	OLED_Init();	
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	while(DS18B20_Init())
	{
		OLED_ShowString(0,0,"DS18B20 Error",12,1);
		OLED_Refresh();
		delay_ms(500);
		OLED_Clear();
	}
//	while(1)
//	{
//	temp=DS18B20_Get_Temp();
//	printf("温度：%d.%d\r\n",temp/10,temp%10);
//	}
	OLED_ShowChinese(0,20,1,24,1);//温
	OLED_ShowChinese(24,20,2,24,1);//度
	OLED_ShowChar(48,20,':',24,1);
	OLED_ShowChar(96,20,'.',24,1);
	OLED_Refresh();
	while(1)
	{
		if(t%10==0)//100ms读取一次数值
		{
//		printf("温度：%d.%d\r\n",temp/10,temp%10);
		temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			OLED_ShowChar(60,20,'-',24,1);	
			OLED_Refresh();			
			temp=-temp;			
		}else		{OLED_ShowChar(60,20,' ',24,1);OLED_Refresh();}
		OLED_ShowNum(72,20,temp/10,2,24,1);
		OLED_ShowNum(108,20,temp%10,1,24,1);
		OLED_Refresh();
		}
		delay_ms(10);
		t++;
		if(t==20)//200msLED闪烁一次
		{
			t=0;
			led=!led;
		}
	}
}

