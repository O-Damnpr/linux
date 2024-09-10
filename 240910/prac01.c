#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int x;
	int y;
	scanf("%d %d", &x, &y);

	int su = x;

	pid_t pid;
	int status;

	pid = fork();

	if(pid>0) {
		for(int i = 1; i < y; i++){
			su*=x;
		}
		printf("parent : %d\n", su);
		wait(&status);
		printf("합:%d\n", (status>>8)+su);
	}
	else if(pid == 0){
		sleep(1);
		int chsu = 0;
		for (int i = x; i <=y; i++){
			chsu += i;
		}
		printf("child : %d\n", chsu);
		exit(chsu);
	}
	else printf("fail to fork\n");

	printf("bye!\n");
}
