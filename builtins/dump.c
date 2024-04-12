#include "../shell.h"
#include "../sym/symtab.h"

int dump(int argc, char **argv)
{
    dump_local_symtab();
    return 0;
}
