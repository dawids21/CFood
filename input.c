
// Created by dawids21 on 5/3/21.
//

#include <stdio.h>
#include "input.h"

void input_char(char *dest) {
    char input[3];
    do {
        fgets(input, 3, stdin);
    } while (input[0] == '\n');

    *dest = input[0];
}

