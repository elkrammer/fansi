#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cp437.h"
#include "parser.h"
#include "sauce.h"
#include "util.h"

int main(int argc, char *argv[]) {
    // set locale and check for UTF-8 support
    char *locale;
    locale = setlocale(LC_ALL, "");

    if(strstr(locale, "UTF8") == NULL && strstr (locale, "UTF-8") == NULL) {
        printf("Your terminal doesn't support UTF-8.");
        return 1;
    }

    if (argc < 2) {
        print_usage();
        exit(0);
    }

    int opt;
    while ((opt = getopt(argc, argv, "pf:s:h")) != -1) {
        switch (opt) {
            case 'p':
                print_cp437();
                break;
            case 'f':
                draw_ansi_art(optarg);
                break;
            case 's':
                print_sauce_info(optarg);
                break;
            case 'h':
                print_usage();
                exit(0);
                break;
            case '?':
                print_usage();
                exit(1);
                break;
        }
    }

    return 0;
}
