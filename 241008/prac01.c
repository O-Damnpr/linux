#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void int_handle(int);

int num = 0;

int main() {

	static struct sigaction act;

	act.sa_handler = int_handle;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);

	while(1) {
		printf("I'm sleepy..\n");
		sleep(1);
		if(num >= 1) exit(0);
	}
}

void int_handle(int signum) {
	int filedes;
	if((filedes = open("a.txt", O_CREAT | O_RDWR, 0644)) == -1) {
		printf("file open error!\n");
        exit(1);
    }
	char buf[] = "종료 구다사이";
	write(filedes, buf, sizeof(buf));
	close(filedes);
	num++;
}
