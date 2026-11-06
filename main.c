
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int w;
    int l;
    int h;
} Block;

typedef struct{
    Block *block;
    int diff_blocks;
    int blocks_in_storage;
}Storage;


Block rotate_block(Block *block, int n){
    int temp;
    Block rotated = *block;
    
    if (n == 1){
        temp = rotated.w;
        rotated.w = rotated.h;
        rotated.h = temp;
    }
    else if(n == 2){
        temp = rotated.l;
        rotated.l = rotated.h;
        rotated.h = temp;
    }
    
   
    return rotated;
}

void normalize_bottom(Storage *storage, Block block){
    int temp;
    if(block.w < block.l){
        temp = block.l;
        block.l = block.w;
        block.w = temp;
    }
    storage->block[storage->blocks_in_storage] = block;
    storage->blocks_in_storage += 1;
}


void create_blocks(Storage *storage,Block *block){
    
    normalize_bottom(storage, *block);
    normalize_bottom(storage, rotate_block(block, 1));
    normalize_bottom(storage, rotate_block(block, 2));
}


void compare_blocks(const void *a, const void *b){
    const Block *x = (const Block*) a;
    const Block *y = (const Block*) b;
    if (x->l != y->l){
        if(y->l > x->l){
            return 1;
        }
        else{
            return -1;
        }
    }
    if (x->w != y->w){
        if(y->w > x->w){
            return 1;
        }
        else{
            return -1;
        }
    }
    return 0;
}

void sort_array(Storage *storage){
    qsort(storage->block, storage->blocks_in_storage,
          sizeof(Block), compare_blocks);
}

int max_height(Storage *storage){
    int n = storage->blocks_in_storage;
    int tower[n];
    int best_tower = 0;
    int i,j;
    for(i = 0; i < n; i++){
        tower[i] = storage->block[i].h;
        for(j = 0; j < i; j++){
            if(storage->block[j].w > storage->block[i].w &&
               storage->block[j].l > storage->block[i].l &&
               tower[j] + storage->block[i].h > tower[i]){
                tower[i] = tower[j] + storage->block[i].h;
            }
        }
        if(tower[i] > best_tower){
            best_tower = tower[i];
        }
    }
    return best_tower;
}

int main(int argc, char *argv[]){

    if(argc != 2){
        return 1;
    }
    int n = atoi(argv[1]);
    int w;
    int l;
    int h;
    
    Storage my_storage;
    Storage *storage = &my_storage;
    storage->blocks_in_storage = 0;
    storage->diff_blocks = n;
    storage->block = (Block*)malloc(3*n * sizeof(Block));
    int i;
    for (i = 0; i < n; i++){
        int res = scanf("%d %d %d", &w,&l,&h);
        (void)res;
        storage->block[i].w = w;
        storage->block[i].l= l;
        storage->block[i].h = h;
    }
    
    free(storage->block);
    return 0;
}
