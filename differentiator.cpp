#include "differentiator.h"



int main()
{
    CONVERSIONS* conversion = make_conversion();
    tokens_t* arr_token = create_lec(conversion);

    NODE* root = create_tree(conversion, arr_token);
    //DrawTree(root);
    simplifare(root);
    NODE* root_dif = diff(root);
    //DrawTree(root_dif);
    for (int i = 0; i < 5; i++)
    {
        simplifare(root_dif);
    }
    DrawTree(root_dif);
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
    switch(node->value.fun_value)
    {
        case SIN:
        {
            union values value_cos = {};
            value_cos.fun_value = COS;
            value.sym_value = MUL;

            assert(node->left);
            return new_node(SYM, value, new_node(FUN, value_cos, copy_node(node->left), NULL), diff(node->left));
        }
        case COS:
        {
            union values value_cos = {};
            union values value_num = {};
            value_num.num_value = -1;
            value_cos.fun_value = SIN;
            value.sym_value = MUL;


            assert(node->left);
            return new_node(SYM, value, new_node(SYM, value, new_node(NUM, value_num, NULL, NULL), new_node(FUN, value_cos, copy_node(node->left), NULL)), diff(node->left));
        }
        case TG:
        {
            union values value_cos = {};
            union values value_num = {};
            union values value_div = {};
            value_div.sym_value = DIV;
            value_num.num_value = 1;
            value_cos.fun_value = COS;
            value.sym_value = MUL;
            assert(node->left);

            NODE* node_cos = new_node(SYM, value_div, new_node(NUM, value_num, NULL, NULL), new_node(SYM, value, new_node(FUN, value_cos, copy_node(node->left), NULL), new_node(FUN, value_cos, copy_node(node->left), NULL)));
            assert(node->left);
            NODE* dif_in_tg = diff(node->left);
            return new_node(SYM, value, node_cos, dif_in_tg);

        }
        case CTG:
        {
            union values value_sin   = {};
            union values value_num   = {};
            union values value_num_m = {};
            union values value_div   = {};
            value_div.sym_value      = DIV;
            value_num.num_value      = 1;
            value_num_m.num_value    = -1;
            value_sin.fun_value      = SIN;
            value.sym_value          = MUL;
            assert(node->left);

            NODE* node_cos = new_node(SYM, value_div, new_node(NUM, value_num, NULL, NULL), new_node(SYM, value, new_node(FUN, value_sin, copy_node(node->left), NULL), new_node(FUN, value_sin, copy_node(node->left), NULL)));
            assert(node->left);
            NODE* dif_in_tg = diff(node->left);
            return new_node(SYM, value, new_node(NUM, value_num_m, NULL, NULL), new_node(SYM, value, node_cos, dif_in_tg));
        }
        case LN:
        {
            union values value_div = {};
            union values value_num  = {};
            value.sym_value = MUL;
            value_div.sym_value = DIV;
            value_num.num_value = 1;
            assert(node->left);
            return new_node(SYM, value, new_node(SYM, value_div, new_node(NUM, value_num, NULL, NULL), copy_node(node->left)), diff(node->left));

        }
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
                else if(node->right->type == NUM && node->right->value.num_value == 1)
                {
                    NODE* node_r = node->left;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                }
                else if(node->right->type == NUM && node->left->type == NUM)
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
                else if(node->right->type == NUM && node->right->value.num_value == 1)
                {
                    NODE* node_r = node->left;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                }
                else if(node->right->type == NUM && node->left->type == NUM)
                {
                    node->type = NUM;
                    value.num_value = node->left->value.num_value / node->right->value.num_value;
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



