#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){
		if (access(argv[1], F_OK) == -1){
			fprintf( stderr, "존재하지 않는 파일입니다. %s \n", argv[1]);
			exit(1);
		}
		printf("%s은 존재합니다.\n", argv[1]);
}
