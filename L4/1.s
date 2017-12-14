	AREA RESET, DATA, READONLY
	EXPORT __Vectors

__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler

		LDR R0,=NUM	
		LDR R3,=RESULT
		LDRB R1,[R0]
		AND R2,R1,#0x0F
		CMP R2,#09
		BLO DOWN
		ADD R2,#07

DOWN	ADD R2,#0x30
		STRB R2,[R3]
		AND R4,R1,#0xF0
		LSR R4,#04
		CMP R4,#09
		BLO DOWN1
		ADD R3,#07

DOWN1	ADD R4,#0x30
		STRB R4,[R3,#01]
		
BK	B BK		
NUM DCD 0x000003A
		AREA mydata,DATA,READWRITE	
RESULT DCD 0
	END