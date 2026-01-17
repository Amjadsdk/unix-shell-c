#include "exec.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int run_external(const Command *cmd) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        execvp(cmd->argv[0], cmd->argv);
        perror("execvp");
        _exit(127);
    }

    if (cmd->background) {
        printf("[bg] pid=%d\n", pid);
        return 0;
    }

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return -1;
    }
    return status;
}
