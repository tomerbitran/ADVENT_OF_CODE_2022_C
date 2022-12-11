#include <stdio.h>
#include <stdlib.h>
#define n 100

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("missing filename");
        return 0;
    }
    int maxes[3] = {0,0,0};
    FILE* f = fopen(argv[1], "r");
    char* line = (char *) malloc((n+1)*sizeof(char));
    int currsum = 0;
    while(line = fgets(line,n+1,f)){
        if (line == 0 || line[0] == '\n'){
            if (currsum > maxes[0]){
                maxes[2] = maxes[1];
                maxes[1] = maxes[0];
                maxes[0] = currsum;
            }
            else if (currsum > maxes[1])
            {
                maxes[2] = maxes[1];
                maxes[1] = currsum;
            }
            else if (currsum > maxes[2])
            {
                maxes[2] = currsum;
            }
            currsum = 0;
        }
        else{
            currsum += atoi(line);
        }
    }
    fclose(f);
    free(line);
    printf("maxes are %d\n", maxes[0]+maxes[1]+maxes[2]);
}