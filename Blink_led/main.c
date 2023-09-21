#include "stm32f10x.h"
void delay(int time)
{
	for (int i=1; i<time;i++);
}
int main(void)
{
	RCC->APB2ENR |=RCC_APB2ENR_IOPCEN;
	GPIOC ->CRH &= ~(GPIO_CRH_MODE13 |GPIO_CRH_CNF13);
	GPIOC ->CRH |= GPIO_CRH_MODE13_0;
  while (1)
	{
		GPIOC->BSRR= GPIO_BSRR_BR13;
		delay(3000000);
		GPIOC->BSRR= GPIO_BSRR_BS13;
		delay(3000000);
	}
}