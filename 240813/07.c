#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fdin;
    ssize_t nread;
    char buffer[1024];
    int alphCount = 0;

    if ((fdin = open(argv[1], O_RDWR)) == -1) {
        printf("file open error!\n");
        exit(1);
    }

    while ((nread = read(fdin, buffer, sizeof(buffer))) > 0) {
        buffer[nread] = '\0';	    
	for (ssize_t i = 0; i < nread; i++) {
		buffer[i] = toupper((unsigned char)buffer[i]);
            if (isalpha(buffer[i])) {
                alphCount++;
            }
        }
	printf("%s\n", buffer);

	lseek(fdin, 0, SEEK_SET);
	write(fdin, buffer, nread);
    }

    close(fdin);

    printf("싹파벳 개수: %d\n", alphCount);

    return 0;
}

