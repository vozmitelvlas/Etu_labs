#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define DEF_FILENAME "testFile.txt"

int main(int argc, char** argv) {
	char fileName[30];
	if(argc < 2) {
		printf("Using default file name '%s'\n",DEF_FILENAME);
		strcpy(fileName,DEF_FILENAME);
	} else
		strcpy(fileName,argv[1]);
	// creatin two channels
	int res = mknod("channel1",S_IFIFO | 0666,0);
	if(res) {
		printf("Can't create first channel\n");
		exit(1);
	}
	res = mknod("channel2",S_IFIFO | 0666,0);
	if(res) {
		printf("Can't create second channel\n");
		exit(1);
	}
	// opens first write channel
	int chan1 = open("channel1",O_WRONLY);
	if(chan1 == -1) {
		printf("Can't open channel for writing\n");
		exit(0);
	}
	// opens second read channel
	int chan2 = open("channel2",O_RDONLY);
	if(chan2 == -1) {
		printf("Can't open channe2 for reading\n");
		exit(0);
	}
	// sends file to the first channel
	write(chan1,fileName,strlen(fileName));
	// reads files content from second channel
	char buf [100];
	for(;;) {
		bzero(buf,100);
		res = read(chan2,buf,100);
		if(res <= 0)
			break;
		printf("Part of file: %s\n", buf);
	}
	close(chan1);
	close(chan2);
	unlink("channel1");
	unlink("channel2");
	return 0;
}
