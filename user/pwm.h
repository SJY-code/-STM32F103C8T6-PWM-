#ifndef _pwm_h_
#define _pwm_h_
#include "stm32f10x.h"                  // Device header

void pwminit(void);//pwm�����ʼ��
void pwmsetcompare(uint8_t com);//�������ռ�ձ�
void pwmsetHz(uint16_t hz);//��ȡ����Ƶ��
void ICinit(void);//���벶���ʼ��
uint16_t ICgetpwm(TIM_TypeDef* TIMx);//��ȡ����ռ�ձ�
uint16_t ICgetHz(TIM_TypeDef* TIMx);//��ȡ����Ƶ��
#endif
