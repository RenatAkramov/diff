#include "differentiator.h"



int main()
{
    CONVERSIONS* conversion = make_conversion();
    NODE* root = create_tree(conversion);
    NODE* root1 = diff(root);
    DrawTree(root1);
}


CONVERSIONS* make_conversion()
{
    CONVERSIONS* conversion = (CONVERSIONS*) calloc(1, sizeof(CONVERSIONS));
    conversion->p = 0;
    FILE* file_in = fopen("primer.txt", "r");
    fscanf(file_in, "%s",conversion->s);   
    printf("%s\n", conversion->s);
    fclose(file_in);
    return conversion;
}

NODE* diff(NODE* node)
{
    values value = {};

    if (node->type == NUM)
    {
        value.num_value = 0;
        return new_node(NUM, value, NULL, NULL);
    }
    if (node->type == VAR)
    {
        value.num_value = 1;
        return new_node(NUM, value, NULL, NULL);
    }
    switch(node->value.sym_value)
    {
        case ADD:
        {
            value.sym_value = ADD;
            return new_node(SYM, value, diff(node->left), diff(node->right));
        }
        case SUB:
        {
            value.sym_value = SUB;
            return new_node(SYM, value, diff(node->left), diff(node->right));
        }
        case MUL:
        {
            NODE* dr = diff(node->right);
            NODE* dl = diff(node->left);
            NODE* cl = copy_node(node->left);
            NODE* cr = copy_node(node->right);

            value.sym_value = MUL;

            
            union values value_add = {};
            value_add.sym_value     = ADD;

            return new_node(SYM, value_add, new_node(SYM, value, dl, cr), new_node(SYM, value, cl, dr));
        }
        case DIV:
        {
            NODE* dl = diff(node->left);
            NODE* dr = diff(node->right);

            NODE* cl = copy_node(node->left);
            NODE* cr = copy_node(node->right);

            value.sym_value = MUL;

            union values value_sub = {};
            union values value_div = {};

            value_sub.sym_value = SUB;
            value_div.sym_value = DIV;

            return new_node(SYM, value_div, new_node(SYM, value_sub, new_node(SYM, value, dl, cr), new_node(SYM, value, cl, dr)),new_node(SYM, value, copy_node(cr), copy_node(cr)));
        }
        default:
        {
            printf("ERROR IN DIFF\n");
            return NULL;
        }

    }
}

NODE* copy_node(NODE* node)
{
    if (!node)
    {
        return NULL;
    }

    NODE* copynode =  new_node(node->type, node->value, copy_node(node->left), copy_node(node->right));

    return copynode;

}




/*
CONVERSIONS* simplifare(CONVERSIONS* node)
{

}
*/


