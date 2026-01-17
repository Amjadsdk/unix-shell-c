#pragma once
#include <stdbool.h>

typedef struct {
    char **argv;     // null-terminated
    int argc;
    bool background; // ends with &
} Command;

bool parse_line(const char *line, Command *out);
void free_command(Command *cmd);
