#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs_impl.h"
#define n 1000

inode* handle_cd(inode* root, inode* curr_node, char* arg){
    if (!strcmp(arg,"/")){
        return root;
    }
    else if(!strcmp(arg, "..")){
        return curr_node->parent;
    }
    else{
        for(int i = 0; i < curr_node->subnodes_count; i++){
            if (!strcmp(curr_node->subnodes[i]->name, arg)){
                return curr_node->subnodes[i];
            }
        }
    }
    
}


int main(int argc, char* argv[]){
    if (argc < 2){
        printf("missing filename \n");
        return 0;
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL){
        printf("filename \"%s\" doesn't exist in this directory. \n", argv[1]);
        return 0;
    }
    char* dollar;
    char* cmd;
    char* arg;

    char* size_or_dir;
    char* name;

    char* line = (char*) malloc((n+1) * sizeof(char));
    inode* root = create_inode("/", 1,0,NULL);
    inode* curr_node = root;
    while (line = fgets(line, n+1 ,f)){
        
        if (strstr(line, "$")){
            dollar = strtok(strdup(line)," ");
            cmd = strtok(0, " ");
            arg = strtok(0, "\n");
            
            if(!strcmp(cmd, "cd")){
                curr_node = handle_cd(root, curr_node, arg);
            }
            
        }
        else{ // in "ls" output block
            size_or_dir= strtok(strdup(line)," ");
            name = strtok(0, "\n");
            if(!strcmp(size_or_dir, "dir")){ // subdirectory of the current node
                inode* new_node = create_inode(name, 1, 0, curr_node);
            }
            else{                            // subfile of the current node
                inode* new_node = create_inode(name, 0, atoi(size_or_dir), curr_node);
            }
        }
        

    }
    calc_total_sizes(root);
    printf("ROOT SIZE (%s) : %d \n",root->name,root->total_size);
    printf("sum of small dirs is %d \n", sum_small_dirs(root));

    int size_to_free = root->total_size - 40000000;
    printf("ANSWER: %d\n", min_dir_more_than(root,size_to_free));
    free_fs(root);
    fclose(f);
    free(line);
}