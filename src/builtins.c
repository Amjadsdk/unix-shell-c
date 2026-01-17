#include "builtins.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

BuiltinResult try_builtin(const Command *cmd) {
    if (cmd->argc == 0) return BUILTIN_RAN;

    if (strcmp(cmd->argv[0], "exit") == 0) {
        return BUILTIN_EXIT;
    }

    if (strcmp(cmd->argv[0], "pwd") == 0) {
        char buf[4096];
        if (getcwd(buf, sizeof(buf))) printf("%s\n", buf);
        else perror("pwd");
        return BUILTIN_RAN;
    }

    if (strcmp(cmd->argv[0], "cd") == 0) {
        const char *path = (cmd->argc >= 2) ? cmd->argv[1] : getenv("HOME");
        if (!path) path = ".";
        if (chdir(path) != 0) perror("cd");
        return BUILTIN_RAN;
    }

    return BUILTIN_NONE;
}
