#include "misc.h"                       // Keil::Device:StdPeriph Drivers:Framework
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_flash.h"            // Keil::Device:StdPeriph Drivers:Flash
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI

#include "gpio.h"
#include "SysConf.h"
#include "WS2812.h"
#include <string.h>
#include "config.h" 


RGB_WS pasek2 [leftWindow+rightWindow+nearFridge];



int main(void)
{

	
	RCC_Conf ();
	if (SysTick_Config(SystemCoreClock / 1000))
  { 
     /* Capture error */ 
		while (1);
	}
	InitPorts ();
	confTIM2 ();
			setColor (0x00,0x00,0x00,pasek2);
	send_all_leds (pasek2) ;
	
	
		Delay (50);
	//g,r,b

	
  while (1)
  {
//	Delay(500);

	}
}

