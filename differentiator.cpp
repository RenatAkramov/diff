#include "differentiator.h"



int main()
{
    CONVERSIONS* conversion = make_conversion();
    create_tree_l(conversion);

    NODE* root = create_tree(conversion);
    NODE* root_dif = diff(root);
    for (int i = 0; i < 5; i++)
    {
        simplifare(root_dif);
    }
    DrawTree(root_dif);
    //create_tree_l(conversion);
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
            value_add.sym_value    = ADD;

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





NODE* simplifare(NODE* node)
{
    if (node->type == SYM)
    {
        union values value = {};
        switch(node->value.sym_value)
        {
            case ADD:
            {

                if(node->right->type == NUM && node->left->type == NUM)
                {
                    node->type = NUM;
                    value.num_value = node->right->value.num_value + node->left->value.num_value;
                    node->value = value;

                    node->left = NULL;
                    node->right = NULL;
                }
                break;
            }
            case SUB:
            {
                if(node->right->type == NUM && node->left->type == NUM)
                {
                    node->type = NUM;
                    value.num_value = node->left->value.num_value - node->right->value.num_value;
                    //printf("v1: %d, v2: %d  sub: %d\n",node->right->value.num_value, value.num_value);
                    node->value = value;

                    node->left = NULL;
                    node->right = NULL;
                }
                break;
            }
            case MUL:
            {

                printf("left_value: %d, right_value: %d\n", node->left->value.num_value, node->right->value.num_value);
                if(node->left->type == NUM && node->left->value.num_value == 1)
                {
                    NODE* node_r = node->right;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;

                }
                if(node->right->type == NUM && node->right->value.num_value == 1)
                {
                    NODE* node_r = node->left;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                }
                if(node->right->type == NUM && node->left->type == NUM)
                {
                    node->type = NUM;
                    value.num_value = node->right->value.num_value * node->left->value.num_value;
                    node->value = value;

                    node->left = NULL;
                    node->right = NULL;
                }
                break;
            }
            case DIV:
            {
                if(node->left->type == NUM && node->left->value.num_value == 1)
                {
                    NODE* node_r = node->right;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;

                }
                if(node->right->type == NUM && node->right->value.num_value == 1)
                {
                    NODE* node_r = node->left;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                }
                if(node->right->type == NUM && node->left->type == NUM)
                {
                    node->type = NUM;
                    value.num_value = node->right->value.num_value / node->left->value.num_value;
                    node->value = value;

                    node->left = NULL;
                    node->right = NULL;
                }
                break;
            }
            default:
            {
                printf("ERROR IN simplifare\n");
                break;

            }

        }
    }
    if (node->left != NULL)
    {
        simplifare(node->left);
    }
    if (node->right != NULL)
    {
        simplifare(node->right);
    }
    return node;
}



