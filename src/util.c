#include "parser.h"
#include "util.h"
#include "version.h"

static int ansi_art_found(const struct dirent *dir) {
    if (!dir)
        return 0;

    if (dir->d_type == DT_REG) { // deal only with regular files
        const char *ext = strrchr(dir->d_name, '.');
        if ((!ext) || (ext == dir->d_name))
            return 0;
        else {
            if (strcmp(ext, ".ans") == 0 || strcmp(ext, ".ANS") == 0)
                return 1;
        }
    }
    return 0;
}

void screensaver_mode(const char *directory, const int speed) {
    struct dirent **namelist;
    int n;
    n = scandir(directory, &namelist, ansi_art_found, alphasort);
    if (n < 0) {
        fprintf(stderr, "No ANSI Art files found in directory %s\n", directory);
        exit(1);
    }

    srand(time(NULL));

    while (1) {
        char file[256];
        unsigned int i = rand() % n;
        snprintf(file, sizeof(file), "%s/%s", directory, namelist[i]->d_name);
        draw_ansi_art(file, speed);
        usleep(1500000);
    }

    free(namelist);
}

void print_usage() {
    print_logo();
    fprintf(stderr,
            "Usage: fansi [options] filename\n\n"
            "Options:\n"
            "       --speed  value      Set rendering speed. Default speed is 110 - increase it to slow down the output\n"
            "  -s   --ssaver dirname    Screen Saver mode\n"
            "       --sauce  filename   Print SAUCE metadata for file\n"
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

// checks if a char array contains only digits
int isArrayNumeric(const char *str) {
  unsigned int i;
  for(i = 0; i < strlen(str); i++) {
    if(!isdigit(str[i]))
      return 1;
  }
  return 0;
}
