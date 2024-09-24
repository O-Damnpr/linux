#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

int main() {
	pid_t pid;
	int fd;

	if((pid = fork()) > 0) {
		sleep(1);
		exit(1);
	}

	else if(pid == 0) {
		fd = open("hyunjaesigak.txt", O_RDWR | O_CREAT, 0644);
		setsid();

		while(1) {
			time_t t = time(NULL);
			char *buf = ctime(&t);
			write(fd, buf, strlen(buf));
			sleep(10);
		}
		close(fd);
	}
}
