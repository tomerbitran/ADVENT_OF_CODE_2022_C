#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* find if there are any duplicates in the first 4 chars of the strings*/
int any_duplicates(char* s){
    for(int i = 0; i < 14; i++){
        for (int j = i+1; j < 14; j++){
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

    char s[14];
    char t;
    int counter = 14;

    fgets(s,15, f);

    if (!(any_duplicates(s))){
        fclose(f);
        printf("s = %s, and ANSWER: %d\n",s, counter);
        return 0;
    }

    while((t=fgetc(f)) != EOF){
        counter++;
        for (int i = 0; i < 13; i++){
            s[i]=s[i+1];
        }
        s[13] = t;

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