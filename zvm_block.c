#include "zvm_block.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

zvm_block_t * zvm_block_new(zvm_block_count_t elements_count, uint8_t element_size){
    if(!zvm_block_is_valid_size(element_size * elements_count)){
        return NULL;
    }

    zvm_block_t *block = (zvm_block_t*)malloc(sizeof(zvm_block_t));
    if(block){
        block->base = (uint8_t*)malloc((element_size) * (elements_count));
        if(!block->base){
            free(block);
            return NULL;
        }
    }else return NULL;
    
    zvm_block_init(block, element_size, elements_count);
    return block;
}

bool zvm_block_delete(zvm_block_t *block){
    if(!block) return false;

    if(block->base)
        free(block->base);

    free(block);
    return true;
}
// step(-1)
bool zvm_block_step(zvm_block_t *block, zvm_block_offset_t to){
    if(!block || !block->base) return false;
    zvm_block_offset_t offset = block->cursor.offset + to;

    if(offset <= ZVM_BLOCK_OFFSET_INIT_VALUE){
        block->cursor.offset = ZVM_BLOCK_OFFSET_INIT_VALUE;
        return false;
    }else if(offset >= block->size){
        block->cursor.offset = block->size;
        return false;
    }

    block->cursor.offset = offset;
    return true;
}

bool zvm_block_put(zvm_block_t *block, uint8_t value){
    if(!block || !block->base) return false;

    if((block->cursor.offset > ZVM_BLOCK_OFFSET_INIT_VALUE) && (block->cursor.offset < block->size)){
        block->base[block->cursor.offset] = value;
        return true;
    }

    return false;
}

bool zvm_block_get(zvm_block_t *block, uint8_t *value){

    if(!block || !block->base || !value) return false;
    
    if((block->cursor.offset > ZVM_BLOCK_OFFSET_INIT_VALUE) && (block->cursor.offset < block->size)){
        *value = block->base[block->cursor.offset];
        return true;
    }

    return false;
}

bool zvm_block_move(zvm_block_t *block, zvm_block_offset_t to){
    if(!block || !block->base){
        return false;
    }

    if((to > ZVM_BLOCK_OFFSET_INIT_VALUE) && (to < block->size)){
        block->cursor.offset = to;
        return true;
    }

    return false;
}

// TODO: block permissions + access by address


// int main(void){
//     zvm_block_t * block = zvm_block_new(8, 1);
    

//     if(!block){
//         fprintf(stderr, "Unable to allocate a new block\n");
//         return 1;
//     }

//     uint8_t value = 25;

//     zvm_block_delete(block);
//     return 0;
// }