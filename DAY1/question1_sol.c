#include <stdio.h>
#include <stdlib.h>
#define n 100

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("missing filename");
        return 0;
    }
    FILE* f = fopen(argv[1], "r");
    char* line = (char *) malloc((n+1)*sizeof(char));
    int MAX = 0;
    int currsum = 0;
    while(line = fgets(line,n+1,f)){
        if (line == 0 || line[0] == '\n'){
            if (currsum > MAX){
                MAX = currsum;
            }
            currsum = 0;
        }
        else{
            currsum += atoi(line);
        }
    }
    fclose(f);
    free(line);
    printf("max is %d\n", MAX);
}