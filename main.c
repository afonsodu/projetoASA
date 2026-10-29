
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "transformations.c"

int main(int argc, char *argv[]){

    if(argc != 2){
        return 1;
    }
    int n = atoi(argv[1]);
    int width;
    int lenght;
    int height;
    Storage my_storage;
    Storage *storage = &my_storage;
    storage->diff_blocks = n;
    storage->block = (Block*)malloc(n * sizeof(Block));

    for (int i = 0; i < n; i++){
        int res = scanf("%d %d %d", &width,&lenght,&height);
        (void)res;
        storage->block[i].width = width;
        storage->block[i].lenght= lenght;
        storage->block[i].height = height;
    }

    free(storage->block);
    return 0;
}
