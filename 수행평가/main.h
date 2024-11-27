// main.h
#ifndef __MAIN_H__
#define __MAIN_H__

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_STR 255
#define PROCESS_NUMBER 10
#define MAX_ARGUEMENT_NUMBER 3
#define LOGDIR "./log"
#define LOGFILE "./log/restart.txt"
#define BACKUP_FILE "./log/restart.txt.backup"

typedef struct _SWBlock {
  char sw_argv[MAX_ARGUEMENT_NUMBER + 2][MAX_STR];    
  int num_of_argv;
} SWBlock;

typedef struct _PInfo {
  SWBlock swBlock;    
  pid_t processId;    
  int restartCount;   
  char startTime[MAX_STR];
  char reason[MAX_STR];
} PInfo;

typedef struct _PData {
  bool runningStatus; 
  int processCount;   
  PInfo processes[PROCESS_NUMBER]; 
} PData;

extern PData manager;
extern pid_t deadProcessId;
extern int exit_status;
extern int last_updated_index;

void InitProcessManager(void);
void StartProcesses(void);
void SignalHandler(int signo);
void INTHandler(int signo);
void ReInit(pid_t deadPid, int status);
int FindIndex(pid_t deadPid);
void ReStart(int targetIndex);
void make_log_dir(void);
void PrintInfo(void);
char* get_time(void);

#endif
