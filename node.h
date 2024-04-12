#ifndef NODE_H
#define NODE_H
/*this enumeration defines the types of our AST nodes. For now, we only need two types. The first type represents the root node of a simple command's AST, while the second type represents the simple command's child nodes i.e which contain the command name and arguments*/
enum node_type_e
{
    NODE_COMMAND,           /* simple command */
    NODE_VAR,               /* variable name (or simply, a word) */
};

/*represents the types of values we can store in a given node structure. For simple commands, we'll only use strings i.e enumeration type*/
enum val_type_e
{
    VAL_SINT = 1,       /* signed int */
    VAL_UINT,           /* unsigned int */
    VAL_SLLONG,         /* signed long long */
    VAL_ULLONG,         /* unsigned long long */
    VAL_FLOAT,          /* floating point */
    VAL_LDOUBLE,        /* long double */
    VAL_CHR,            /* char */
    VAL_STR,            /* str (char pointer) */
};

/*union represents the value we can store in a given node structure. Each node can have only one type of value, such as a character string or a numeric value. We access the node's value by referencing the appropriate union member */
union symval_u
{
    long               sint;
    unsigned long      uint;
    long long          sllong;
    unsigned long long ullong;
    double             sfloat;
    long double        ldouble;
    char               chr;
    char              *str;
};

/*structure represents an AST node. It contains fields that tell us about the node's type, the type of the node's value, as well as the value itself.*/
struct node_s
{
    enum   node_type_e type;    /* type of this node */
    enum   val_type_e val_type; /* type of this node's val field */
    union  symval_u val;        /* value of this node */
    int    children;            /* number of child nodes */
    struct node_s *first_child; /* first child node */
    struct node_s *next_sibling, *prev_sibling; /* if this is a child node, pointers to prev/next siblings*/
};

struct  node_s *new_node(enum node_type_e type);
void    add_child_node(struct node_s *parent, struct node_s *child);
void    free_node_tree(struct node_s *node);
void    set_node_val_str(struct node_s *node, char *val);

#endif
