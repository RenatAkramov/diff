#ifndef differentiator_h
#define differentiator_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

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
    int fun_value;
};

struct NODE
{
    int type;
    union values value;
    NODE* left;
    NODE* parent;
    NODE* right;
};

struct tokens_t
{
    int type;
    union values value;
    char* name;
    NODE* node;
};



enum type
{
    bracket_left  = 1,
    bracket_right = 2,
    variable_x    = 3,
    SIN    = 4,
    COS    = 5,
    TG     = 6,
    CTG    = 7,
    SYM    = 8,
    NUM    = 9,
    VAR    = 10,
    FUN    = 11,
    MUL    = 12,
    DIV    = 13,
    SUB    = 14,
    LN     = 15,
    ADD    = 17,
    DOLLAR = 18,
};

const int amount_operations = 4;


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

const operations_t operations[amount_operations] = {{'*', MUL}, {'/', DIV}, {'-', SUB}, {'+', ADD}};

struct FUNKTION_T
{
    const char* name;
    int code;
};

const FUNKTION_T funktions[5] = {{"sin", SIN}, {"cos", COS}, {"tg", TG}, {"ctg", CTG}, {"ln", LN}};

NODE* new_node(int type, values value, NODE* vol, NODE* vol2);
NODE* create_tree(CONVERSIONS* conversion, tokens_t* arr_token);
NODE* GetP(CONVERSIONS* conversion, tokens_t* arr_token);
NODE* GetE(CONVERSIONS* conversion, tokens_t* arr_token);
NODE* GetT(CONVERSIONS* conversion, tokens_t* arr_token);
NODE* GetG(CONVERSIONS* conversion, tokens_t* arr_token);
NODE* GetN(CONVERSIONS* conversion, tokens_t* arr_token);
void  SyntaxERROR();
NODE* GetV(CONVERSIONS* conversion, tokens_t* arr_token);
void  spend(NODE* node);
int   DrawTree(NODE* root);
int   DrawNode(NODE* node, FILE* file_ptr);
CONVERSIONS* make_conversion();
NODE* GetF(CONVERSIONS* conversion, tokens_t* arr_token);
NODE* copy_node(NODE* node);
NODE* diff(NODE* node);
NODE* simplifare(NODE* node);
tokens_t* create_lec(CONVERSIONS* conversion);
int create_tokens(int len_buf, CONVERSIONS* conversion, tokens_t* arr_token);


#endif
