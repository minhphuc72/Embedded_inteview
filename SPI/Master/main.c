#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

//chon 3 chan bat ki co the xuat ra muc 0 or 1
#define SCK 	GPIO_Pin_6
#define MOSI 	GPIO_Pin_7
#define SS 		GPIO_Pin_8
#define PORT 	GPIOB

void config();
void spiInit();
void Transmit (uint8_t data);
void clock ();
void delay ();
void transmit (uint8_t data)
{
	//ha day ss xuong muc 0 de truyen data qua slave
	GPIO_ResetBits (GPIOB, SS);
	//dung vong lap for va phep and de truyen tung bit
	for (int i=0 ; i<8; i++)
	{
		//if kq & tai bit do la 1 thi set chan MOSI 
		if( data & (1<<i)) GPIO_SetBits (GPIOB , MOSI);
		//If kq & tai bit do la 0 thi reset chan MOSI
		GPIO_ResetBits (GPIOB ,MOSI);
		//cap clock cho Mater de truyen data
		clock ();
	}
	// sau khi truyen xong set chan SS len 1 de ket thuc
	GPIO_SetBits (GPIOB, SS);
}
	
int main (void)
{
	config ();
	spiInit ();
	
	uint8_t data  =170;
	
	delay (2000000);
	
	transmit(data);
}
void config()
{
	GPIO_InitTypeDef gpio;
	//cap clock cho GPIOB
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
	//d.ki cho 3 chan co chuc nang nhu GPIO
	gpio.GPIO_Pin = SCK | MOSI | SS;
	//d.ki 3 chan o che do PP ( 0 or 1)
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	//chon toc do cho chan GPIO : 2Mhz
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init (PORT, &gpio);
}

//ham trang thai ban dau cua Master
void spiInit()
{ 
	//d.ki trang thai ban dau SCK, MOSI : 0
	GPIO_ResetBits (GPIOB, SCK);
	GPIO_ResetBits (GPIOB, MOSI);
	//d.ki trang thai ban dau SS : 1
	GPIO_SetBits (GPIOB , SS);
}
 void delay(int ms)
 {
	 for (int i=0; i< ms; i++){};
 }
 
 //ham cap clock de nhan Master truyen data
void clock ()
{ 
	GPIO_SetBits (GPIOB, SCK);
	delay (1000000);
	GPIO_ResetBits (GPIOB, SCK);
	delay(1000000);
}