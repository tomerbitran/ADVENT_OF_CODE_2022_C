#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* integer Stack implementation
*/

typedef struct charStack{
    char* stack_p;
    int curr;
    int size;
} charStack;

/* creates stack of size n*/
charStack* create_charStack(charStack*, int);
/* is stack empty */
int isEmpty(charStack*);
/* returns top item in stack. */
char top(charStack*);
/* pops an item from stack */
char pop(charStack*);
/* pushes item into stack, returns -1 if stack size exceeded else 0 */
int push(charStack*, char);
/* frees stack*/
int free_charStack(charStack*);
/* expands stack size (and frees previous stack). 
*  assumes new_size > prev_size */
charStack* expand_charStack(charStack*, int);
/* prints stack (top to bottom) */
void print_charStack(charStack*);