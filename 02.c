#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	DIR *dirp;
	struct dirent *dentry;
	int dircnt=0;
	int filecnt=0;

	if((dirp = opendir(argv[1])) == NULL)
		exit(1);


	while(dentry = readdir(dirp)){
		if(dentry ->d_ino != 0){ 
		       	printf("%s\n", dentry->d_name);
			dircnt++;
		} else {
			filecnt++;
		}
	}

	printf("파일 개수 %d, 디렉토리 개수 %d", dircnt, filecnt);

	closedir(dirp);
}
