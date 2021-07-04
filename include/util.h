#ifndef UTIL_H
#define UTIL_H

#include <dirent.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// prototypes
void print_logo();
void print_usage();
char *trimwhitespace(char *str);
void screensaver_mode(char *directory);

#endif // UTIL_H
