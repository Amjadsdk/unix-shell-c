#define _GNU_SOURCE
#include "parse.h"
#include <stdlib.h>
#include <string.h>

static char *dupstr(const char *s) {
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, s, n + 1);
    return p;
}

bool parse_line(const char *line, Command *out) {
    memset(out, 0, sizeof(*out));

    char *buf = dupstr(line);
    if (!buf) return false;

    int cap = 8;
    out->argv = (char**)calloc((size_t)cap, sizeof(char*));
    if (!out->argv) { free(buf); return false; }

    char *save = NULL;
    char *tok = strtok_r(buf, " \t", &save);
    while (tok) {
        if (out->argc + 1 >= cap) {
            cap *= 2;
            char **tmp = (char**)realloc(out->argv, (size_t)cap * sizeof(char*));
            if (!tmp) { free(buf); return false; }
            out->argv = tmp;
        }
        out->argv[out->argc++] = dupstr(tok);
        tok = strtok_r(NULL, " \t", &save);
    }
    out->argv[out->argc] = NULL;

    if (out->argc > 0 && strcmp(out->argv[out->argc - 1], "&") == 0) {
        out->background = true;
        free(out->argv[out->argc - 1]);
        out->argv[out->argc - 1] = NULL;
        out->argc--;
    }

    free(buf);
    return (out->argc > 0);
}

void free_command(Command *cmd) {
    if (!cmd || !cmd->argv) return;
    for (int i = 0; i < cmd->argc; i++) free(cmd->argv[i]);
    free(cmd->argv);
    cmd->argv = NULL;
    cmd->argc = 0;
    cmd->background = false;
}
