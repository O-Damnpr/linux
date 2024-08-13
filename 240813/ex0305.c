#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int filedes;
	off_t newpos;
	
	if((filedes = open("data.txt", O_RDONLY)) == -1){
		printf("file open error!\n");
		exit(1);
	}

	newpos = lseek(filedes, (off_t)0, SEEK_END);

	printf("file size : %lld\n", newpos);
}
