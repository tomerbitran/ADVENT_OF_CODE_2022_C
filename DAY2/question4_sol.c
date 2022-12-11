#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 100

#define max(a,b) ((a > b)? (a) : (b))
#define min(a,b) ((a < b)? (a) : (b))

// Rock = 1 (0), Paper = 2 (1), Scissors =3 (2)

int score_graph[3][3] = {{4, 8, 3}, {1,5,9},{7,2,6}}; // access as score_graph[opp][me]
int calc_score(char P1, char P2){
    int opp;
    switch(P1){
        case('A'): //ROCK
            opp = 0;
            break;
        case('B'): //PAPER
            opp = 1;
            break;
        case ('C'): // Scissors
            opp = 2;
            break;
        default:
            return -1;
    }
    switch(P2){
        case('X'): // NEED TO LOSE
            return min(score_graph[opp][(opp+2)%3], score_graph[opp][(opp+1)%3]);
        case('Y'): // NEED TO DRAW
            return score_graph[opp][opp];
        case('Z'): // NEED TO WIN
            return max(score_graph[opp][(opp+2)%3], score_graph[opp][(opp+1)%3]);
        default:
            return -1;
    }

}


int main(int argc, char* argv[]){
    if (argc < 2){
        printf("missing filename");
        return 0;
    }
    FILE* f = fopen(argv[1], "r");
    char* line = (char *) malloc((n+1)*sizeof(char));
    char* BUF;
    char P1,P2;
    int P2_score;
    while(line = fgets(line,n+1,f)){
        BUF = strtok(strdup(line), " \n");
        P1 = BUF[0];
        BUF = strtok(0," \n");
        P2 = BUF[0];
        P2_score += calc_score(P1,P2);
    }
    printf("P2 score is: %d\n", P2_score);
    fclose(f);
    free(line);
}