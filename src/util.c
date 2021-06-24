#include <stdio.h>

void print_usage() {
    fprintf(stderr,
            " usage:\n"
            "    ./fansi [-p] [-f filename] [-s filename] \n"
            "       -f:            print ANSI file to terminal \n"
            "       -s:            print SAUCE of specified file\n"
            "       -p:            print codepage 437 as UTF-8 characters\n"
            "       -h:            print usage information e\n"
            "\n");
}
