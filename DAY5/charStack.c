#include "charStack.h"


/* creates heap allcoated stack from user provided pointer */

charStack* create_charStack(charStack* sp, int size){
    sp->size = size;
    sp->curr = -1;
    sp->stack_p = (char *) malloc(sizeof(char)*size); 
    return sp;
}

/* returns top. sp->curr is >= 0 */
char top(charStack* sp){
    if (sp->curr >= 0){
        return sp->stack_p[sp->curr];
    }
    return 0;
}
/* stack is empty <-> sp->curr == -1 */
int isEmpty(charStack* sp){
    return (sp->curr == -1);
}
/* returns top. sp->curr has to be >= 0 */
char pop(charStack* sp){
    if (sp->curr >= 0){
        return sp->stack_p[sp->curr--];
    }
    else{
        return 0;
    }
}

/* returns -1 if stack size exceeded */
int push(charStack* sp, char val){
    if (sp->curr == sp->size - 1 ){
        // stack is full 
        return -1;
    }
    else {
        sp->stack_p[++sp->curr] = val;
        return 0;
    }
}




/* free allocated memory*/
int free_charStack(charStack* sp){
    free(sp->stack_p);
    free(sp);
}

/* asserts new_size >= curr_size. also frees sp.*/
charStack* expand_charStack(charStack* sp, int new_size){
    if (new_size < sp->size){return 0;}

    charStack* new_sp;
    create_charStack(new_sp, new_size);

    for (int i = 0; i <= sp->curr; i++){
        new_sp->stack_p[i] = sp->stack_p[i];
    }
    new_sp->curr = sp->curr;

    free_charStack(sp);
    return new_sp;
}

/* prints stack (top to bottom) */
void print_charStack(charStack* sp){
    for(int t = sp->curr; t>=0; t--){
        printf("|%c|\n", sp->stack_p[t]);
    }
    printf("|____|\n end of stack \n");
}