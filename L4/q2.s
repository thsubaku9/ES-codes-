	AREA RESET ,  DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R0, =ASCII
	LDR R6, [R0]
	MOV R1, #4
	MOV R3, #0
UP	MOV R2, #0
	CMP R1, #0
	BEQ EXIT
	LSL R3, #4
	AND R2, R6, #0XFF
	CMP R2, #0X40
	SUBLO R2, #0X30
	SUBHI R2, #0X37
	ORR R3, R2
	ROR R6, #8
	SUB R1, #1
	B UP
EXIT	LDR R0 ,=HEX
	STR R3, [R0]
STOP	B STOP

ASCII DCD 0x3939
	AREA mydata, DATA, READWRITE
HEX DCD 0
	END