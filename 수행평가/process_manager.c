#include "main.h"

void SignalHandler(int signo) {
    deadProcessId = waitpid(-1, &exit_status, 0);
    if (deadProcessId != -1) {
        manager.runningStatus = false;
    }
}

void InitProcessManager() {
    manager.runningStatus = true;
    manager.processCount = 0;
    
    int fd = open("./swblock", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open swblock file");
        exit(1);
    }

    char line[MAX_STR];
    int swno = 0;
    char temp[MAX_STR];
    
    ssize_t bytes_read;
    char *pos = line;
    while ((bytes_read = read(fd, pos, 1)) > 0 && swno < PROCESS_NUMBER) {
        if (*pos == '\n') {
            *pos = '\0';
            char *ptr = line;
            int argCount = 0;
            char *token;
            
            snprintf(temp, MAX_STR, "SwBlock%d", swno + 1);
            strcpy(manager.processes[swno].swBlock.sw_argv[0], temp);
            argCount++;
            
            while ((token = strsep(&ptr, ";\n")) != NULL && argCount < MAX_ARGUEMENT_NUMBER + 1) {
                while (*token == ' ') token++;
                char *end = token + strlen(token) - 1;
                while (end > token && (*end == ' ' || *end == '\n')) end--;
                *(end + 1) = '\0';
                
                if (strlen(token) > 0) {
                    strcpy(manager.processes[swno].swBlock.sw_argv[argCount], token);
                    argCount++;
                }
            }
            
            if (argCount > 0) {
                manager.processes[swno].swBlock.num_of_argv = argCount;
                manager.processes[swno].processId = -1;
                manager.processes[swno].restartCount = 0;
                strcpy(manager.processes[swno].startTime, get_time());
                strcpy(manager.processes[swno].reason, "Init.");
                swno++;
            }
            pos = line;
        } else {
            pos++;
        }
    }
    
    if (bytes_read < 0) {
        perror("Read error");
        close(fd);
        exit(1);
    }
    
    close(fd);
    manager.processCount = swno;
}

void StartProcesses() {
    for (int i = 0; i < manager.processCount; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execl("./doWrite", 
                  manager.processes[i].swBlock.sw_argv[0],
                  manager.processes[i].swBlock.sw_argv[1],
                  manager.processes[i].swBlock.sw_argv[2],
                  manager.processes[i].swBlock.sw_argv[3],
                  NULL);
            perror("Execl failed");
            exit(1);
        } else if (pid > 0) {
            manager.processes[i].processId = pid;
            manager.processes[i].restartCount++;
        } else {
            perror("Fork failed");
            exit(1);
        }
    }
    last_updated_index = -1;
    PrintInfo();
}

void ReInit(pid_t deadPid, int status) {
    int index = FindIndex(deadPid);
    if (index == -1) return;
    
    strcpy(manager.processes[index].startTime, get_time());
    
    if (WIFSIGNALED(status)) {
        sprintf(manager.processes[index].reason, "Signal(%d, %s)", 
                WTERMSIG(status), strsignal(WTERMSIG(status)));
    } else {
        sprintf(manager.processes[index].reason, "Exit(%d)", 
                WEXITSTATUS(status));
    }
    
    last_updated_index = index;
    ReStart(index);
    PrintInfo();
}

int FindIndex(pid_t deadPid) {
    for (int i = 0; i < manager.processCount; i++) {
        if (manager.processes[i].processId == deadPid) {
            return i;
        }
    }
    return -1;
}

void ReStart(int targetIndex) {
    pid_t pid = fork();
    if (pid == 0) {
        execl("./doWrite", 
              manager.processes[targetIndex].swBlock.sw_argv[0],
              manager.processes[targetIndex].swBlock.sw_argv[1],
              manager.processes[targetIndex].swBlock.sw_argv[2],
              manager.processes[targetIndex].swBlock.sw_argv[3],
              NULL);
        perror("Execl failed");
        exit(1);
    } else if (pid > 0) {
        manager.processes[targetIndex].processId = pid;
        manager.processes[targetIndex].restartCount++;
    } else {
        perror("Fork failed");
    }
}

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
