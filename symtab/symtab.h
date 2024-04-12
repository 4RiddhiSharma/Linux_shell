#ifndef SYMTAB_H
#define SYMTAB_H

/* Use hash tables to implement the symbol table struct. Remove this macro,or set it to 0 if you want to use the linked lists implementation instead.*/
#define USE_HASH_TABLES 1

/* the type of a symbol table entry's value */
enum symbol_type
{
    SYM_STR ,       /*shell variable*/
    SYM_FUNC,       
};

/* the symbol table entry structure */
struct symtab_entry_s
{
    char     *name;                   /* key */
    enum      symbol_type val_type;   /* type of value */
    char     *val;                    /* value */
    unsigned  int flags;              /* flags like readonly, export i.e properties that wee assign variables,func */
    struct    symtab_entry_s *next;   /* pointer to the next entry */
    struct    node_s *func_body;      /* for functions, the nodetree of the function body */
};


#ifdef USE_HASH_TABLES

/* using hash tables to implement the symbol table struct */
#include "symtab_hash.h"

#else
/* using linked lists to implement the symbol table struct */
/*structure represents a single symbol table. For starters, we'll use one symbol table, in which we'll define all our shell variables. Later on, when we discuss shell functions and begin working with script files, we'll need to define more symbol tables.The zeroth symbol table will be the global table, in which we'll define our global variables (the ones that are accessible to the shell, and all functions and scripts executed by it).Symbol tables number one and above are the local tables, in which we'll define our local variables (the ones that are only accessible to the shell function or script in which they were declared). By cascading symbol tables in this way, we are effectively implementing variable scoping.*/
    struct symtab_s
    {
        int    level; /*=> 0 for the global symbol table, 1 and above for local symbol tables.*/
        struct symtab_entry_s *first, *last;   /*pointers to the first and last entries in the table's linked list,*/
    };
#endif


/* values for the flags field of struct symtab_entry_s */
#define FLAG_EXPORT         (1 << 0)    /* export entry to forked commands */
#define FLAG_READONLY       (1 << 1)    /* entry is read only */
#define FLAG_CMD_EXPORT     (1 << 2)    /* used temporarily between cmd fork and exec */
#define FLAG_LOCAL          (1 << 3)    /* entry is local (to script or function) */
#define FLAG_ALLCAPS        (1 << 4)    /* convert value to capital letters when assigned */
#define FLAG_ALLSMALL       (1 << 5)    /* convert value to small letters when assigned */
#define FLAG_FUNCTRACE      (1 << 6)    /* enable function tracing (bash, ksh) */
#define FLAG_INTVAL         (1 << 7)    /* assign only integer values (bash) */
#define FLAG_SPECIAL_VAR    (1 << 8)    /* special shell variable, e.g. $TPERIOD or $RANDOM */
#define FLAG_TEMP_VAR       (1 << 9)    /* temp var (used during arithmetic expansion) */

/* the symbol table stack structure */
#define MAX_SYMTAB	256      /* maximum allowed symbol tables in the stack */
struct symtab_stack_s
{
    int    symtab_count;                            /* number of tables in the stack */
    struct symtab_s *symtab_list[MAX_SYMTAB];       /* array of pointers to the tables */
    struct symtab_s *global_symtab, *local_symtab;  /*pointers to the local and global symbol tables*/
};

/* symtab.c (or symtab_hash.c, depending on the used implementation) */
struct symtab_s       *new_symtab(int level);
void                   symtab_stack_add(struct symtab_s *symtab);
struct symtab_s       *symtab_stack_push(void);
struct symtab_s       *symtab_stack_pop(void);
int                    rem_from_symtab(struct symtab_entry_s *entry, struct symtab_s *symtab);
void                   rem_from_any_symtab(struct symtab_entry_s *entry);
struct symtab_entry_s *add_to_any_symtab(char *symbol, struct symtab_s *st);
struct symtab_entry_s *add_to_symtab(char *symbol);
struct symtab_entry_s *do_lookup(char *str, struct symtab_s *symtable);
struct symtab_entry_s *get_local_symtab_entry(char *str);
struct symtab_entry_s *get_symtab_entry(char *str);
struct symtab_s       *get_local_symtab(void);
struct symtab_s       *get_global_symtab(void);
struct symtab_stack_s *get_symtab_stack(void);
void                   init_symtab(void);
void                   dump_local_symtab(void);
void                   free_symtab(struct symtab_s *symtab);
void                   symtab_entry_setval(struct symtab_entry_s *entry, char *val);
void                   merge_global(struct symtab_s *symtab);

#endif
