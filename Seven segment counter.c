#include <LPC17xx.h>
#include <stdio.h>

 #define	FIRST_SEG	0xFFF87FFF
 #define	SECOND_SEG	0xFFF8FFFF
 #define	THIRD_SEG	0xFFF97FFF
 #define	FOURTH_SEG	0xFFF9FFFF
 #define	DISABLE_ALL 0xFA7FFFFF

 int dig1=0x09,dig2=0x09,dig3=0x09,dig4=0x09;
 unsigned int twenty_count = 0x00,dig_count=0x00,temp1=0x00;
 unsigned char array_dec[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x58,0x5E,0x79,0x71};
 unsigned char tmr0_flg = 0x00,one_sec_flg = 0x00;
 unsigned long int temp2 = 0x00000000,i=0;
 unsigned int temp3=0x00;
 unsigned int maskdecoder=0x00078000;
 unsigned int masknum=0x00000FF0;
 void TIMER0_Init(void);
 void TIMER0_IRQHandler(void);
 void Display(void);
 
 
 int main(void)
 {    
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 = 0x0;	 //P0.4 to P0.15 GPIO data lines
	LPC_PINCON->PINSEL1 = 0x0;	 //P0.15 to P0.31 GPIO enable lines

	LPC_GPIO0->FIODIR |= 0x00078FF0;	//P0.4 to P0.11 and P0.15 P0.16 to P0.18 output
	//LPC_GPIO1->FIODIR |= 0x00000007;	
	 
while(1)
	{
		//while(tmr0_flg == 0x00);
		//tmr0_flg = 0x00;

		dig_count +=0x01;  
		if(dig_count == 0x05)
            dig_count = 0x00;		//keeps trackofsegementused

		if(one_sec_flg == 0xFF)
		{
 			one_sec_flg = 0x00;
			dig1 -=0x01;
              
			if(dig1 < 0x00)
			{ 
				dig1 = 0x09;
				dig2 -=0x01;

				if(dig2 < 0x00)
				{
					dig2 = 0x09;
					dig3 -=0x01;

					if(dig3 < 0x00)
					{
						dig3 = 0x09;
						dig4 -= 0x01;
                             
						if(dig4 < 0x00)
						{
							dig4 = 0x09;
						} //end of dig4
					
					} //end of dig3
				
				} //end of dig2

			}  //end of dig1

		}   //end of one_sec if

 		Display();	
		
	}
}
void Display(void)      //To Display on 7-segments
 {

  LPC_GPIO0->FIOMASK= masknum;
	if(dig_count == 0x01)		// For Segment U8
	{
		temp1 = dig1; 
		LPC_GPIO0->FIOPIN = FIRST_SEG;    }

	else if(dig_count == 0x02)	// For Segment U9
	{
		temp1 = dig2;             
		LPC_GPIO0->FIOPIN = SECOND_SEG;    	}

	else if(dig_count == 0x03)	// For Segment U10
	{
		temp1 = dig3;           
		LPC_GPIO0->FIOPIN = THIRD_SEG;    
	}
	else if(dig_count == 0x04)	// For Segment U11
	{ 
		temp1 = dig4;   
		LPC_GPIO0->FIOPIN = FOURTH_SEG;    

	}
	temp1 &= 0x0F;
	temp2 = array_dec[temp1];	// Decoding to 7-segment
	temp2 = temp2 << 4;
	LPC_GPIO0->FIOMASK= maskdecoder;
	LPC_GPIO0->FIOPIN = temp2;		// Taking Data Lines for 7-Seg
	for(i=0;i<500;i++);
	LPC_GPIO0->FIOCLR = 0x00000FF0;
/*	LPC_GPIO1->FIOPIN = DISABLE_ALL; //disable all the segments */
	one_sec_flg++;
 }		

