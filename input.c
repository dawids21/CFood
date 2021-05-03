
// Created by dawids21 on 5/3/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"

void input_char(char *dest) {
    char input[3];
    do {
        fgets(input, 3, stdin);
    } while (input[0] == '\n');

    *dest = input[0];
}

void input_string(char *dest, int limit) {
    fgets(dest, limit, stdin);

    if ((strlen(dest) > 0) && (dest[strlen(dest) - 1] == '\n')) {
        dest[strlen(dest) - 1] = '\0';
    }
}

void input_integer(int *dest) {
    char input[15];
    fgets(input, 15, stdin);

    if ((strlen(input) > 0) && (dest[strlen(input) - 1] == '\n')) {
        dest[strlen(input) - 1] = '\0';
    }

    *dest = (int) strtol(input, NULL, 10);
}