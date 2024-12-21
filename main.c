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

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements


    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; 
    if (!with)
        with = "";
    len_with = strlen(with);

  
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;


    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

int main(int argc, char *argv[]) {
    //"example.txt" -d "Nikita"
    //"example.txt" -r "ert" "Nikita"
    //"example.txt" -i -f ">"
    //"example.txt" -i -b "<"
    
    printf("start\n");
    char *action = "";
	char *added_text = "";
	char *text_to_delete = "";
	char *text_to_replace = "";
	char *text_with_replace = "";
    
    if (argc < 4) {
		printf("error: wrong amount of arguments");
		return 1;
	}
	
	char *filename = argv[1];
	const char *command = argv[2];
	printf("command: %s\n", command);
	if (strcmp(command,"-r")==0) {
	    action = "replace";
	    text_to_replace = argv[3];
	    text_with_replace = argv[4];
	}
	
	if (strcmp(command,"-d")==0) {
	    action = "delete";
	    text_to_delete = argv[3];
	}
	
	if (strcmp(command,"-i")==0 && strcmp(argv[3],"-f")==0) {
	    action = "add_before";
	    added_text = argv[4];
	}
	
	if (strcmp(command,"-i")==0 && strcmp(argv[3],"-b")==0) {
	    action = "add_after";
	    added_text = argv[4];
	}
	
	//print arguments
	printf("action: %s\n", action);
	printf("added_text: %s\n", added_text);
	printf("text_to_delete: %s\n", text_to_delete);
	printf("text_to_replace: %s\n", text_to_replace);
	printf("text_with_replace: %s\n", text_with_replace);

	
	
	//reading file into buffer
	char *buffer = 0;
	file_to_buffer(&buffer, filename);
	printf("%s", buffer);
	


	FILE * fw = fopen(filename, "w");

	if (buffer)
	{
		fseek(fw, 0, SEEK_SET);
		char *line = strtok(strdup(buffer), "\n");
		while(line) {
			printf("%s\n", line);


			if (strcmp(action, "add_before")==0) {
				fprintf(fw, "%s%s", added_text, line);
			} else if (strcmp(action, "add_after")==0) {
				fprintf(fw, "%s%s", line, added_text);
			} else if (strcmp(action, "delete")==0) {
			    char *newline;
                newline = str_remove(line, text_to_delete);
				fprintf(fw, "%s", newline);
			} else if (strcmp(action, "replace")==0) {
			    char *newline;
			    newline = str_replace(line, text_to_replace, text_with_replace);
				fprintf(fw, "%s", newline);
			}
			else {
				printf("error: incorrect flag\n");
			}



			line  = strtok(NULL, "\n");
			if (line != NULL) {
				fprintf(fw, "\n");
			}

		}

	}

	fclose(fw);
	return 0;
}