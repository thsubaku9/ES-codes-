	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler

Reset_Handler
	LDR R0,=N1+4*(LN-1)
	LDR R1,=N2+4*(LN-1)
	LDR R9,=RES+4*(LN-1)
	MOV R8,#LN
	
BK	LDR R2,[R0],#-4
	LDR R3,[R1],#-4
	
	SBCS R4,R2,R3
	STR R4,[R9],#-4
	SUB R8,#1
	TEQ R8,#0
	BNE BK	
EM	B EM	

LN EQU 4
	AREA ML,DATA,READWRITE
N1 DCD 0,0,0,0
N2 DCD 0,0,0,0
RES DCD 0,0,0,0
	END