//单片机头文件
#include "stm32f10x.h"

//硬件驱动
#include "key.h"
#include "delay.h"
#include "led.h"



/*
************************************************************
*	函数名称：	LED_Init
*
*	函数功能：	蜂鸣器初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Key_Init(void)
{

	GPIO_InitTypeDef gpio_initstruct;
	EXTI_InitTypeDef exit_initstucture;
	NVIC_InitTypeDef nvic_initstructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//打开GPIOC的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
	
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;					//设置为输出
	gpio_initstruct.GPIO_Pin = GPIO_Pin_1;						//将初始化的Pin脚
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;				//可承载的最大频率
	
	GPIO_Init(GPIOB, &gpio_initstruct);							//初始化GPIO
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	
	exit_initstucture.EXTI_Line = EXTI_Line1;
	exit_initstucture.EXTI_LineCmd = ENABLE;
	exit_initstucture.EXTI_Mode = EXTI_Mode_Interrupt;
	exit_initstucture.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&exit_initstucture);
	
	nvic_initstructure.NVIC_IRQChannel = EXTI1_IRQn;
	nvic_initstructure.NVIC_IRQChannelCmd = ENABLE;
	nvic_initstructure.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_initstructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvic_initstructure);

}

void EXTI1_IRQHandler(void)
{
	DelayXms(10);
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		if(led_info.LED_Status == LED_ON)
		{
			LED_Set(LED_OFF);
		}
		else
		{
			LED_Set(LED_ON);
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
