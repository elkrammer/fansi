#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

char *load_ansi_file(const char *filename) {
    char *buffer = NULL;
    unsigned int buffer_size = 0;

    int fd = open(filename, O_RDONLY); // file descriptor

    if (fd < 0) {
        fprintf(stderr,"Error: Unable to read ansi file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // TODO: validate this is actually an .ans file

    buffer_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    buffer = mmap(NULL, buffer_size, PROT_READ, MAP_SHARED, fd, 0);

    // error reading file
    if (buffer == (void*)(-1)) {
        close(fd);
        fprintf(stderr, "Error mapping file `%s' into memory.\n", filename);
        exit(EXIT_FAILURE);
    }

    char *file = malloc(buffer_size);
    memcpy(file, buffer, buffer_size);
    free(file);

    // clean up
    munmap(buffer, buffer_size);
    close(fd);

    return file;
}

void draw_ansi_art(const char *art) {
    printf("%s", art);
}
