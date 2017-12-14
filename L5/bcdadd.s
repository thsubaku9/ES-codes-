	AREA RESET,DATA,READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10000000 ;STACK PTR VAL WHEN STK IS EMPTY
	DCD Reset_Handler
	
	AREA mycode,CODE,READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	ldr r1,=num1
	ldr r2,=num2
	mov r7,#5
	mov r6,#0
	ldr r8,=res
	
back
	ldrb r3,[r1],#1
	ldrb r4,[r2],#1
	mov r9,r3
	mov r10,r4
	and r9,#0x0f7
	and r10,#0x0f
	add r9,r10
	add r9,r6
	cmp r9,#0x0a
	subhs r9,#0x0a
	addhs r6,#1
	lsr r3,#4
	add r3,r4
	add r3,r6
	cmp r3,#0x0a
	subhs r3,#0x0a
	movhs r6,#1
	movlo r6,#0
	lsl r3,#4
	orr r3,r9
	str r3,[r8],#1
	sub r7,#1
	teq r7,#0
	bne back


stop b stop

num1 dcd 0x90000009
num2 dcd 0x99876541
	AREA mydata, DATA, READWRITE
res dcd 0,0

end