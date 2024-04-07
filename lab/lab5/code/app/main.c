#include "types.h"
#include "utils.h"
#include "lib.h"

union DirEntry {
	uint8_t byte[128];
	struct {
		uint32_t inode;
		char name[64];
	};
};

typedef union DirEntry DirEntry;


int ls(char *destFilePath) {
	printf("ls %s\n", destFilePath);
	//int i = 0;
	int fd = 0;
	int ret = 0;
	DirEntry *dirEntry = 0;
	uint8_t buffer[512 * 2];
	fd = open(destFilePath, O_READ | O_DIRECTORY);
	if (fd == -1)
	{
		printf("open fail");
		return -1;
	}
	ret = read(fd, buffer, 512 * 2);
	//if (ret == 0)printf("no file\n");
	while (ret != 0) 
	{
	// TODO: ls
	// Hint: 使用 DIrEntry
	
		dirEntry = (DirEntry*)buffer;
		for( int i = 0; i < sizeof(buffer)/sizeof(DirEntry); i++ )
		{
			if(dirEntry[i].inode == 0)continue;
			else
				printf("%s ",dirEntry[i].name);
		}
		ret = read(fd, buffer, 512 * 2);
	}
	//sleep(10000);
	printf("\n");
	close(fd);
	return 0;
}

int cat(char *destFilePath) {
	printf("cat %s\n", destFilePath);
	int fd = 0;
	int ret = 0;
	uint8_t buffer[512 * 2];
	fd = open(destFilePath, O_READ);
	if (fd == -1)
	{
		printf("open fail\n");
		return -1;
	}
	
	ret = read(fd, buffer, 512 * 2);
	if (ret == 0)
	{
		printf("read fail\n");
		return -1;
	}
	while (ret != 0) {
		// TODO: cat
		//把内容读到buffer，输出...
		write(STD_OUT,buffer,ret);
		ret = read(fd, buffer, 512 * 2);

	}
	close(fd);
	return 0;
}

int uEntry(void) {
	int fd = 0;
	int i = 0;
	char tmp = 0;
	
	ls("/");
	ls("/boot/");
	ls("/dev/");
	ls("/usr/");

	printf("create /usr/test and write alphabets to it\n");
	fd = open("/usr/test", O_WRITE | O_READ | O_CREATE);
	for (i = 0; i < 26; i ++) {
		tmp = (char)(i % 26 + 'A');
		write(fd, (uint8_t*)&tmp, 1);
	}
	//sleep(500);
	close(fd);
	ls("/usr/");
	//printf("99");
	//sleep(500);
	cat("/usr/test");
	//sleep(500);
	
	printf("\n");
	printf("rm /usr/test\n");
	
	remove("/usr/test");
	//sleep(500);
	ls("/usr/");
	printf("rmdir /usr/\n");
	//sleep(200);
	remove("/usr");
	ls("/");
	printf("create /usr/\n");
	fd = open("/usr/", O_CREATE | O_DIRECTORY);
	//sleep(1000);
	close(fd);
	//sleep(200);
	ls("/");
	//printf("ss\n");
	
	exit();
	return 0;
}
