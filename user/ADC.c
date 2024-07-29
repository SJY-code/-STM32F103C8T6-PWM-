#include "stm32f10x.h"                  // Device header





void ADCinit(void)
{
//	打开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC6分频
	
	//GPIO初始化
	GPIO_InitTypeDef GPIO_InitStrcture;
	GPIO_InitStrcture.GPIO_Mode = GPIO_Mode_AIN;//ADC专属模式
	GPIO_InitStrcture.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStrcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrcture);
	
	//ADC初始化
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	ADC_InitTypeDef ADC_InitStrcture;
	ADC_InitStrcture.ADC_ContinuousConvMode = DISABLE;//单次转换
	ADC_InitStrcture.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
	ADC_InitStrcture.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发
	ADC_InitStrcture.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStrcture.ADC_NbrOfChannel = 1;
	ADC_InitStrcture.ADC_ScanConvMode = DISABLE;//非扫描模式
	ADC_Init(ADC1,&ADC_InitStrcture);
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);//开始复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//判断是否开始复位校准
	ADC_StartCalibration(ADC1);//开始校准
	while(ADC_GetCalibrationStatus(ADC1)  == SET);//判断是否开始校准
	
}

uint16_t ADCgetvalue(void)//获取AD值
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//开始转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//等待转换是否完成
	return ADC_GetConversionValue(ADC1);//读取寄存器数值
	
}
