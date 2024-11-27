// main.c
#include "main.h"

PData manager;
pid_t deadProcessId;
int exit_status;
int last_updated_index = -1;

void INTHandler(int signo) {
    printf("\nCleaning up and exiting...\n");
    remove(LOGFILE);
    unlink("./current_log");
    exit(0);
}

int main() {
    signal(SIGCHLD, SignalHandler);
    signal(SIGINT, INTHandler);
    
    make_log_dir();
    InitProcessManager();
    StartProcesses();
    
    while(1) {
        if(!manager.runningStatus) {
            ReInit(deadProcessId, exit_status);
            manager.runningStatus = true;
        }
        sleep(1);
    }
    return 0;
}
