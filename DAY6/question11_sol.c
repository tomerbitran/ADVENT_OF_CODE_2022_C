#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* find if there are any duplicates in the first 4 chars of the strings*/
int any_duplicates(char* s){
    for(int i = 0; i < 4; i++){
        for (int j = i+1; j < 4; j++){
            if(s[i]==s[j]){
                return 1;
            }
        }
    }
    return 0;
}


int main(int argc, char* argv[]){
    if (argc < 2){
        printf("missing filename \n");
        return 0;
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL){
        printf("filename doesn't exist. \n");
        return 0;
    }

    char s[4];
    char t;
    int counter = 4;

    fgets(s,5, f);

    if (!(any_duplicates(s))){
        fclose(f);
        printf("s = %s, and ANSWER: %d\n",s, counter);
        return 0;
    }

    while((t=fgetc(f)) != EOF){
        counter++;
        s[0] = s[1];
        s[1] = s[2];
        s[2] = s[3];
        s[3] = t;

        if (!any_duplicates(s)){
            fclose(f);
            printf("ANSWER: %d\n", counter);
            return 0;
        }
    }

    fclose(f);
    printf("NO ANSWER FOUND. \n");
    return 0;
}