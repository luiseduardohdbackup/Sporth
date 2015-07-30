#include <soundpipe.h>
#include "sporth.h"

enum {
PLUMBER_CREATE,
PLUMBER_COMPUTE,
PLUMBER_DESTROY,
PLUMBER_OK,
PLUMBER_NOTOK
};

typedef struct plumber_pipe {
    uint32_t type;
    size_t size;
    void *ud;
    struct plumber_pipe *next;
} plumber_pipe;

typedef struct plumber_data {
    int mode;
    sp_data *sp;
    sporth_data sporth;
    sp_ftbl tbl_stack[32];
    uint32_t npipes;
    plumber_pipe root;
    plumber_pipe *last;
} plumber_data;

int plumber_init(plumber_data *plumb);
int plumber_clean(plumber_data *plumb);
int plumber_add_float(plumber_data *plumb, float num);
int plumber_add_module(plumber_data *plumb, 
        uint32_t id, size_t size, void *ud);
int plumber_parse(plumber_data *plumb, int mode);