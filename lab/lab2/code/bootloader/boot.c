#include "boot.h"

#define SECTSIZE 512





void bootMain(void) 
{
	// TODO: 填写kMainEntry、phoff、offset...... 然后加载Kernel（可以参考NEMU的某次lab）
	ELFHeader *elf;
	ProgramHeader * ph,*eph;
	//int i;
	//unsigned int dest ;
	unsigned int buf = 0x300000;
	elf  = (ELFHeader *)buf;
	void (*kMainEntry)(void);
	
		for ( int i = 0; i < 200; i++) 
		{
			readSect((void*)(buf + i*512), 1+i);
		}
		kMainEntry = (void*)(elf->entry);
		ph =(ProgramHeader * ) (buf + elf->phoff);
		eph = ph + elf->phnum;
		for(;ph < eph; ph++)
	{
		if (ph->type == 1)
		{
			unsigned int p = ph->vaddr, q = ph->off;
			while (p < ph->vaddr + ph->filesz) 
			{
				*(unsigned char*)p = *(unsigned char*)(buf + q);
				q++;
				p++;
			}
			while (p < ph->vaddr + ph->memsz) 
			{
				*(unsigned char*)p = 0;
				q++;
				p++;
			}
		}
	}
	kMainEntry();
}

void waitDisk(void) { // waiting for disk
	while((inByte(0x1F7) & 0xC0) != 0x40);
}

void readSect(void *dst, int offset) { // reading a sector of disk
	int i;
	waitDisk();
	outByte(0x1F2, 1);
	outByte(0x1F3, offset);
	outByte(0x1F4, offset >> 8);
	outByte(0x1F5, offset >> 16);
	outByte(0x1F6, (offset >> 24) | 0xE0);
	outByte(0x1F7, 0x20);

	waitDisk();
	for (i = 0; i < SECTSIZE / 4; i ++) {
		((int *)dst)[i] = inLong(0x1F0);
	}
}
