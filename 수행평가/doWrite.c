#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define LOGDIR "./log"
#define LOGFILE "./log/restart.txt"

char* get_time(void) {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   time_t t = (time_t)tv.tv_sec;
   struct tm* ptm = localtime(&t);
   static char str[1024];
   sprintf(str, "%04d.%02d.%02d %02d:%02d:%02d",
           ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
           ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
   return str;
}

int main(int argc, char** argv) {
   struct timeval tv;
   gettimeofday(&tv, NULL);
   
   // time을 이용해 더 확실한 랜덤값 생성
   time_t t;
   srand((unsigned) time(&t) + tv.tv_usec + getpid());
   int action = rand() % 3;  // 0, 1, 2
   
   sleep(1);
   
   switch(action) {
       case 0:
           raise(SIGKILL);  // Signal(9, Killed)
           break;
       case 1:
           exit(5);         // Exit(5)
           break;
       case 2:
           raise(SIGTERM);  // Signal(15, Terminated)
           break;
   }
   
   return 0;
}
