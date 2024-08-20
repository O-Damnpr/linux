#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
		if (access(argv[1], R_OK) == -1){
			fprintf( stderr, "유저가 이 파일을 읽을 수 없습니다 %s \n", argv[1]);
			exit(1);
		}
		printf("%s is readable , proceding \n", argv[1]);
}
