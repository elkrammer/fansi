#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "util.h"
#include "version.h"

void print_usage() {
    print_logo();
    fprintf(stderr,
            "Usage: fansi [options] filename\n\n"
            "Options:\n"
            "       --sauce filename    Print SAUCE metadata for file\n"
            "       --cp437             Print Code Page 437 table as UTF-8 characters\n"
            "  -h   --help              Display this information\n");
}

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

// strips spaces from string
char *trimwhitespace(char *str) {
    char *end;

    // trim leading space
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  // all spaces?
        return str;

    // trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // add null terminator character
    end[1] = '\0';

    return str;
}
