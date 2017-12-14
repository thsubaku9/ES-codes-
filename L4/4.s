	AREA RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler

		LDR R0,=BCD
		LDR R1,[R0]
		MOV R2,R1
		LSR R2,#4
		AND R1,0x0F
		MOV R3,#10
		MLA R4,R2,R3,R1
		LDR R0,=HEX
		STR R4,[R0]

STOP B STOP
		
BCD DCD 0x98
		AREA mydata,DATA,READWRITE	
HEX DCD 0
	END