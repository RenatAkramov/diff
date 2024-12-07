#include "differentiator.h"

NODE* create_tree(CONVERSIONS* conversion)
{
    NODE* root;
    root = GetG(conversion);
    DrawTree(root);
    return root;
}

void spend(NODE* node)
{
    printf("val : %d\n",node->type);
    if (node->left != NULL) spend(node->left);
    if (node->right != NULL) spend(node->right);
}

NODE* GetP(CONVERSIONS* conversion)
{
    if (conversion->s[conversion->p] == '(')
    {
        conversion->p++;
        NODE* val = GetE(conversion);
        if (conversion->s[conversion->p] != ')')
        {
            SyntaxERROR();
        }
        conversion->p++;
        return val;
    }
    else if (conversion->s[conversion->p] == 'x')
    {
        return GetV(conversion);
    }
    else 
    {
        return GetN(conversion);
    }
}

NODE* GetE(CONVERSIONS* conversion)
{
    NODE* val = GetT(conversion);
    while (conversion->s[conversion->p] == '+' || conversion->s[conversion->p] == '-')
    {
        int sym = conversion->s[conversion->p];
        conversion->p++;
        NODE* val_2 = GetT(conversion);
        if (sym == '+')
        {
            values value;
            value.sym_value = ADD;
            val = new_node(SYM, value, val, val_2);
        }
        else
        {
            values value;
            value.sym_value = SUB;
            val = new_node(SYM, value, val, val_2);
        }
    }
    return val;
}

NODE* GetN(CONVERSIONS* conversion)
{
    int val_value = 0;
    int p_old = conversion->p;
    while ('0' <= conversion->s[conversion->p] && conversion->s[conversion->p] <= '9')
    {
        val_value = val_value * 10 + (conversion->s[conversion->p] - '0');
        conversion->p++;
    }
    if (p_old == conversion->p) SyntaxERROR();

    printf("VALUE : %d\n", val_value);
    values value;
    value.num_value = val_value;
    printf("VALUE in union : %d\n", value.num_value);

    NODE* val = new_node(NUM, value, NULL, NULL);
    printf("VALUE in struct : %d\n+", val->value);
    return val;
   
}

NODE* GetT(CONVERSIONS* conversion)
{
    NODE* val = GetP(conversion);
    while (conversion->s[conversion->p] == '*' || conversion->s[conversion->p] == '/')
    {
        int op = conversion->s[conversion->p];
        conversion->p++;
        NODE* val_2 = GetP(conversion);
        if (op == '*')
        {
            values value;
            value.sym_value = MUL;   
            val = new_node(SYM, value, val, val_2);
        }
        else
        {
            values value;
            value.sym_value = DIV;
            val = new_node(SYM, value , val, val_2);
        }
    }
    return val;
}

NODE* GetG(CONVERSIONS* conversion)
{
    printf("Start\n");
    NODE* val = GetE(conversion);

    if (conversion->s[conversion->p] == '$')
    {
        printf("END\n");
        conversion->p++;
        return val;
    }
}

NODE* GetV(CONVERSIONS* conversion)
{
    int p_old = conversion->p;
    if (conversion->s[conversion->p] == 'x')
    {
        values value;
        value.var_value = 'x';
        NODE* val = new_node(VAR, value, NULL, NULL);
        conversion->p++;
        printf("%d %c\n",val->type, val->value);
        return val;
    }
    if (p_old == conversion->p) SyntaxERROR();
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
