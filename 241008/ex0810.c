#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	putenv("APPLE=BANANA");
	printf("%s\n", getenv("APPLE"));
	execl("ex0811", "ex0811", (char *)0);
}
