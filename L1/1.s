	AREA RESET,DATA,READONLY
	EXPORT 	__Vectors
__Vectors
	DCD 0X10001000 
	DCD Reset_Handler

	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler

Reset_Handler
	MOV R0,#0x0A
	LDR R1,=SRC
	LDR R2,=SRC+(len-1)*4
	
	
L1	LDR R4,[R1],#4
	STR R4,[R2],#4
	SUB R0,R0,#1
	BNE L1
	
Stop B Stop
len EQU 10

	AREA NONOVERLAP,DATA,READWRITE 
SRC DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	END