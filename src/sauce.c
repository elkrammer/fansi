#include "sauce.h"
#include "util.h"

void print_sauce_info(char *filename) {
    struct sauce_info *sauce;
    sauce = read_sauce_info(filename);

    if (!sauce) {
        fprintf(stderr, "File '%s' has no SAUCE information.", filename);
        exit(1);
    }

    printf("Artwork Name: '%s'\n", sauce->workname);
    printf("Author      : '%s'\n", sauce->author);
    printf("Group Name  : '%s'\n", sauce->group);
    printf("Date        : '%s'\n", sauce->date);

    // clean up
    free(sauce);
}

// http://www.acid.org/info/sauce/sauce.htm
// http://www.retroarchive.org/swag/DATATYPE/0036.PAS.html
struct sauce_info *read_sauce_info(char *filename) {
    FILE *input = fopen(filename, "r");
    struct sauce_record sauce;
    struct sauce_info *info;
    info = calloc(1, sizeof(struct sauce_info));

    if (!input) {
        fprintf(stderr, "Error: Failed to open file '%s' to read SAUCE information.\n", filename);
        exit(1);
    }

    if (fseek(input, -sizeof(sauce), SEEK_END) != 0) {
        fclose(input);
        fprintf(stderr, "Error: Unable to read SAUCE record from file '%s'.\n", filename);
        exit(1);
    }

    // read data
    fread(&sauce, sizeof sauce, 1, input);

    // map & parse fields
    info->author    = parse_sauce_field(sauce.Author, sizeof sauce.Author);
    info->workname  = parse_sauce_field(sauce.Title, sizeof sauce.Title);
    info->group     = parse_sauce_field(sauce.Group, sizeof sauce.Group);
    info->date      = parse_sauce_field(sauce.Date, sizeof sauce.Date);

    // check if data is valid by looking for an ANSI escape sequence in the Title
    if(strstr(sauce.Title, "\033[") != NULL) {
        fclose(input);
        fprintf(stderr, "Error: Parsing of SAUCE record for file '%s' has failed.\n", filename);
        exit(1);
    }

    fclose(input);
    return info;
}

static char *parse_sauce_field(char *input, size_t input_length) {
    char *result;
    result = malloc(input_length + 1);

    if (result == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for parsing sauce.\n");
        exit(1);
    }

    strncpy(result, input, input_length);

    if (!result) {
        fprintf(stderr, "Error: Could not parse sauce field '%s'", input);
        return input;
    }

    // strip spaces
    return trimwhitespace(result);
}
