#include <stdlib.h>
#define SMALL_DIR 100000
#define m 1000

typedef struct inode{
    char* name;         //  name of file/dir
    int total_size;     //  total size (sum of subnodes' sizes if a directory, else filesize.)
    int is_dir;         //  1 if inode is a directory, 0 otherwise.

    int subnodes_count; //  counts number of files in the directory (set to 0 if not a directory)
    struct inode** subnodes;   //  list of inode_ptrs in the directory (set to NULL if not a directory or no subfiles found)

    struct inode* parent;      //  immeadiate parent of the current file. for root (/) is set to 0 / NULL.

} inode;


/// @brief  creates new inode. auto sets subnodes and subnodes_count to NULL and 0 respectively.
/// @param  name - file/dir name
/// @param  is_dir - is the inode a directory (1 if it is, else 0)
/// @param  file_size - if the file isn't a directory total_size is set to file_size.
/// @param  parent - the parent directory of the inode. adds inode to the parent.
/// @return inode variable with initialized values.
inode* create_inode(char*, int, int, inode*);


/// @brief calculates total size of each node (recursively).return 1 upon success. 0 otherwise.
/// @param  root of fs.
/// @return int (total size of root)
int calc_total_sizes(inode*);

/// @brief sum of total_size of all dirs such that dir.total_size <= SMALL_DIR
/// @param  root of fs.
/// @return int (sum of "small" directories)
int sum_small_dirs(inode*);


/// @brief frees entire fs structure (including allocated subnode lists)
/// @param  root - root of the filesystem
/// @return 1 upon success, else 0.
int free_fs(inode*);



/// @brief find size of minimal dir larger than x
/// @param  root - root of the filesystem
/// @param  x 
/// @return total size of the minimal dir larger than x
int min_dir_more_than(inode*, int);
