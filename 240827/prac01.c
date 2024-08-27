#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    	int num;

    printf("입력 : ");
    if (scanf("%d", &num) != 1) {
        printf("유효한 숫자를 입력하세요.\n");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("그거 그렇게 하는 거 아닌데");
        exit(1);
    }

    if (pid > 0) {
        int sum = 0;
        for (int i = 1; i <= num; i++) {
            sum += i;
        }
        printf("부모: %d\n", sum);
    } else {
        int mul = 1;
        for (int j = 1; j <= num; j++) {
            mul *= j;
        }
        printf("자식:  %d\n", mul);
    }

    return 0;
}

