//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//Ӳ������
#include "led.h"


LED_INFO led_info = {0};


/*
************************************************************
*	�������ƣ�	LED_Init
*
*	�������ܣ�	��������ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void LED_Init(void)
{

	GPIO_InitTypeDef gpio_initstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		//��GPIOC��ʱ��
	
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;					//����Ϊ���
	gpio_initstruct.GPIO_Pin = GPIO_Pin_13;						//����ʼ����Pin��
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;				//�ɳ��ص����Ƶ��
	
	GPIO_Init(GPIOC, &gpio_initstruct);							//��ʼ��GPIO
	
	LED_Set(LED_OFF);											//��ʼ����ɺ󣬹رշ�����

}

/*
************************************************************
*	�������ƣ�	LED_Set
*
*	�������ܣ�	����������
*
*	��ڲ�����	status�����ط�����
*
*	���ز�����	��
*
*	˵����		��-LED_ON		��-LED_OFF
************************************************************
*/
void LED_Set(_Bool status)
{
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, status == LED_ON ? Bit_RESET : Bit_SET);		//���status����LED_ON���򷵻�Bit_SET�����򷵻�Bit_RESET
	
	led_info.LED_Status = status;

}
