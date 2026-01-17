#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "builtins.h"
#include "exec.h"

static void trim_newline(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}

int main(void) {
    char *line = NULL;
    size_t cap = 0;

    while (1) {
        printf("tinysh> ");
        fflush(stdout);

        ssize_t nread = getline(&line, &cap, stdin);
        if (nread == -1) {
            printf("\n");
            break; // EOF (Ctrl-D)
        }

        trim_newline(line);
        if (line[0] == '\0') continue;

        Command cmd = (Command){0};
        if (!parse_line(line, &cmd)) {
            fprintf(stderr, "parse error\n");
            free_command(&cmd);
            continue;
        }

        BuiltinResult br = try_builtin(&cmd);
        if (br == BUILTIN_EXIT) {
            free_command(&cmd);
            break;
        } else if (br == BUILTIN_RAN) {
            free_command(&cmd);
            continue;
        }

        run_external(&cmd);
        free_command(&cmd);
    }

    free(line);
    return 0;
}
