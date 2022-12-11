#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 1000

typedef struct assignment{
    int start;
    int end;
} assignment;

assignment* str_to_assignment(char* str){
    int num1 = atoi(strtok(str, "-"));
    int num2 = atoi(strtok(0, "-"));
    assignment* a = (assignment*) malloc(sizeof (assignment));
    a->start = num1;
    a->end = num2;
    return a;
}

int main(int argc, char* argv[]){
    
    if (argc < 2){
        printf("missing filename");
        return 0;
    }
    
    FILE* f = fopen(argv[1], "r");
    char* line = (char *) malloc((n+1)*sizeof(char));
    char* e1_buf;
    char* e2_buf;
    int count = 0;
    
    while(line = fgets(line,n+1,f)){
        e1_buf = strtok(strdup(line),",");
        e2_buf = strdup(strtok(0, "\n"));
        printf("%s, %s\n", e1_buf, e2_buf);
        assignment* a1 = str_to_assignment(e1_buf);
        assignment* a2 = str_to_assignment(e2_buf);
        printf("a1: [%d-%d]. a2: [%d-%d]\n", a1->start, a1->end,a2->start,a2->end);

        if (((a1->start <= a2->start) && (a2->end <= a1->end)) || ((a2->start <= a1->start) && (a1->end <= a2->end))){ 
            printf("assigments are contained within each other. \n");
            count++;
        }

        free(a1);
        free(a2);
        free(e1_buf);
        free(e2_buf);
    }

    printf("result %d\n", count);
    fclose(f);
    free(line);
}