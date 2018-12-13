#include "gpio.h"
#include "WS2812.h"
GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef exti;
NVIC_InitTypeDef nvic;
NVIC_InitTypeDef nvicTim;
TIM_TimeBaseInitTypeDef Timer1;

TIM_OCInitTypeDef TimerOC1;
RGB_WS pasek [leftWindow+rightWindow+nearFridge];

void InitPorts (void) {

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 |GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 ;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStruct);	
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);
	

	exti.EXTI_Line = EXTI_Line7	;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
	
	nvic.NVIC_IRQChannel = EXTI9_5_IRQn ;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x00;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

};



void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line7)) {
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 1) {
         setColor (defaultG,defaultR,defaultB,pasek);
		send_all_leds (pasek) ;
		
		TIM_SetCompare1(TIM2, 30000);
		TIM_SetCounter (TIM2,0);
		TIM_Cmd(TIM2,ENABLE);
		TIM_ITConfig(TIM2, TIM_IT_CC1,ENABLE);
	//	turnOn();
        } 
    EXTI_ClearITPendingBit(EXTI_Line7);
		
		NVIC_ClearPendingIRQ (EXTI9_5_IRQn);
    }
}

void TIM2_IRQHandler ()
{
	if (TIM_GetITStatus (TIM2, TIM_IT_CC1) != RESET)	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		
		setColor (0x00,0x00,0x00,pasek);
		send_all_leds (pasek) ;
		
		TIM_Cmd(TIM2, DISABLE);
		TIM_ITConfig (TIM2, TIM_IT_CC1, DISABLE);
	}
	
}


void confTIM2(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	nvicTim.NVIC_IRQChannel = TIM2_IRQn ;
	nvicTim.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvicTim.NVIC_IRQChannelSubPriority = 0x00;
	nvicTim.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicTim);
	
  Timer1.TIM_Period = 65000;
  Timer1.TIM_Prescaler = 36000;
  Timer1.TIM_ClockDivision = TIM_CKD_DIV1;
  Timer1.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit (TIM2, &Timer1);
	
	TimerOC1.TIM_OCMode = TIM_OCMode_Timing;     
  TimerOC1.TIM_OutputState = TIM_OutputState_Enable;   
  TimerOC1.TIM_Pulse = 60000;    
  TimerOC1.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init (TIM2, &TimerOC1);
	
	TIM_OC1PreloadConfig (TIM2,TIM_OCPreload_Disable);	
}




