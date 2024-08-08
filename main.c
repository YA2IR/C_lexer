#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer/lexer.h"
#include <sys/stat.h>

char* open_file(char* name) {
    struct stat status;
        
    if(stat(name, &status) < 0) {
        perror("opening file");
        return NULL;
    }

    long long file_size = status.st_size;

    char *buff = (char*)malloc(file_size + 1);
    if(!buff) {
        perror("malloc");
        return NULL;
    }

    FILE* f = fopen(name, "rb");
    if (!f) {
        perror("opening file");
        fclose(f);
        return NULL;
    }

    fread(buff, 1, file_size, f);
    buff[file_size] = '\0'; 

    fclose(f);
    return buff;
}

void lex_file(char*name) {

    char* buff = open_file(name);
    if (buff == NULL) 
        return;
    

    lexer *l = init_lexer(buff);

    token t;
    while((t = next_token(l)).type != t_EOF) {

        if (t.type == ILLEGAL) {
            printf("\n ###### error: illegal charachter : '%s'", t.literal);
            break;
        }
        
        printf("\n== ('%s','%s')", t.literal, enum_str[t.type]);
        free(t.literal);
    }

    free(l);
    free(buff);
    

    if(t.type != ILLEGAL)
        assert(t.type == t_EOF);
    
    printf("\n== --END-- ==\n");
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("usage: ./program <filename.c>\n");
        return 0;
    }

    lex_file(argv[1]);

    return 0;
}


