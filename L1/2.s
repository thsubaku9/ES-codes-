	AREA RESET,DATA,READONLY
	EXPORT 	__Vectors
__Vectors
	DCD 0X10001000 
	DCD Reset_Handler

	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler
	
Reset_Handler
	LDR R0,=SRC +(len-1)*4
	LDR R1,=SRC +4*(2*len-lap-1)
	MOV R2,#10
	
bk  LDR R3,[R0],#-4
	STR R3,[R1],#-4
	SUB R2,R2,#1
	TEQ R2,#0
	BNE bk

kb B kb
	
lap equ 7
len equ 10
	AREA OVERLAP,DATA,READWRITE 
SRC DCD 0,0,0,0,0,0,0,0,0,0,0,0,0
	END	