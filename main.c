#include <stdio.h>
#include "zvm.h"
#include "blobify.h"

int main(void) {
    blb_blob_t *blob = blb_blob_create(64, 1);
    if (!blob) {
        return 1;
    }

    zvm_vm_t vm;
    uint8_t program_size = 24;
    uint8_t program[] = {
        2, R0, 'Z', 0,
        7, R0, 0, 0,
        2, R0, ZVM_IO_PORT_SCREEN, 0,
        2, R1, ZVM_IO_SERVICE_SCREEN_WRITE_CHARACTER, 0,
        2, R2, 1, 0,
        12, R0, R1, R2
    };

    blb_blob_jump(blob, 0);

    for (int i = 0; i < program_size; i++) {
        blb_blob_put(blob, program[i]);
        if (i < program_size - 1) {
            blb_blob_step(blob, 1);
        }
    }


    printf("Blobify Dynamic Data Verification:\n");
    blb_blob_print(blob, stdout);
    printf("\n");

    printf("Running ZVM with Dynamic Bytecode\n");
    int result = zvm_main(&vm, blob->block->base, program_size);

    blb_blob_delete(blob);

    printf("\nExecution Completed Successfully\n");
    return result;
}