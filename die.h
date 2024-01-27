
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define die(msg) die_(msg, __func__, __LINE__)
static int die_(const char* msg, const char* function, int line)
{
    fprintf(stderr, msg);
    if (errno) {
        perror(" ");
    }
    fprintf(stderr, "line:     %d\n", line);
    fprintf(stderr, "function: %s\n", function);
    fprintf(stderr, "errno:    %d\n", errno);
    exit(EXIT_FAILURE);
}
