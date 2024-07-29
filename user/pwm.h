#ifndef _pwm_h_
#define _pwm_h_
#include "stm32f10x.h"                  // Device header

void pwminit(void);//pwm输出初始化
void pwmsetcompare(uint8_t com);//设置输出占空比
void pwmsetHz(uint16_t hz);//获取输入频率
void ICinit(void);//输入捕获初始化
uint16_t ICgetpwm(TIM_TypeDef* TIMx);//获取输入占空比
uint16_t ICgetHz(TIM_TypeDef* TIMx);//获取输入频率
#endif
