#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fptr = fopen("input.txt", "r");

    int cr;
    size_t lines = 0;

    while((cr = getc(fptr)) != EOF){
        if(cr == '\n'){
            lines++;
        }
    }

    printf("Number of lines: %ld\n", lines);
    rewind(fptr);

    char *data[lines][2];
    size_t n;

    for(size_t i = 0; i< lines; i++){
        data[i][0] = NULL;
        data[i][1] = NULL;
        char*temp = NULL;
        size_t n = 0;
        size_t line_length = 0;

        line_length = getline(&temp, &n, fptr);

        if(line_length < 14) continue;

        char *token = strtok(temp, " ");

        for(size_t j = 0; j<3; j++){
            if(j>0){
                data[i][j-1] = token;
                token = strtok(NULL, " ");
            }
        }
    }

    for(size_t i = 0; i<lines; i++){
        printf("Values for line %d: %s and %s", i, data[i][0], data[i][1]);
        free(data[i][0]);
        free(data[i][1]);
    }


    fclose(fptr);
    return 0;
}
