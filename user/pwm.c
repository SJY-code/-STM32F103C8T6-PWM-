#include "stm32f10x.h"                  // Device header




void pwminit(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//计数器模式
	TIM_TimeBaseInitStructure.TIM_Period=100-1;//自动重装阈值ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//72mhz,7200分频PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitstructure;
	TIM_OCStructInit(&TIM_OCInitstructure);
	TIM_OCInitstructure.TIM_OCMode=TIM_OCMode_PWM1;//输出比较模式
	TIM_OCInitstructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出极性
	TIM_OCInitstructure.TIM_OutputState=TIM_OutputState_Enable;//输出使能
	TIM_OCInitstructure.TIM_Pulse=0;//CCR
	TIM_OC1Init(TIM2,&TIM_OCInitstructure);
	//通道1，
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	TIM_Cmd(TIM2,ENABLE);//使能
	
	
	
}
void pwmsetcompare(uint8_t com)
{
	TIM_SetCompare1(TIM2,com);
	
}

void pwmsetHz(uint16_t hz)
{
	TIM_PrescalerConfig(TIM2,hz, TIM_PSCReloadMode_Immediate);
	
	
}
void ICinit(void)//输入捕获初始化
{
	//打开时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//GPIO初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//TIM定时器初始化
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrcture;
	TIM_TimeBaseInitStrcture.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStrcture.TIM_Period  = 65536-1;
	TIM_TimeBaseInitStrcture.TIM_Prescaler = 72 -1;
	TIM_TimeBaseInitStrcture.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrcture);
	//输入捕获初始化
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//通道一
	TIM_ICInitStructure.TIM_ICFilter = 0xf;//滤波器采样频率
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//上升沿触发
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//1分频，每次触发均有效
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//直连模式
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);//触发通道
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//通道一
//	TIM_ICInitStructure.TIM_ICFilter = 0xf;//滤波器采样频率
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//下降沿触发
//	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//1分频，每次触发均有效
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//交叉模式
//	TIM_SelectInputTrigger(TIM3,TIM_TS_TI2FP2);//触发通道
//	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
//	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);//启动交叉模式
	TIM_Cmd(TIM3,ENABLE);//定时器使能
	
}

uint16_t ICgetpwm(TIM_TypeDef* TIMx)
{
	
	return  TIM_GetCapture2(TIMx)*100/TIM_GetCapture1(TIM3);
}

uint16_t ICgetHz(TIM_TypeDef* TIMx)
{
	
	return 1000000/TIM_GetCapture1(TIMx);//fc = 72M/(PSC + 1)
	
}
