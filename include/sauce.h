#ifndef SAUCE_H
#define SAUCE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// http://www.acid.org/info/sauce/sauce.htm
struct sauce_record {
	char                ID[5];
	char                Version[2];
	char                Title[35];
	char                Author[20];
	char                Group[20];
	char                Date[8];
	uint32_t            FileSize;
	unsigned char		DataType;
	unsigned char		FileType;
	uint16_t            TInfo1;
	uint16_t            TInfo2;
	uint16_t            TInfo3;
	uint16_t            TInfo4;
	uint16_t            Flags;
	char                Filler[22];
} __attribute__ ((__packed__)); // use smallest possible size https://gcc.gnu.org/onlinedocs/gcc-4.0.2/gcc/Type-Attributes.html

// we only care about these fields for now
struct sauce_info {
    char    *workname;
    char    *author;
    char    *group;
    char    *date;
};

// prototypes
void print_sauce_info(char *filename);
struct sauce_info *read_sauce_info(char *filename);
static char *parse_sauce_field(char *input, size_t input_length);

#endif // SAUCE_H
