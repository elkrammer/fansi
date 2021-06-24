#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sauce.h"

// http://www.acid.org/info/sauce/sauce.htm
// http://www.retroarchive.org/swag/DATATYPE/0036.PAS.html
struct sauce_info *read_sauce_info(char *filename) {
    FILE *input = fopen(filename, "r");
    struct sauce_record sauce;
    struct sauce_info *info;
    info = calloc(1, sizeof(struct sauce_info));

    if (!input) {
        fclose(input);
        fprintf(stderr, "Failed to open file %s.\n", filename);
        exit(1);
    }

    if (fseek(input, -sizeof(sauce), SEEK_END) != 0) {
        fclose(input);
        fprintf(stderr, "Unable to read SAUCE record from %s.\n", filename);
        exit(1);
    }

    // read data
    fread(&sauce, sizeof sauce, 1, input);

    // map & parse fields
    info->author    = parse_sauce_field(sauce.Author, sizeof sauce.Author);
    info->workname  = parse_sauce_field(sauce.Title, sizeof sauce.Title);
    info->group     = parse_sauce_field(sauce.Group, sizeof sauce.Group);
    info->date      = parse_sauce_field(sauce.Date, sizeof sauce.Date);

    fclose(input);
    return info;
}

// strips spaces
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

static char *parse_sauce_field(char *input, size_t input_length) {
    char *result;
    result = malloc(input_length + 1);
    strncpy(result, input, input_length);

    if (!result) {
        fprintf(stderr, "Error parsing sauce field :%s", input);
        return input;
    }

    // strip spaces
    return trimwhitespace(result);
}
