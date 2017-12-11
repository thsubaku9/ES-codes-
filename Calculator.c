#include<LPC17xx.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

//LCD 
#define RS_CTRL 0x08000000  //P0.27
#define EN_CTRL 0x10000000	//P0.28
#define DT_CTRL 0x07800000	//P0.23 to P0.26

void lcd_init(void);
void wr_cn(void);
void wr_dn(void);
void clr_disp(void);
void lcd_com(void);
void delay_lcd(unsigned long int);
void lcd_data(void);
void clear_ports(void);
void lcd_puts(unsigned char*);
int lcdStringCount=0;
void keyboardToLCD_display(char ch);
unsigned long int temp1=0,temp2=0;


//keyboard
void keyboard(void);
void scan(void);
unsigned long int temp3;
void keyboard_init(void);
int row=0,col=0,flag[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},prev_flag[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
unsigned char mappedString[100]="";
unsigned long int rowCode=0;


//Mapping kyboard keys to message
unsigned char mapkeyboard1[4][4]={
								{'1','2','3','+'},
								{'4','5','6','-'},
								{'7','8','9','q'},//q-squareroot
								{'>','0','=','C'}
								};


unsigned char mapkeyboard2[4][4]={
								{'l','i','f','*'},
								{'w','(',')','/'},//w-log base 10
								{'s','c','t','^'},
								{'>','e','=','C'}
								};
												
int shift=0;


//Expression string
char expression[100]="\0";
int endpos=0;
int expressioncount=0;
void deleteExpression(void);
void addToExpression(char ch);
float evalExpression(void);
int j=0,i=0;
float num[2]={0,0};
int sinFlag=0;
int cosFlag=0;
int tanFlag=0;
int logFlag=0;
int invFlag=0;
int factFlag=0;
int sqrtFlag=0;
int addFlag=0;
int subFlag=0;
int log10Flag=0;
int	expFlag=0;
int multiplicationFlag=0;
int divisionFlag=0;
int openBracketFlag=0;
int closeBracketFlag=0;
int powerFlag=0;
float result=0;
unsigned char resultInString[100]="\0";
//void evalExpressionUsingStack();
void selection(int row,int col);


//Utility Function
#define expo 2.718

//Main
int main()
{
	SystemInit();
	SystemCoreClockUpdate();

	lcd_init();
	keyboard_init();
	
	while(1)
	{
		keyboard();
		delay_lcd(10000);	
	}
	
}




void deleteExpression()
{
	expression[0]='\0';
	endpos=0;
	return;
}

void addToExpression(char ch)
{
	expression[endpos++]=ch;
	keyboardToLCD_display(ch);
	return;
}

/*
void evalExpressionUsingStack()
{
	expressioncount=0;
	char* exp=expressionmapping(expression);
	exp=infixToPostfix(exp); //return required or not

	
}
*/


void analyzeExpression()
{
	
	while(expression[j]!='\0')
	{

		if(expression[j]>='0' && expression[j]<='9')
		{
			while(expression[j]>='0' && expression[j]<='9')
			{
				num[i]=num[i]*10+(expression[j]-0x30);
				j++;
			}
			i++;
			j--;
		}
		else if(expression[j]=='s')
		{
			sinFlag=1;
		}
		else if(expression[j]=='c')
		{
			cosFlag=1;
		}
		else if(expression[j]=='t')
		{
			tanFlag=1;
		}
		else if(expression[j]=='l')
		{
			logFlag=1;
		}
		else if(expression[j]=='i')
		{
			invFlag=1;
		}
		else if(expression[j]=='f')
		{
			factFlag=1;
		}
		else if(expression[j]=='q')
		{
			sqrtFlag=1;
		}
		else if(expression[j]=='(')
		{
			openBracketFlag++;
		}
		else if(expression[j]==')')
		{
			closeBracketFlag++;
		}
		else if(expression[j]=='w')
		{
			log10Flag=1;
		}
		else if(expression[j]=='e')
		{
			expFlag=1;
		}
		else if(expression[j]=='+')
		{
			addFlag=1;
		}
		else if(expression[j]=='-')
		{
			subFlag=1;
		}
		else if(expression[j]=='*')
		{
			multiplicationFlag=1;
		}
		else if(expression[j]=='/')
		{
			divisionFlag=1;
		}
		else if(expression[j]=='^')
		{
			powerFlag=1;
		}
		else
		{
			return;
		}

		j++;

	}
	
	return;
}


float evalExpression()
{
	j=0;
	num[0]=0;
	num[1]=0;
	i=0;
	sinFlag=0;
	cosFlag=0;
	tanFlag=0;
	logFlag=0;
	invFlag=0;
	factFlag=0;
	sqrtFlag=0;
	addFlag=0;
	subFlag=0;
	log10Flag=0;
	expFlag=0;
	multiplicationFlag=0;
	divisionFlag=0;
	openBracketFlag=0;
	closeBracketFlag=0;
	powerFlag=0;
	analyzeExpression();
	if(closeBracketFlag==openBracketFlag)
	{
		if(sinFlag)
		{
			return sin(num[0]);
		}
		else if(cosFlag)
		{
			return cos(num[0]);
		}
		else if(tanFlag)
		{
			return tan(num[0]);
		}
		else if(logFlag)
		{
			return log(num[0]);
		}
		else if(log10Flag)
		{
			return log10(num[0]);
		}
		else if(invFlag)
		{
			return  1/(num[0]);
		}
		else if(factFlag)
		{
			int fact=0;
			for(i=1;i<factFlag;i++)
			{
				fact=fact*i;
			}
			return fact;
		}

		else if(sqrtFlag)
		{
			return sqrt(num[0]);
		}
		else if(expFlag)
		{
			return pow(expo,num[0]);
		}
		else if(addFlag) 
		{
			return num[0]+num[1];
		}

		else if(subFlag)
		{
			return num[0]-num[1];
		}

		else if(multiplicationFlag)
		{
			return num[0]*num[1];
		}

		else if(divisionFlag)
		{
			return num[0]/num[1];
		}
		else if(powerFlag)
		{
			return pow(num[0],num[1]);
		}
	}
	return -9999999;
	
}

void selection(int row,int col)
{
		if(shift==0)
		{
			switch(mapkeyboard1[row][col])
			{
				case 'C':	clr_disp(); //clear and delete expression
							deleteExpression();
					break;
				case '>': 	shift=1;
					break;
				case '=': 	result=evalExpression();
							sprintf(resultInString,"%3.2f",result);
							lcd_puts(&resultInString[0]);
					break;
				default: 	addToExpression(mapkeyboard1[row][col]);
			}
		}
		else
		{
			switch(mapkeyboard2[row][col])
			{
				case 'C': 	clr_disp();			//clear and delete expression
							deleteExpression();
					break;
				case '>': 	shift=0;
					break;
				case '=': 	evalExpression();
							sprintf(resultInString,"%3.2f",result);
							lcd_puts(&resultInString[0]);
					break;
				default: 	addToExpression(mapkeyboard2[row][col]);
			}
		}
}

void keyboard(void)
{
	rowCode=0x00000400;

	for(row=0;row<4;row++)
	{
			
		LPC_GPIO2->FIOPIN=rowCode<<row;
		
		
		scan();
		if(flag[row][col]==1 && prev_flag[row][col]!=1 && col>=0)
		{
			
			selection(row,col);
			//LCD_display(row,col,shift);
			
		}
		prev_flag[row][col]=flag[row][col];
	}
}

void scan(void)
{
	 temp3= LPC_GPIO1->FIOPIN;
	 temp3&=0x07800000;
	 if(temp3 != 0x00000000)
	 {	
		 
		if(temp3 == 0x00800000)
			col=0;
		if(temp3 == 0x01000000)
			col=1;
		if(temp3 == 0x02000000)
			col=2;
		if(temp3 == 0x04000000)
			col=3;
		
		flag[row][col]=1;
	 }
	 else 
	 {
		 
		 flag[row][col]=0; 
	}
		
	return;
}


void keyboard_init(void)
{
	LPC_PINCON->PINSEL3 &= 0xFFC03FFF; //col input
	LPC_PINCON->PINSEL4 &= 0xF00FFFFF; //row output
	LPC_GPIO2->FIODIR |= 0X00003C00;	//row output
	LPC_GPIO1->FIODIR &= 0XF87FFFFF;	//col input
}
	
void lcd_init(void)
{
	LPC_PINCON->PINSEL3 &= 0xFC003FFF;
	LPC_GPIO0->FIODIR |=DT_CTRL;
	LPC_GPIO0->FIODIR |=RS_CTRL;
	LPC_GPIO0->FIODIR |=EN_CTRL;
	
	clear_ports();
	delay_lcd(3200);
	
	temp2=(0x30<<19);
	wr_cn();
	delay_lcd(30000);
	
	temp2=(0x30<<19);
	wr_cn();
	delay_lcd(30000);
	
	temp2=(0x30<<19);
	wr_cn();
	delay_lcd(30000);
	
	temp2=(0x20<<19);
	wr_cn();
	delay_lcd(30000);
	
	temp1=0x28;
	lcd_com();
	delay_lcd(30000);
	
	temp1=0x0F;
	lcd_com();
	delay_lcd(800);
	
	temp1=0x06;
	lcd_com();
	delay_lcd(800);
	
	temp1=0x01;
	lcd_com();
	delay_lcd(10000);
	
	temp1=0x80;
	lcd_com();
	delay_lcd(800);
	
		return;
	
}

void lcd_com(void)
{
temp2=temp1 & 0xf0;
temp2=temp2<<19;
wr_cn();
temp2=temp1 & 0x0f;
temp2=temp2 <<23;
wr_cn();
	delay_lcd(1000);
	return;
}

void wr_cn(void)
{clear_ports();
LPC_GPIO0->FIOPIN=temp2;	
	LPC_GPIO0->FIOCLR=RS_CTRL;
	LPC_GPIO0->FIOSET=EN_CTRL;
	delay_lcd(25);
	LPC_GPIO0->FIOCLR= EN_CTRL;
	return;
	
}

void lcd_data(void)
{temp2=temp1 & 0xf0;
temp2=temp2<<19;
	wr_dn();
	temp2=temp1 & 0x0f;
	temp2=temp2<<23;
	wr_dn();
	delay_lcd(1000);
	return;
}

void wr_dn(void)
{
	LPC_GPIO0->FIOPIN=temp2;	
	LPC_GPIO0->FIOSET=RS_CTRL;
	LPC_GPIO0->FIOSET=EN_CTRL;
	delay_lcd(25);
	LPC_GPIO0->FIOCLR= EN_CTRL;
	return;
}

void delay_lcd(unsigned long int r1)
{ unsigned long int r;
	for(r=0;r<r1;r++);
	return;
}

void clr_disp(void)
{
temp1=0x01;
lcd_com();
delay_lcd(10000)	;
return;
}

void clear_ports(void)
{LPC_GPIO0->FIOCLR=DT_CTRL;
LPC_GPIO0->FIOCLR=RS_CTRL;
LPC_GPIO0->FIOCLR=EN_CTRL;
	return;
}

void lcd_puts(unsigned char *buf1)
{
	
	while(buf1[i]!='\0')
	{
		temp1=buf1[lcdStringCount];
		lcd_data();
		if( lcdStringCount>=16)
		{
			temp1=0xC0;
			lcd_com();
			
		}
		lcdStringCount++;
	}
	return;
}	


char* stringMap(char ch)
{
	switch(ch)
	{
		case '1': return "1";
		case '2': return "2";
		case '3': return "3";
		case '4': return "4";
		case '5': return "5";
		case '6': return "6";
		case '7': return "7";
		case '8': return "8";
		case '9': return "9";
		case '0': return "0";
		case '+': return "+";
		case '-': return "-";
		case '*': return "*";
		case '/': return "/";
		case '^': return "^";
		case 's': return "sin";
		case 'c': return "cos";
		case 't': return "tan";
		case 'l': return "log";
		case 'i': return "inv";
		case 'f': return "fact";
		case 'q': return "sqrt";
		case '(': return "(";
		case ')': return ")";
		case '.': return ".";
	}
	return "";
}

void keyboardToLCD_display(char ch)
{
	strcat(mappedString,stringMap(ch));
	lcd_puts(&mappedString[0]);
	return;
}
