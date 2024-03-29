#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plumber.h"

int sporth_gen_vals(sporth_stack *stack, void *ud)
{
    plumber_data *pd = ud;

    SPFLOAT out = 0;
    sp_ftbl *ft;
    char *str, *args;

    switch(pd->mode){
        case PLUMBER_CREATE:
            plumber_add_module(pd, SPORTH_GEN_VALS, 0, NULL);
            break;

        case PLUMBER_INIT:
            if(sporth_check_args(stack, "ss") != SPORTH_OK) {
               fprintf(stderr,"Init: not enough arguments for gen_vals\n");
                return PLUMBER_NOTOK;
            }
            args = sporth_stack_pop_string(stack);
            str = sporth_stack_pop_string(stack);
#ifdef DEBUG_MODE
           fprintf(stderr,"Creating value table %s\n", str);
#endif
            sp_ftbl_create(pd->sp, &ft, 1);
            sp_gen_vals(pd->sp, ft, args);
            plumber_ftmap_add(pd, str, ft);
            free(str);
            free(args);
            break;

        case PLUMBER_COMPUTE:
            break;

        case PLUMBER_DESTROY:
            break;

        default:
          fprintf(stderr,"Error: Unknown mode!");
           break;
    }
    return PLUMBER_OK;
}
