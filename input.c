
// Created by dawids21 on 5/3/21.
//

#include <stdio.h>
#include <string.h>
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
