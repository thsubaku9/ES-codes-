	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	ALIGN
	DCD Reset_Handler
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=N1
	LDR R1,=N2
	LDR R0,[R0]
	LDR R1,[R1]
	MOV R2,#0;CARRY
	MOV R9,#0; COUNTER
	MOV R8,#0;RES
	
L1	MOV R11,#0X0A
	MOV R3,#0X0F
	AND R3,R0
	MOV R4,#0X0F
	AND R4,R1
	ROR R0,#4
	ROR R1,#4
	ADD R9,#1
	CMP R3,R4
	SUBHI R7,R3,R4
	SUB R7,R7,R2
	SUBLO R7,R4,R3
	SUBLO R7,R11,R7
	MOVLO R2,#1
	ORR R8,R7
	ROR R8,#4
	CMP	R9,#8
	BNE L1
	
	LDR R6,=RES
	STR R8,[R6]
BK	B BK

N1 DCD 0X4532
N2 DCD 0X3211
	AREA DATASEG,DATA,READWRITE
RES DCD 0
	END	