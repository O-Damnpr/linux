#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[1]){
	if(symlink (argv[1], argv[2])) printf("soft-link failed\n");
}
