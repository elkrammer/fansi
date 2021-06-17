#include <stdio.h>

void print_cp437();
void load_ansi_file(const char *filename);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // print code page 437 table
        print_cp437();
    } else if (argc == 2) {
        // load ansi file
        load_ansi_file(argv[1]);
    } else {
        printf("Command error. Usage: ./fansi FILE");
    }
    return 0;
}
