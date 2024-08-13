#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	int filedes;
	//char pathname1[] = 

	if ((filedes = open("/Users/nk/linux/240813/temp0.txt", O_EXCL | O_CREAT | O_RDWR,0644)) == -1) {
		printf("file open error!\n");
		exit(1);
	}
	close(filedes);
}
