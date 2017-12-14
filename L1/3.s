	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY 
	EXPORT Reset_Handler
	
Reset_Handler
	MOV R0,#pi
	LDR R1,=src
	LDR R2,=src + 4*(len-1)
	
bk	LDR R3,[R2]
	LDR R4,[R1]
	STR R4,[R2]
	STR R3,[R1]
	SUB R2,R2,#4
	ADD R1,R1,#4
	TEQ R0,#0
	BNE bk
ki b ki 

len equ 6	
pi equ 3
	AREA swap,DATA,READWRITE
src DCD 0,0,0,0,0,0
	END