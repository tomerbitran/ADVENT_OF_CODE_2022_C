#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 1000

int reset_count_list(int* list, int size){
    for (int i =0; i<size; i++){
        list[i] = 0;
    }
}

int priority(char c){
    if (97<= c && c<=122){      // c  is in [a,z]
        return ((int)c)-96;
    } 
    else if (65 <= c && c<= 90) // c is in [A,Z]
    {
        return ((int)c)-38;
    }
    else{                       //invalid character
        fprintf(stderr, "INVALID CHAR PASSED AS ARGUMENT - %c/%d \n", c, c);
    }
    
}

int find_commons_priority(char* s1, char* s2,char* s3, int* L1, int* L2, int* L3){

    
    int retval = 0;
    
    for(int i = 0; i < strlen(s1)-1; i++){ // WANT TO DISREGARD \n\0
        int p1 = priority(s1[i]);
        L1[p1 - 1] += 1;
        
    }
    for(int i = 0; i < strlen(s2)-1; i++){
        int p2 = priority(s2[i]);
        L2[p2 - 1] += 1;
        
    }
    for(int i = 0; i < strlen(s3)-1; i++){
        int p3 = priority(s3[i]);
        L3[p3 - 1] += 1;
        
    }
    for(int j = 0; j < 52; j++){
        if ((L1[j] > 0) && (L2[j] > 0) && (L3[j] > 0)){
            retval = j+1;
        }
    }

    reset_count_list(L1,52);
    reset_count_list(L2,52);
    reset_count_list(L3,52);
    if (retval > 0){
        printf("\npriority of common item is: %d\n", retval);
        return retval;
    }
}


int main(int argc, char* argv[]){
    if (argc < 2){
        printf("missing filename");
        return 0;
    }
    
    int count_list_1[52];
    reset_count_list(count_list_1, 52);
    int count_list_2[52];
    reset_count_list(count_list_2, 52);
    int count_list_3[52];
    reset_count_list(count_list_3, 52);
    
    FILE* f = fopen(argv[1], "r");
    char* line = (char *) malloc((n+1)*sizeof(char));
    int prior_sum = 0;
    
    while(line = fgets(line,n+1,f)){
        printf("Line read: ");
        
        char* s1 = strdup(line);
        line = fgets(line,n+1,f);
        char* s2 = strdup(line);
        line = fgets(line,n+1,f);
        char* s3 = strdup(line);
        
        printf("%s %s %s", s1, s2, s3);

        prior_sum += find_commons_priority(s1,s2, s3, count_list_1, count_list_2, count_list_3);

        free(s1);
        free(s2);
        free(s3);
    }
    printf("answer is: %d\n", prior_sum);
    fclose(f);
    free(line);
}