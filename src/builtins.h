#pragma once
#include "parse.h"

typedef enum {
    BUILTIN_NONE = 0,
    BUILTIN_RAN,
    BUILTIN_EXIT
} BuiltinResult;

BuiltinResult try_builtin(const Command *cmd);
