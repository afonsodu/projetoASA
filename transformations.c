#include <stdio.h>

typedef struct{
    int current_width;
    int current_lenght;
    int current_height;
}Current_measures;

typedef struct{
    int width;
    int lenght;
    int height;
    int min_width_or_lenght;

}Block;

typedef struct{
    Block *block;
    int diff_blocks;
}Storage;

int check_min_height(Block *block){
    if(block->height <= block->width && block->height <= block->lenght){
        return 1;
    }
    return 0;
}

int check_width_or_lenght(Block *block){
    if(block->width <= block->lenght){
        return 1;
    }
    if(block ->width > block->lenght){
        return 2;
    }
}

void ordenate_array(Storage *storage){
    

}



void minimal_height(Storage *storage){
    for(int i = 0; i < storage->diff_blocks; i++){
        if(check_min_height(&storage->block[i]) == 0){
            int value = check_width_or_lenght(&storage->block[i]);
                if(value == 1){
                    rotate_block(&storage->block[i],2);
                }
                else{
                    rotate_block(&storage->block[i],3);
                }
        }

    }
}


void rotate_block(Block *block, int n){
    int temp;

    if(n == 1){
        temp = block->width;
        block->width = block->lenght;
        block->lenght = temp;
    }
    else if (n == 2){
        temp = block->width;
        block->width = block->height;
        block->height = temp;
    }
    else if(n == 3){
        temp = block->lenght;
        block->lenght = block->height;
        block->height = temp;
    }
    
    else if(n == 4){
        temp = block->lenght;
        block->lenght = block->height;
        block->height = temp;
        temp = block->width;
        block->width = block->height;
        block->height = temp;
    }
    else if(n == 5){
        temp = block->width;
        block->width = block->height;
        block->height = temp;
        temp = block->lenght;
        block->lenght = block->height;
        block->height = temp;
    }
}


void place_block(Block *block){

}