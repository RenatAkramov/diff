#include "differentiator.h"

#define fun_for_F(arg) arr_token[conversion->p].value.fun_value == arg

unsigned long long hash_func(int val, NODE* node)
{
    unsigned long long hash_calculation = 0x1505;
    int value = val + (int) node;
    hash_calculation = ((hash_calculation << 5) + hash_calculation) ^ (value); /* hash * 33 + c */
    
    return hash_calculation;

}    

void hash_all(NODE* val)
{
   
    assert(val);
    if (val->type == FUN)
    {
        hash_fun;
    }
    else if (val->type == NUM)
    {
        hash_num;
    }
    else if (val->type == SYM)
    {
        
        hash_sym;
    }
    else if (val->type == VAR)
    {
        hash_var;
    }

    if (val->left != NULL)
    {
        hash_all(val->left);
    }

    if (val->right != NULL)
    {
        hash_all(val->right);
    }
}

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
    else if(fun_for_F(SIN) || fun_for_F(COS) || fun_for_F(TG) || fun_for_F(CTG) || fun_for_F(LN) || fun_for_F(EXP))
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
            hash_sym;
        }
        else if(arr_token[p_old].value.sym_value == SUB)
        {
            values value;
            value.sym_value = SUB;
            val = new_node(SYM, value, val, val_2);
            hash_sym;
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
    hash_num;
    return val;

}

NODE* GetT(CONVERSIONS* conversion, tokens_t* arr_token)
{
    NODE* val = GetC(conversion, arr_token);
    //printf("gett con p: %d\n", conversion->p);
    while (arr_token[conversion->p].value.sym_value == MUL || arr_token[conversion->p].value.sym_value == DIV)
    {
        int p_old = conversion->p;
        conversion->p++;
        NODE* val_2 = GetC(conversion, arr_token);
        printf("tok: %d, mul: %d, gett con p: %d\n", arr_token[conversion->p].value.sym_value, MUL, conversion->p);
        if (arr_token[p_old].value.sym_value == MUL)
        {
            values value;
            value.sym_value = MUL;
            val = new_node(SYM, value, val, val_2);
            hash_sym;
        }
        else if (arr_token[p_old].value.sym_value == DIV)
        {
            values value;
            value.sym_value = DIV;
            val = new_node(SYM, value , val, val_2);
            hash_sym;
        }
        //conversion->p++;//!!!!!!!!!!!!!!!!!!!!!
    }
    return val;
}

NODE* GetC(CONVERSIONS* conversion, tokens_t* arr_token)
{
    NODE* val = GetP(conversion, arr_token);
    while(arr_token[conversion->p].value.sym_value == POW)
    {
        conversion->p++;
        NODE* val_2 = GetP(conversion, arr_token);

        values value;
        value.sym_value = POW;
        val = new_node(SYM, value, val, val_2);
        hash_sym;
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
        hash_var;
        return val;
    }
    if (p_old == conversion->p) SyntaxERROR();
}

NODE* GetF(CONVERSIONS* conversion, tokens_t* arr_token)
{
    values value;
    value.fun_value = arr_token[conversion->p].value.fun_value;
    conversion->p++;
    NODE* val = GetP(conversion, arr_token);
    val = new_node(FUN, value, val, NULL);
    hash_fun;
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
