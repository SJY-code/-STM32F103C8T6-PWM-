#include "stm32f10x.h"                  // Device header




void pwminit(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//������ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//�Զ���װ��ֵARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//72mhz,7200��ƵPSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitstructure;
	TIM_OCStructInit(&TIM_OCInitstructure);
	TIM_OCInitstructure.TIM_OCMode=TIM_OCMode_PWM1;//����Ƚ�ģʽ
	TIM_OCInitstructure.TIM_OCPolarity=TIM_OCPolarity_High;//�������
	TIM_OCInitstructure.TIM_OutputState=TIM_OutputState_Enable;//���ʹ��
	TIM_OCInitstructure.TIM_Pulse=0;//CCR
	TIM_OC1Init(TIM2,&TIM_OCInitstructure);
	//ͨ��1��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	TIM_Cmd(TIM2,ENABLE);//ʹ��
	
	
	
}
void pwmsetcompare(uint8_t com)
{
	TIM_SetCompare1(TIM2,com);
	
}

void pwmsetHz(uint16_t hz)
{
	TIM_PrescalerConfig(TIM2,hz, TIM_PSCReloadMode_Immediate);
	
	
}
void ICinit(void)//���벶���ʼ��
{
	//��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//GPIO��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//TIM��ʱ����ʼ��
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrcture;
	TIM_TimeBaseInitStrcture.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStrcture.TIM_Period  = 65536-1;
	TIM_TimeBaseInitStrcture.TIM_Prescaler = 72 -1;
	TIM_TimeBaseInitStrcture.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrcture);
	//���벶���ʼ��
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//ͨ��һ
	TIM_ICInitStructure.TIM_ICFilter = 0xf;//�˲�������Ƶ��
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//�����ش���
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//1��Ƶ��ÿ�δ�������Ч
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//ֱ��ģʽ
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);//����ͨ��
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//ͨ��һ
//	TIM_ICInitStructure.TIM_ICFilter = 0xf;//�˲�������Ƶ��
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//�½��ش���
//	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//1��Ƶ��ÿ�δ�������Ч
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//����ģʽ
//	TIM_SelectInputTrigger(TIM3,TIM_TS_TI2FP2);//����ͨ��
//	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
//	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);//��������ģʽ
	TIM_Cmd(TIM3,ENABLE);//��ʱ��ʹ��
	
}

uint16_t ICgetpwm(TIM_TypeDef* TIMx)
{
	
	return  TIM_GetCapture2(TIMx)*100/TIM_GetCapture1(TIM3);
}

uint16_t ICgetHz(TIM_TypeDef* TIMx)
{
	
	return 1000000/TIM_GetCapture1(TIMx);//fc = 72M/(PSC + 1)
	
}
