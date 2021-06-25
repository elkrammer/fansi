#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "version.h"

void print_logo() {
    char *logo =
        "   ·▄▄▄ ▄▄▄·  ▐ ▄ .▄▄ · ▪  \n"
        "   ▐▄▄·▐█ ▀█ •█▌▐█▐█ ▀. ██ \n"
        "   ██▪ ▄█▀▀█ ▐█▐▐▌▄▀▀▀█▄▐█·\n"
        "   ██▌.▐█ ▪▐▌██▐█▌▐█▄▪▐█▐█▌\n"
        "   ▀▀▀  ▀  ▀ ▀▀ █▪ ▀▀▀▀ ▀▀▀\n";

    const char *logo_color = "\033[38;5;162m";
    const char *white = "\033[0;37m";
    fprintf(stderr, "%s%s", logo_color, logo);
    fprintf(stderr, "%s\t      Version %s\n\n", white, VERSION);
    fprintf(stderr, "\033[0m"); // reset terminal
}

void print_usage() {
    print_logo();
    fprintf(stderr,
            " usage:\n"
            "    ./fansi [-p] [-f filename] [-s filename] \n"
            "       -f:            print ANSI file to terminal\n"
            "       -s:            print SAUCE of specified file\n"
            "       -p:            print codepage 437 as UTF-8 characters\n"
            "       -h:            print usage information\n");
}
