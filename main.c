#include "main.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_misc.h"

#define TIM2_Zakl_Frek 64000000
#define TIM2_Za_Sek 2
#define Ledka_Port GPIOA
#define Ledka_Pin GPIO_Pin_5

uint32_t TimingDelay;
RCC_ClocksTypeDef mRCC_Clocks;

void Delay(uint32_t ms_delay)
{
	TimingDelay = ms_delay;
	while(TimingDelay !=0);	
}	

int main(void)
{
	GPIO_InitTypeDef				GPIO_InitStucture;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef        NVIC_InitStructure;  

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	RCC_GetClocksFreq(&mRCC_Clocks);
	
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStucture.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStucture.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStucture.GPIO_Pin = Ledka_Pin;	
	GPIO_Init(Ledka_Port, &GPIO_InitStucture);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = TIM2_Zakl_Frek / TIM2_Za_Sek;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
	
    while (1)
    {
			
			
    }
}
