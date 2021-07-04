#include <assert.h>
#include <getopt.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
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
        fprintf(stderr, "Your terminal doesn't support UTF-8.");
        return 1;
    }

    // check terminal size
    // https://man7.org/linux/man-pages/man4/tty_ioctl.4.html
    struct winsize term_size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &term_size);

    if (term_size.ws_col < 80) {
        fprintf(stderr, "Your terminal window is currently smaller than 80"
                " columns. Please make your terminal bigger for correct"
                " rendering of art files\n");
        return 1;
    }

    if (argc < 2) {
        print_usage();
        exit(1);
    }

    // parse cmd line options
    int opt = 0;
    while (opt != -1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"cp437",   no_argument,       NULL,    0},
            {"help",    no_argument,       NULL,  'h'},
            {"sauce",   required_argument, NULL,    0},
            {NULL,      0,                 NULL,    0}
        };

        opt = getopt_long(argc, argv, ":h", long_options, &option_index);

        switch (opt) {
            // no args
            case -1:
                break;
            // long options are being used
            case 0:
                if (strcmp(long_options[option_index].name, "sauce") == 0 && optarg) {
                    print_sauce_info(optarg);
                } else if (strcmp(long_options[option_index].name, "cp437") == 0) {
                    print_cp437();
                }
                break;
            case 'h':
                print_usage();
                exit(0);
                break;
            case '?':
                print_usage();
                exit(1);
                break;
            case ':':
                fprintf(stderr, "Missing option for %c\n", optopt);
                break;
            default:
                print_usage();
                exit(1);
                break;
        }
    }

    // only one argument provided, try to render ansi art for that file
    if ((argc == 2) && (optind == 1)) {
        draw_ansi_art(argv[optind]);
        exit(0);
    }

    return 0;
}
