data segment
abc dd 12345678H
def dd 12345678H
ghi dq ?
data ends
 
code segment
assume cs:code, ds:data
start:
mov ax, data
mov ds, ax
mov ax, word ptr abc
mul word ptr def
mov word ptr ghi, ax
mov cx, dx
mov ax, word ptr abc+2
mul word ptr def
add cx, ax
mov bx, dx
jnc move
add bx,0001H
 
move: mov ax,word ptr abc
mul word ptr def+2
add cx, ax
mov word ptr ghi+2, cx
mov cx,dx
 
jnc ma
add bx, 0001H
ma: mov ax, word ptr abc+2
mul word ptr def+2
add cx, ax
 
jnc mb
add dx, 0001H
mb: add cx, bx
mov word ptr ghi+4, cx
 
jnc mc
add dx, 0001H
mc: mov word ptr ghi+6, dx
int 3
code ends
end start
