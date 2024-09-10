#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	int status;

	pid = fork();

	if(pid>0) {
		printf("부모 죽는중 ..\n");
	}

	else if(pid == 0){
		sleep(100);
		printf("child : 구에엑 나는 좀비다!i\n");
	}

	printf("bye!\n");
}
