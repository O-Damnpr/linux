#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[1]){
	if(link (argv[1], argv[2])) printf("hard-link failed\n");
}
