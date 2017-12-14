//Program to vary the intensity of an LED (LD10), according to the input given.
//The intensity levels are: 10%, 33%, 66%, and 100%.

#include <stdio.h>
#include <LPC17xx.H>
void pwm_init(void);
void PWM1_IRQHandler(void);
void GPIO_init(void);

unsigned long int i,row=0,x,col;
unsigned long int int_value;
unsigned char flag, flag1;

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	GPIO_init();
	pwm_init();
	while(1)
	{
		for(i=0;i<500;i++);
	}
}

void GPIO_init(void)
{
	LPC_PINCON->PINSEL0=0x00;
	LPC_GPIO0->FIODIR = 0x100;
	LPC_GPIO0->FIOSETL =  0x0100;
	LPC_GPIOINT->IO0IntEnR = (0x0F<<4);
	NVIC_EnableIRQ(EINT3_IRQn);
	return;
}

void pwm_init(void)
{
	LPC_SC->PCONP |= (1<<16);
	LPC_PINCON ->PINSEL3 &= ~(0X0000C000);
	LPC_PINCON->PINSEL3|=0x00008000;
	LPC_PWM1->PR=0x00000000;
	LPC_PWM1->PCR=0x00001000;
	LPC_PWM1->MCR=0x00000003;
	LPC_PWM1->MR0=30000;
	LPC_PWM1->MR4=0x00000100;
	LPC_PWM1->LER=0x000000FF;
	LPC_PWM1->TCR=0x00000002;
	LPC_PWM1->TCR=0x00000009;
	NVIC_EnableIRQ(PWM1_IRQn);
	return;
}

void EINT3_IRQHandler(void)
{
	x = LPC_GPIOINT->IO0IntStatR;
	LPC_GPIOINT->IO0IntClr = 0xFFFFFFFF;
	x &= 0x0F0;
	x = x >> 4;
	
	if(x == 0x01)
		col =1;
	if(x == 0x02)
		col =2;
	if(x == 0x04)
		col =3;
	if(x == 0x08)
		col =4;
	
	if(col == 1)
		int_value = 30000*0.05;
	else if(col == 2)
		int_value = 30000*0.3;
	else if(col == 3)
		int_value = 30000*0.65;
	else if(col == 4)
		int_value = 30000*1;
}

void PWM1_IRQHandler(void)
{
	
	LPC_PWM1->LER = 0X000000FF;
	LPC_PWM1->MR4=int_value;
	LPC_PWM1->IR = 0XFF;
}