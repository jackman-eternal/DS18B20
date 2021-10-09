//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2018-10-31
//  ����޸�   : 
//  ��������   : OLED I2C�ӿ���ʾ����(STM32F103ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND  ��Դ��
//              VCC  3.3v��Դ
//              D0   PA0��SCL��
//              D1   PA1��SDA��
//              RES  PA2��SPIģ��ĳ�IICģ����Ҫ�Ӵ����ţ�IICģ���û�����ԣ�
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2018-10-31
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "oled.h"
#include "led.h"
#include "bmp.h"
#include "ds18b20.h"
//////////////////////////////////////////////////////�¶Ȳ���///////////////////////////////////////////////////////////////////
int main()
{
	u8 t;
	short temp;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
	LED_Init();
	OLED_Init();	
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
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
//	printf("�¶ȣ�%d.%d\r\n",temp/10,temp%10);
//	}
	OLED_ShowChinese(0,20,1,24,1);//��
	OLED_ShowChinese(24,20,2,24,1);//��
	OLED_ShowChar(48,20,':',24,1);
	OLED_ShowChar(96,20,'.',24,1);
	OLED_Refresh();
	while(1)
	{
		if(t%10==0)//100ms��ȡһ����ֵ
		{
//		printf("�¶ȣ�%d.%d\r\n",temp/10,temp%10);
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
		if(t==20)//200msLED��˸һ��
		{
			t=0;
			led=!led;
		}
	}
}

