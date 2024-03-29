#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plumber.h"

int sporth_gen_sine(sporth_stack *stack, void *ud)
{
    plumber_data *pd = ud;

    int size;
    SPFLOAT out = 0;
    sp_ftbl *ft;
    char *str;

    switch(pd->mode){
        case PLUMBER_CREATE:
            plumber_add_module(pd, SPORTH_GEN_SINE, 0, NULL);
            break;

        case PLUMBER_INIT:
            if(sporth_check_args(stack, "sf") != SPORTH_OK) {
                fprintf(stderr, "Init: not enough arguments for gen_sine\n");
                return PLUMBER_NOTOK;
            }
            size = (int)sporth_stack_pop_float(stack);
            str = sporth_stack_pop_string(stack);
#ifdef DEBUG_MODE
            fprintf("Creating sine table %s of size %d\n", str, size);
#endif
            sp_ftbl_create(pd->sp, &ft, size);
            sp_gen_sine(pd->sp, ft);
            plumber_ftmap_add(pd, str, ft);
            free(str);
            break;

        case PLUMBER_COMPUTE:
            size = (int)sporth_stack_pop_float(stack);
            break;

        case PLUMBER_DESTROY:
            break;

        default:
           printf("Error: Unknown mode!");
           break;
    }
    return PLUMBER_OK;
}
