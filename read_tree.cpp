#include "differentiator.h"

NODE* create_tree(CONVERSIONS* conversion, tokens_t* arr_token)
{
    NODE* root;
    root = GetG(conversion, arr_token);
    //simplifare(root);
    return root;
}

void spend(NODE* node)
{
    printf("val : %d\n",node->type);
    if (node->left != NULL) spend(node->left);
    if (node->right != NULL) spend(node->right);
}

NODE* GetP(CONVERSIONS* conversion, tokens_t* arr_token)
{
    if (arr_token[conversion->p].value.sym_value == bracket_left)
    {
        conversion->p++;
        NODE* val = GetE(conversion, arr_token);
        if (arr_token[conversion->p].value.sym_value != bracket_right)
        {
            SyntaxERROR();
        }
        conversion->p++;
        return val;
    }
    else if (arr_token[conversion->p].value.var_value == variable_x)
    {
        return GetV(conversion, arr_token);
    }
    else if(arr_token[conversion->p].value.num_value == NUM)
    {
        printf("in P NUM\n");
        return GetN(conversion, arr_token);
    }
    else if(arr_token[conversion->p].value.fun_value == SIN || arr_token[conversion->p].value.fun_value == COS || arr_token[conversion->p].value.fun_value == TG || arr_token[conversion->p].value.fun_value == CTG || arr_token[conversion->p].value.fun_value == LN)
    {
        return GetF(conversion, arr_token);
    }
}

NODE* GetE(CONVERSIONS* conversion, tokens_t* arr_token)
{
    NODE* val = GetT(conversion, arr_token);
    while (arr_token[conversion->p].value.sym_value == ADD || arr_token[conversion->p].value.sym_value == SUB)
    {
        int p_old = conversion->p;
        conversion->p++;
        NODE* val_2 = GetT(conversion, arr_token);
        if (arr_token[p_old].value.sym_value == ADD)
        {
            values value;
            value.sym_value = ADD;
            val = new_node(SYM, value, val, val_2);
        }
        else if(arr_token[p_old].value.sym_value == SUB)
        {
            values value;
            value.sym_value = SUB;
            val = new_node(SYM, value, val, val_2);
        }
    }
    return val;
}

NODE* GetN(CONVERSIONS* conversion, tokens_t* arr_token)
{
    int val_value = 0;
    int j = 0;
    while ('0' <= arr_token[conversion->p].name[j] && arr_token[conversion->p].name[j] <= '9')
    {
        val_value = val_value * 10 + (arr_token[conversion->p].name[j]- '0');
        j++;
    }
    if (j == 0) SyntaxERROR();

    conversion->p++;
    values value;
    value.num_value = val_value;

    NODE* val = new_node(NUM, value, NULL, NULL);
    return val;

}

NODE* GetT(CONVERSIONS* conversion, tokens_t* arr_token)
{
    NODE* val = GetP(conversion, arr_token);
    //printf("gett con p: %d\n", conversion->p);
    while (arr_token[conversion->p].value.sym_value == MUL || arr_token[conversion->p].value.sym_value == DIV)
    {
        int p_old = conversion->p;
        conversion->p++;
        NODE* val_2 = GetP(conversion, arr_token);
        printf("tok: %d, mul: %d, gett con p: %d\n", arr_token[conversion->p].value.sym_value, MUL, conversion->p);
        if (arr_token[p_old].value.sym_value == MUL)
        {
            values value;
            value.sym_value = MUL;
            val = new_node(SYM, value, val, val_2);
        }
        else if (arr_token[p_old].value.sym_value == DIV)
        {
            values value;
            value.sym_value = DIV;
            val = new_node(SYM, value , val, val_2);
        }
        //conversion->p++;//!!!!!!!!!!!!!!!!!!!!!
    }
    return val;
}

NODE* GetG(CONVERSIONS* conversion, tokens_t* arr_token)
{
    printf("Start\n");
    NODE* val = GetE(conversion, arr_token);

    if (arr_token[conversion->p].value.sym_value == DOLLAR)
    {
        printf("END\n");
        conversion->p++;
        return val;
    }
}

NODE* GetV(CONVERSIONS* conversion, tokens_t* arr_token)
{
    int p_old = conversion->p;
    if (arr_token[conversion->p].value.var_value == variable_x)
    {
        values value;
        value.var_value = variable_x;
        NODE* val = new_node(VAR, value, NULL, NULL);
        conversion->p++;

        return val;
    }
    if (p_old == conversion->p) SyntaxERROR();
}

NODE* GetF(CONVERSIONS* conversion, tokens_t* arr_token)
{
    values value;
    printf("in fffffff do\n");
    value.fun_value = arr_token[conversion->p].value.fun_value;
    conversion->p++;
    printf("in fffffff do\n");
    NODE* val = GetP(conversion, arr_token);
    val = new_node(FUN, value, val, NULL);
    return val;


}

void  SyntaxERROR()
{
    printf("ERROR");
    exit(0);
}

NODE* new_node(int type, values value, NODE* vol, NODE* vol2)
{
   NODE*  node = (NODE*) calloc(1, sizeof(NODE));
   node->type  = type;
   node->value = value;
   node->left  = vol;
   node->right = vol2;
   return node;
}
