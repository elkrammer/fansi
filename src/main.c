#include <stdio.h>

void print_cp437();
char *load_ansi_file(const char *filename);
void draw_ansi_art(const char *art);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // print code page 437 table
        print_cp437();
    } else if (argc == 2) {
        // load ansi file
        char *file = load_ansi_file(argv[1]);
        draw_ansi_art(file);
    } else {
        printf("Command error. Usage: ./fansi FILE");
    }
    return 0;
}
