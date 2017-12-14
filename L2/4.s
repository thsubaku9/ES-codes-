	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler

Reset_Handler
	MOV R3,#10
	LDR R0,=N1+4*(ln-1)
	LDR R1,=N2+4*(ln-1)
	LDR R2,=SUM+4*(ln-1)
	
BK  LDR R4,[R0],#-4
	LDR R5,[R1],#4
	
	ADCS R6,R4,R5
	
	STR R6,[R2],#4
	SUB R3,#1
	TEQ R3,#0
	BNE BK
KB B KB

ln equ 10
	AREA dif,DATA,READWRITE
SUM DCD 0,0,0,0,0,0,0,0,0,0
N1 DCD 0,0,0,0,0,0,0,0,0,0
N2 DCD 0,0,0,0,0,0,0,0,0,0
	END