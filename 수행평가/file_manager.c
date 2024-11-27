// file_manager.c
#include "main.h"

void make_log_dir(void) {
    mode_t old_mask = umask(0);
    if (mkdir(LOGDIR, 0755) < 0 && errno != EEXIST) {
        perror("Failed to create log directory");
        exit(1);
    }
    umask(old_mask);

    if (access(LOGDIR, W_OK) != 0) {
        perror("Log directory not writable");
        exit(1);
    }

    if (chmod(LOGDIR, 0755) < 0) {
        perror("Failed to set directory permissions");
        exit(1);
    }

    if (access(LOGFILE, F_OK) == 0) {
        if (link(LOGFILE, BACKUP_FILE) < 0) {
            perror("Failed to create backup");
            exit(1);
        }
        unlink(LOGFILE);
    }
}

void PrintInfo() {
   int fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
   if (fd < 0) {
       perror("Failed to open log file");
       return;
   }

   char buffer[4096];
   static bool header_printed = false;
   
   if (!header_printed) {
       sprintf(buffer, 
           "S/W Block Name    Restart\t\tStart Time\t\tReason\n"
           "                  Count\n"
           "------------------------------------------------------------\n");
       if (write(fd, buffer, strlen(buffer)) < 0) {
           perror("Write failed");
           close(fd);
           return;
       }
       printf("%s", buffer);

       for (int i = 0; i < manager.processCount; i++) {
           sprintf(buffer, "%-16s\t%-14d\t%-20s\t%s\n",
                   manager.processes[i].swBlock.sw_argv[0],
                   manager.processes[i].restartCount,
                   manager.processes[i].startTime,
                   manager.processes[i].reason);
           
           if (write(fd, buffer, strlen(buffer)) < 0) {
               perror("Write failed");
               close(fd);
               return;
           }
           printf("%s", buffer);
       }
       header_printed = true;
   } else if (last_updated_index != -1) {
       if (lseek(fd, 0, SEEK_END) < 0) {
           perror("Lseek failed");
           close(fd);
           return;
       }

       sprintf(buffer, "%-16s\t%-14d\t%-20s\t%s\n",
               manager.processes[last_updated_index].swBlock.sw_argv[0],
               manager.processes[last_updated_index].restartCount,
               manager.processes[last_updated_index].startTime,
               manager.processes[last_updated_index].reason);
       
       if (write(fd, buffer, strlen(buffer)) < 0) {
           perror("Write failed");
           close(fd);
           return;
       }
       printf("%s", buffer);
   }
   close(fd);
}
