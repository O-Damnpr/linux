#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void parent_handle(int);

int main() {
    pid_t pid;
    struct sigaction act;
    act.sa_handler = parent_handle;
    sigfillset(&(act.sa_mask));
    sigaction(SIGCHLD, &act, NULL);

    pid = fork();

    if(pid == 0) {
	    printf("나는 자식\n");
	    kill(getppid(), SIGCHLD);
	   printf("안녕엄마\n" );
    }
    sleep(2);
}

void parent_handle(int signum){
	printf("signum : %d\n", signum);
	printf("부모주금\n");
}
