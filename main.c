#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "pwm.h"
#include "Delay.h"
#include "ADC.h"
int main()
{

	uint8_t pwm=50,flag=0;
	float ADC;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStrcture;
	GPIO_InitStrcture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStrcture.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStrcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrcture);
	GPIO_InitStrcture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStrcture.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStrcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrcture);
	
	
	pwminit();//pwm��ʼ��
	OLED_Init();//oled��ʼ��
	OLED_ShowString(1,2,"f:");
	OLED_ShowString(1,10,"KHz");
	OLED_ShowString(2,2,"PWM:");
	OLED_ShowString(2,10,"%");
	ICinit();//��ȡƵ��ռ�ձ�
	ADCinit();
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	while(1)
	{
		
		if(flag)
		{
			pwm-=1;
			if(pwm==0)
				flag=!flag;
		}
		else
		{
			pwm+=1;
			if(pwm==100)
				flag=!flag;
		}
		Delay_ms(15);
		pwmsetcompare(pwm);//����ռ�ձ�
		OLED_ShowNum(1,7,ICgetHz(TIM3)/1000,3);//��ȡƵ��
		OLED_ShowNum(2,7,ICgetpwm(TIM3),3);//��ȡռ�ձ�
		
		ADC = ADCgetvalue();//ADCֵ��ȡ
		ADC = ADC/4095*3.3;//ADC��ֵת��Ϊ��ѹֵ
		
		OLED_ShowNum(3,1,ADC,2);
		OLED_ShowChar(3,3,'.');
		OLED_ShowNum(3,4,(int)(ADC*10)%10,1);
		if(ADC>2)//������ֵ������ģ��Խ����ѹԽ��
			GPIO_SetBits(GPIOB,GPIO_Pin_14);
		else
			GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	}
	
}
