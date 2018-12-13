#include "WS2812.h"
#include "SysConf.h"

//  bit=0							bit=1
//	+-------+			+		+-----------+		+
//	|		|			|		|			|		|
//	|		|			|		|			|		|
//	|		|			|		|			|		|
//	|		|			|		|			|		|
//	|		|			|		|			|		|
//	|		+-----------+		|			+-------+
//	  350ns		900ns				900		   350ns

// TH+TL=1250ns

// "NOP"=20,1ns



RGB_WS belt [leftWindow+rightWindow+nearFridge];


static void send_zero(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
		GPIOx->BSRR = GPIO_Pin;
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); 
	__nop(); __nop(); __nop(); __nop(); __nop();

	  GPIOx->BRR  = GPIO_Pin;
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		  


}

static void send_one(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	 GPIOx->BSRR = GPIO_Pin;
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop(); __nop();
		__nop(); __nop(); __nop(); __nop(); __nop(); __nop();  

	  GPIOx->BRR  = GPIO_Pin;
 	  

}

void send_rgb (uint8_t g,uint8_t r,uint8_t b, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{


	if (g & 128) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (g & 64) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (g & 32) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (g & 16) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (g & 8) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (g & 4) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (g & 2) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (g & 1) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);

	if (r & 128) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (r & 64) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (r & 32) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (r & 16) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (r & 8) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (r & 4) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (r & 2) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (r & 1) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);

	if (b & 128) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (b & 64) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (b & 32) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (b & 16) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (b & 8) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (b & 4) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (b & 2) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);
	if (b & 1) 	send_one(GPIOx,GPIO_Pin); else send_zero(GPIOx,GPIO_Pin);


}

void send_all_leds (RGB_WS * leds ) {

uint8_t i;
uint8_t * wsk= (uint8_t *) leds;


for (i = 0; i < nearFridge; i++) {
	send_rgb(*wsk, *(wsk+1), *(wsk+2), GPIOA, GPIO_Pin_6);
	wsk+=3;

}

for (i = 0; i < leftWindow; i++) {
	send_rgb(*wsk, *(wsk+1), *(wsk+2), GPIOA, GPIO_Pin_7);
	wsk+=3;

}

for (i = 0; i < rightWindow; i++) {
	send_rgb(*wsk, *(wsk+1), *(wsk+2), GPIOA, GPIO_Pin_5);
	wsk+=3;

}

}

void setColor(uint8_t g,uint8_t r,uint8_t b, RGB_WS * leds) {
	uint8_t i;
		for ( i = 0; i < getAllLeds () ; i++) {
			
			leds[i].r = r;
			leds[i].g = g;
			leds[i].b = b;

}
}

uint8_t getAllLeds()
{
return leftWindow + rightWindow +nearFridge ;
}

void turnOn(void)
{
	uint8_t i;
	
	
	for(i = 0; i < getAllLeds () ; i++)
  {
			belt[i].r = defaultR;
			belt[i].g = defaultG;
			belt[i].b = defaultB;
			send_all_leds (belt);
			Delay(190);
  }
}

void turnOff(void)
{
	uint8_t i;
	
	
	for(i = 0; i < getAllLeds () ; i++)
  {
			belt[i].r = 0x00;
			belt[i].g = 0x00;
			belt[i].b = 0x00;
			send_all_leds (belt);
			Delay(190);
			
  }
}

