#include "stm32f10x.h"                  // Device header





void ADCinit(void)
{
//	��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC6��Ƶ
	
	//GPIO��ʼ��
	GPIO_InitTypeDef GPIO_InitStrcture;
	GPIO_InitStrcture.GPIO_Mode = GPIO_Mode_AIN;//ADCר��ģʽ
	GPIO_InitStrcture.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStrcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrcture);
	
	//ADC��ʼ��
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_55Cycles5);
	ADC_InitTypeDef ADC_InitStrcture;
	ADC_InitStrcture.ADC_ContinuousConvMode = DISABLE;//����ת��
	ADC_InitStrcture.ADC_DataAlign = ADC_DataAlign_Right;//�����Ҷ���
	ADC_InitStrcture.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
	ADC_InitStrcture.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_InitStrcture.ADC_NbrOfChannel = 1;
	ADC_InitStrcture.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ
	ADC_Init(ADC1,&ADC_InitStrcture);
	ADC_Cmd(ADC1,ENABLE);
	ADC_ResetCalibration(ADC1);//��ʼ��λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);//�ж��Ƿ�ʼ��λУ׼
	ADC_StartCalibration(ADC1);//��ʼУ׼
	while(ADC_GetCalibrationStatus(ADC1)  == SET);//�ж��Ƿ�ʼУ׼
	
}

uint16_t ADCgetvalue(void)//��ȡADֵ
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//��ʼת��
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//�ȴ�ת���Ƿ����
	return ADC_GetConversionValue(ADC1);//��ȡ�Ĵ�����ֵ
	
}
