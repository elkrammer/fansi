#include "cp437.h"
#include "parser.h"

// read ansi art file into a buffer
char *read_ansi_file(const char *filename) {
    FILE *input = fopen(filename, "r");
    if (!input) {
        fprintf(stderr, "Error: Failed to open file '%s'.\n", filename);
        exit(1);
    }

    // check if this file is actually an ANSI Art file
    char *ext = strrchr(filename, '.');
    unsigned int i = 0;
    for (i = 0; i < strlen(ext); i++)
        ext[i] = tolower(ext[i]);

    if (!ext || ext == filename || strcmp(ext, ".ans") != 0) {
        fprintf(stderr, "Error: Only ANSI Art files are supported\n");
        exit(1);
    }

    // get file size
    fseek(input, 0, SEEK_END);
    long input_size = ftell(input);

    // move cursor to the begining of file
    fseek(input, 0, SEEK_SET);

    // allocate memory for the artwork
    char *artwork = malloc(input_size);

    if (artwork == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory to read ansi file.\n");
        exit(1);
    }

    unsigned int ch;
    size_t n = 0;
    while ((ch = fgetc(input)) != EOF) {
        artwork[n++] = (char) ch;
    }

    // null terminate buffer
    artwork[n] = '\0';
    return artwork;
}

void draw_ansi_art(const char *filename, const int speed) {
    // check terminal size
    // https://man7.org/linux/man-pages/man4/tty_ioctl.4.html
    struct winsize term_size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &term_size);

    if (term_size.ws_col < 80) {
        fprintf(stderr, "Your terminal window is currently smaller than 80"
                " columns. Please make your terminal bigger for correct"
                " rendering of art files\n");
        exit(1);
    }
    char *artwork = read_ansi_file(filename);
    size_t artwork_size = strlen(artwork);
    char *artworkend = (char*) ((unsigned long) artwork + artwork_size); // memory address of the end of array

    // FSM variables
    STATE state = CONTINUE;         // set initial state of FSM
    unsigned int end_parsing = 0;   // continue parsing
    unsigned int cursor_pos = 0;    // set initial cursor position
    unsigned int saved_cursor = 0;  // saved cursor position

    char cmd[10];                   // store CSI command
    unsigned int cmd_n = 0;         // track CSI command position
    unsigned int args[10];          // command arguments
    unsigned int args_n = 0;        // track CSI command number of arguments

    // loop through the ANS art canvas using a FSM
    // https://en.wikipedia.org/wiki/ANSI_escape_code
    while (artwork != artworkend && end_parsing == 0) {
next_state:
        switch(state) {
            case CONTINUE:
                // check if this is an escape sequence
                if (*artwork == 0x1B) { // starts all the escape sequences
                    fputwc(btowc(*artwork), stdout);
                    state = GET_NEXT_CHAR;
                }

                // check if this is EOF
                else if (!strncmp(artwork, "\x1ASAUCE00", 7)) {
                    end_parsing = 1;
                    break;
                }

                // print characters to screen and advance cursor position
                else {
                    // slow down output to defined speed. Default Value = 110
                    usleep(speed);

                    // character needs to be converted to unicode
                    if ((unsigned char)*artwork >= (unsigned char)128)
                        fputwc(cp437[(*artwork)&0xFF], stdout);
                    else
                        fputwc(btowc(*artwork), stdout); // print character directly

                    // typically ANSI art has a limit of 80 characters per row
                    if (cursor_pos < 79) {
                        cursor_pos++;
                    } else {
                        // if this is the last character reset the terminal
                        if (artwork + 1 < artworkend) {
                            if (*(artwork + 1) != '\n')
                                wprintf(L"\e[0m\n");
                            cursor_pos = 0;
                        }
                    }

                    // reset cursor position if this is a newline
                    if (*artwork == '\n' || *artwork == '\r')
                        cursor_pos = 0;
                }
                goto get_next_char;

            case GET_NEXT_CHAR:
                fputwc(btowc(*artwork), stdout);
                if (*artwork == '[')
                    state = CHECK_IF_CSI;
                else
                    state = GET_NEXT_CHAR;
                goto get_next_char;

            case CHECK_IF_CSI:
                if (is_csi_cmd(*artwork) || *artwork == ';') {
                    state = PARSE_CSI_SEQ;
                    goto next_state;
                } else
                    cmd[cmd_n++] = *artwork;
                goto get_next_char;

            case PARSE_CSI_SEQ:
                cmd[cmd_n] = 0;
                cmd_n = 0;
                args[args_n] = strtol(cmd, NULL, 10);

                if (args[args_n] == 40)
                    args[args_n] = 49;

                // move cursor to next or previous line
                if (*artwork == 'E' || *artwork == 'F') {
                    cursor_pos = 0;
                    wprintf(L"\e[0m\n");
                }

                // move cursor to specifed column
                else if (*artwork == 'G') {
                    cursor_pos = args[0] - 1;
                }

                // set cursor position
                else if (*artwork == 'H' || *artwork == 'f') {
                    cursor_pos = args[1] - 1;
                }

                // move cursor forward
                else if (*artwork == 'C') {
                    cursor_pos = cursor_pos + args[0];
                    if (cursor_pos >= 80) {
                        wprintf(L"\e[0m\n");
                        cursor_pos = cursor_pos % 80;
                    }
                }

                // move cursor back
                else if (*artwork == 'D') {
                    if (cursor_pos != 0)
                        cursor_pos = cursor_pos - args[0];
                }

                // save cursor position
                else if (*artwork == 's') {
                    saved_cursor = cursor_pos;
                }

                // restore saved cursor position
                else if (*artwork == 'u') {
                    cursor_pos = saved_cursor;
                }

                wprintf(L"%u%c", args[args_n], *artwork);
                args_n++;
                if (is_csi_cmd(*artwork)) {
                    cmd_n = 0;
                    args_n = 0;
                    state = CONTINUE;
                } else {
                    state = CHECK_IF_CSI;
                }
                goto get_next_char;

        } // switch

        // get next character
get_next_char:
        artwork++;

    } // while loop
    wprintf(L"\e[m\n"); // reset terminal

} // draw_ansi_art

// check if this is a CSI Control Sequence
// https://en.wikipedia.org/wiki/ANSI_escape_code#CSI_(Control_Sequence_Introducer)_sequences
unsigned char is_csi_cmd(char c) {
    char csi[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'S', 'T', 'f', 'm', 'n', 's', 'u', 'l', 'h' };
    unsigned int i = 0;
    for (i = 0; i < strlen(csi); i++) {
        if (csi[i] == c)
            return 1; // character is CSI
    }
    return 0; // not a CSI character
}
