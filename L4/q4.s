	AREA RESET ,  DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =NUM1
	LDR R0, [R0]
	MOV R7, #8
	MOV R8, #0
	MOV R6, #1
	MOV R10, #0X0F
	MOV R11, #0X0A
UP	CMP R7, #0
	BEQ DONE
	AND R1, R0, R10
	ROR R0, #4
	MUL R1, R6
	ADD R8, R1
	SUB R7, #1
	MUL R6, R11
	B UP
DONE	LDR R0, =HEX
	STR R8, [R0]
STOP B STOP
		
NUM1 DCD 0X2255841

	AREA mydata, DATA, READWRITE
HEX DCD 0

	END 