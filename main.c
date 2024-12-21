#define FILE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"


char *str_remove(char *str, char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

int main() {
    char *filename = "example.txt";

    //reading file into buffer
	char *buffer = 0;
	file_to_buffer(&buffer, filename);
	printf("%s", buffer);
}