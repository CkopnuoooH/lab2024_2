#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int file_to_buffer(char **buffer, char *filename) {
    long length;
    FILE *f = fopen(filename, "r");
    
    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        *buffer = malloc(length + 1);
        if (*buffer) {
            fread(*buffer, 1, length, f);
            (*buffer)[length] = '\0';
        } else {
            fclose(f);
            return -1; // Memory allocation failed
        }
    } else {
        return -1; // File open failed
    }
    
    fclose(f);
    return 0;
}

