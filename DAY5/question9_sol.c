#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charStack.h"

#define n 1000


int main(int argc, char* argv[]){
    
    if (argc < 2){
        printf("missing filename \n");
        return 0;
    }
    
    
    charStack csl[9];

    for (int i = 0; i<9; i++){ 
        create_charStack(&csl[i], 100);
    }

    // // 0
    // push(&csl[0],'Z');
    // push(&csl[0],'N');
    // // 1
    // push(&csl[1],'M');
    // push(&csl[1],'C');
    // push(&csl[1],'D');
    // // 2
    // push(&csl[2],'P');


    // 0 
    push(&csl[0],'B');
    push(&csl[0],'S');
    push(&csl[0],'V');
    push(&csl[0],'Z');
    push(&csl[0],'G');
    push(&csl[0],'P');
    push(&csl[0],'W');
    // 1
    push(&csl[1],'J');
    push(&csl[1],'V');
    push(&csl[1],'B');
    push(&csl[1],'C');
    push(&csl[1],'Z');
    push(&csl[1],'F');
    // 2
    push(&csl[2],'V');
    push(&csl[2],'L');
    push(&csl[2],'M');
    push(&csl[2],'H');
    push(&csl[2],'N');
    push(&csl[2],'Z');
    push(&csl[2],'D');
    push(&csl[2],'C');
    // 3
    push(&csl[3],'L');
    push(&csl[3],'D');
    push(&csl[3],'M');
    push(&csl[3],'Z');
    push(&csl[3],'P');
    push(&csl[3],'F');
    push(&csl[3],'J');
    push(&csl[3],'B');
    // 4
    push(&csl[4],'V');
    push(&csl[4],'F');
    push(&csl[4],'C');
    push(&csl[4],'G');
    push(&csl[4],'J');
    push(&csl[4],'B');
    push(&csl[4],'Q');
    push(&csl[4],'H');
    // 5
    push(&csl[5],'G');
    push(&csl[5],'F');
    push(&csl[5],'Q');
    push(&csl[5],'T');
    push(&csl[5],'S');
    push(&csl[5],'L');
    push(&csl[5],'B');
    // 6
    push(&csl[6],'L');
    push(&csl[6],'G');
    push(&csl[6],'C');
    push(&csl[6],'Z');
    push(&csl[6],'V');
    // 7
    push(&csl[7],'N');
    push(&csl[7],'L');
    push(&csl[7],'G');
    // 8
    push(&csl[8],'J');
    push(&csl[8],'F');
    push(&csl[8],'H');
    push(&csl[8],'C');

    for ( int i = 0; i < 9; i++){
        printf("CHAR STACK NUMBER %d: \n",i);
        print_charStack(&csl[i]);

        printf("END STACK NUMBER %d. \n",i);
    }
    FILE* f = fopen(argv[1], "r");
    int num, src, dest;
    while(fscanf(f, "move %d from %d to %d\n",&num, &src, &dest) == 3){
        printf("num = %d, src = %d, dest = %d \n", num, src, dest);
        src = src - 1;
        dest = dest - 1;
        for (int i = 0; i < num; i++){
            char r = pop(&csl[src]);
            push(&csl[dest], r);
        }
    }

    for (int i = 0; i<9; i++){
        printf("%c",top(&csl[i]));
    }

    for(int i = 0; i<9; i++){
        free(csl[i].stack_p);
    }
    printf("\n");
    fclose(f);
}