#ifndef PARSER_H
#define PARSER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <sys/ioctl.h>

typedef enum {
    CONTINUE,           // continue parsing file
    GET_NEXT_CHAR,      // get next character
    CHECK_IF_CSI,       // check if this is a CSI Sequence
    PARSE_CSI_SEQ,      // parse CSI Sequence
} STATE;

// prototypes
char *read_ansi_file(const char *filename);
unsigned char is_csi_cmd(char c);
void draw_ansi_art(const char *filename, const int speed);

#endif // PARSER_H
