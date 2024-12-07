#ifndef differentiator_h
#define differentiator_h


#include <stdio.h>
#include <stdlib.h>

struct CONVERSIONS
{
    char s[999];
    int p;
};

union values
{
    int num_value;
    int var_value;
    int sym_value;
};

struct NODE
{
    int type;
    union values value;
    NODE* left;
    NODE* parent;
    NODE* right;
};

enum operations
{
    MUL = 1,
    DIV = 2,
    SUB = 3,
    ADD = 4
};

enum variable
{
    X = 1
};

const int amount_operations = 4;


enum type
{
    SYM  = 1,
    NUM  = 2,
    VAR  = 3
};

struct operations_t
{
    char name_symbol;
    int code;
};

enum errorcode
{
    ERROR_E = 0,
    ERROR_P = 1,
    ERROR_N = 2,
    ERROR_T = 3,
    ERROR_G = 4
};

const operations_t operations[amount_operations] = {{'*', 1}, {'/', 2}, {'-', 3}, {'+', 4}};

/*struct token
{
    
};*/


NODE* new_node(int type, values value, NODE* vol, NODE* vol2);

NODE* create_tree(CONVERSIONS* conversion);

NODE* GetP(CONVERSIONS* conversion);
NODE* GetE(CONVERSIONS* conversion);
NODE* GetT(CONVERSIONS* conversion);
NODE* GetG(CONVERSIONS* conversion);
NODE* GetN(CONVERSIONS* conversion);
void  SyntaxERROR();
NODE* GetV(CONVERSIONS* conversion);
void  spend(NODE* node);
int   DrawTree(NODE* root);
int   DrawNode(NODE* node, FILE* file_ptr);
CONVERSIONS* make_conversion();
NODE* copy_node(NODE* node);
NODE* diff(NODE* node);


#endif