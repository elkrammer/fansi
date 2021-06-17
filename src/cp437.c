#include <stdio.h>
#include <locale.h>

#include "cp437.h"

void print_cp437() {
    setlocale(LC_ALL, "en_US.utf8");
    unsigned int y = 0;
    for (int x = 0; x < 256; x++) {
        fputwc(cp437[x], stdout);
        y++;
        if (y == 32) {
            fputwc(L'\x0A', stdout);
            y = 0;
        }
    }
}
