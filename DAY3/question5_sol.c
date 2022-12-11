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

int find_priority_item(char* s1, char* s2, int k, int* count_list){

    reset_count_list(count_list, 52);
    int retval = 0;
    
    for(int i = 0; i < k; i++){
        int p1 = priority(s1[i]);
        count_list[p1 - 1] += 1;
        
    }
    for(int j = 0; j < k; j++){
        int p2 = priority(s2[j]);
        if(count_list[p2 - 1] > 0){
            retval = p2; //ret p
            printf("\ncommon item is : %c\n ", s2[j]);
        }
    }

    reset_count_list(count_list, 52);
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
    
    int count_list[52];
    reset_count_list(count_list, 52);
    FILE* f = fopen(argv[1], "r");
    char* line = (char *) malloc((n+1)*sizeof(char));
    int prior_sum = 0;
    
    while(line = fgets(line,n+1,f)){
        printf("Line read: ");
        int racksize = strlen(line); // racksize should be 2k+1+1 (for \n\0) unless EOF reached (then, 2k)
        int k = (racksize-1)/2;
        printf("racksize: %d k: %d\n", racksize, k);
        char* s1 = (char*)malloc(k+1);
        strncpy(s1, line, k);
        s1[k] = '\0'; 
        char* s2 = (char*)malloc(k+1);
        strncpy(s2, line+k, k);
        s2[k] = '\0'; 
        
        printf("%s %s", s1, s2);

        prior_sum += find_priority_item(s1,s2, k, count_list);

        free(s1);
        free(s2);
    }
    printf("answer is: %d\n", prior_sum);
    fclose(f);
    free(line);
}