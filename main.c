
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


void sort_array(Storage *storage){
    int modifications = 0;
    for(int i = 1; i <storage->blocks_in_storage; i++){
        if(storage->block[i].l > storage->block[i-1].l || 
            (storage->block[i].l == storage->block[i-1].l 
            && storage->block[i].w > storage->block[i-1].w)){
                Block temp_block = storage->block[i-1];
                storage->block[i-1] = storage->block[i];
                storage->block[i] = temp_block;
                modifications += 1;
        }
    }
    if(!modifications){
        return;
    }
    sort_array(storage);
}

int max_height(Storage *storage){
    int n = storage->blocks_in_storage;
    int dp[n];
    int best = 0;

    for(int i = 0; i < n; i++){
        dp[i] = storage->block[i].h;
        for(int j = 0; j < i; j++){
            if(storage->block[j].w > storage->block[i].w &&
               storage->block[j].l > storage->block[i].l &&
               dp[j] + storage->block[i].h > dp[i]){
                dp[i] = dp[j] + storage->block[i].h;
            }
        }
        if(dp[i] > best){
            best = dp[i];
        }
    }
    return best;
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

    storage->diff_blocks = n;
    storage->block = (Block*)malloc(n * sizeof(Block));

    for (int i = 0; i < n; i++){
        int res = scanf("%d %d %d", &w,&l,&h);
        (void)res;
        storage->block[i].w = w;
        storage->block[i].l= l;
        storage->block[i].h = h;
    }
    
    free(storage->block);
    return 0;
}
