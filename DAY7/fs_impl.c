
# include "fs_impl.h"
# include <stdio.h>



int calc_total_size_recur(inode* pnode){
    if (pnode == NULL){
        return 0;
    }
    if (!(pnode -> is_dir)){
        return pnode->total_size;
    }
    if (pnode -> subnodes == NULL){
        pnode -> total_size = 0;
        return 0;
    }
    
    int sum = 0;
    for(int i = 0; i < pnode->subnodes_count; i++){
        sum += calc_total_size_recur(pnode->subnodes[i]);
    }
    pnode->total_size = sum;
    return sum;
}


inode* create_inode(char* name,int is_dir, int file_size,  inode* parent){
    inode* new_node = (inode*) malloc(sizeof(inode));
    new_node -> name = name;
    new_node -> is_dir = is_dir;
    if (is_dir){
        new_node ->total_size = 0;
    }
    else {
        new_node-> total_size = file_size;
    }

    new_node -> subnodes_count = 0;
    new_node -> subnodes = NULL;
    new_node -> parent = parent; 

    if(parent == NULL){
        return new_node;
    }

    if (parent -> subnodes == NULL){
        parent -> subnodes = (inode **) malloc(m * sizeof(inode*));
        parent -> subnodes_count = 1;
        parent -> subnodes[0] = new_node;
    }
    else{
        parent -> subnodes_count += 1;
        parent -> subnodes[parent->subnodes_count - 1] = new_node;
    }

    return new_node;
}

int calc_total_sizes(inode* root){
    if (root == NULL){
        return 0;
    }
    
    if(calc_total_size_recur(root) <= 0){
        
        return 0;
    }
    
    return 1;
}



int sum_small_dirs_recur(inode* pnode, int* psum){
    if (pnode == NULL){
        return 0;
    }
    if (!(pnode -> is_dir)){
        return 0;
    }
    if (pnode -> subnodes == NULL){
        return 0;
    }

    for (int i = 0; i < pnode->subnodes_count; i++){
        sum_small_dirs_recur(pnode->subnodes[i], psum);
    }
    if (pnode->total_size<= SMALL_DIR){
        *psum += pnode->total_size;
    }
    return 1;

}

int sum_small_dirs(inode* root){
    int sum = 0;
    sum_small_dirs_recur(root, &sum);
    return sum;
}



int free_fs_recur(inode* pnode){
    if (pnode == NULL){
        return 0;
    }
    if (!(pnode->is_dir)){
        free(pnode);
        return 0;
    }
    if (pnode->subnodes == NULL){
        free(pnode);
        return 0;
    }

    for (int i = 0; i < pnode->subnodes_count; i++){
        free_fs_recur(pnode->subnodes[i]);
    }
    free(pnode->subnodes);
    free(pnode);
    return 1;

}


int free_fs(inode* root){
    return free_fs_recur(root);
}

int min_dir_more_than_recur(inode* pnode, int x, int* curr_min){
    if (pnode == NULL){
        return -1;
    }
    if (!(pnode -> is_dir)){
        return -1;
    }
    if (pnode -> subnodes == NULL){
        return (pnode->total_size >= x)? pnode->total_size:-1;
    }

    for (int i = 0; i < pnode->subnodes_count; i++){
        min_dir_more_than_recur(pnode->subnodes[i], x, curr_min);
    }
    if ((pnode->total_size >= x) && ((pnode->total_size < *curr_min)|| (*curr_min < x))){
        *curr_min = pnode->total_size;
    }
    return 1;
}


int min_dir_more_than(inode* root, int x){
    int min = -1;
    min_dir_more_than_recur(root, x, &min);
    return min;
}