#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){
	char *args[] = {argv[1], argv[2], argv[3], NULL};
        execv("/usr/bin/head",  args);
}
