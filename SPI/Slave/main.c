#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

#define SCK 	GPIO_Pin_6
#define MOSI 	GPIO_Pin_7
#define SS 		GPIO_Pin_8

void config (void);
uint8_t receive (void);

uint8_t receive (void)
{ 
	//tao 1 bien de nhan data tu Master
	uint8_t data ;
	//dung while de doc tin hieu tu Master
	//If tin hieu la 1 thi tiep tuc doc
	//if tin hieu la 0 thi thu hien cau lenh tiep theo
	while ((GPIO_ReadInputDataBit(GPIOB , SS)) ==1);
	//dung for va phep or de nhan gia tri tung bit khi Master truyen
	for(int i=0; i<8; i++)
	{
		// Doi chan CLK len 1 roi moi bat dau nhan cho dong bo
		while ((GPIO_ReadInputDataBit (GPIOB ,SCK)) == 0);
		
		// nhan tin hieu tu Mater chan : MOSI
		//Neu la 1 thi bit dang set len 1, neu la 0 thi bit do van la 0
		if ( (GPIO_ReadInputDataBit (GPIOB, MOSI)) ==1) data |= (1<<i);
		
		//Note: phai co khoang thoi gian doi de xung clock thay doi len xuong muc 0 va 1
		//doi clock xuong muc 0 thi bit tiep theo moi duoc nhan ( thoat khoi vong lap while)
		while ((GPIO_ReadInputDataBit (GPIOB ,SCK)) == 1);
	}
}


int main(void)
{
	config();
	while(1)
	{
		uint8_t receive ();
	}
	return 0;
	
}
void config()
{
		GPIO_InitTypeDef gpio;
	//cap clock cho GPIOB
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
	
	gpio.GPIO_Pin =SCK |MOSI;
	//d.ki 2 chan input keo xuong: 0
	gpio.GPIO_Mode = GPIO_Mode_IPD;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init (GPIOB, &gpio);
	
	gpio.GPIO_Pin = SS;
	//d.ki 2 chan input keo len: 1
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init (GPIOB, &gpio);
}