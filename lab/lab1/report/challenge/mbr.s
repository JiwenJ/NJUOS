[org 0x7c00] ;start at 0x7c00
	mov ax, cs		
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov ax, 0x7d00
	mov sp, ax
	push 13
	push message
	call displayStr

loop:
	jmp loop


displayStr:
	push bp
	mov ax, [esp+4]
	mov bp, ax
	mov cx, [esp+6]
	mov ax, 0x1301
	mov bx, 0x000c
	mov dx, 0x0000
	int 0x10
	pop bp
	ret

message db 'hello world',0ah,0dh
times 510-($-$$) db 0 ;to fill the vacant volume 
db 0x55,0xaa
