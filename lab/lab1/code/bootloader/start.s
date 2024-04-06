# start.s

/* Start Protected Mode */
.code16

.global start
start:
	# 关闭中断
	cli 
	
	# 开启A20地址线
	pushw %ax
	movb $0x2,%al
	outb %al,$0x92
	popw %ax
	
	# 加载GDTR
	data32 addr32 lgdt gdtDesc 

	# TODO: 把cr0的最低位设置为1

	movl %cr0, %eax                 
	orb $0x01, %al
	movl %eax, %cr0

	# 长跳转切换到保护模式
	data32 ljmp $0x08, $start32 

.code32
start32:
	movw $0x10, %ax # setting data segment selector
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %ss
	movw $0x18, %ax # setting graphics data segment selector
	movw %ax, %gs
	movl $0x8000, %eax # setting esp
	movl %eax, %esp
	jmp bootMain
	# TODO：编写输出函数，输出"Hello World" （Hint:参考app.s！！！）



.p2align 2
gdt:
	.word 0,0                       #GDT第一个表项必须为空
	.byte 0,0,0,0

	.word 0xffff,0                  #代码段描述符
	.byte 0,0x9a,0xcf,0

	.word 0xffff,0                  #数据段描述符
	.byte 0,0x92,0xcf,0

	.word 0xffff,0x8000             #视频段描述符
	.byte 0x0b,0x92,0xcf,0

gdtDesc:
	.word (gdtDesc - gdt -1)
	.long gdt


