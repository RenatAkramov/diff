#include "differentiator.h"


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
            NODE* node_one = new_node(SYM, value, new_node(FUN, value_cos, copy_node(node->left), NULL), new_node(FUN, value_cos, copy_node(node->left), NULL));
            NODE* node_two = new_node(SYM, value_div, new_node(NUM, value_num, NULL, NULL), node_one);
            return new_node(SYM, value, node_two, diff(node->left));

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
        case EXP:
        {
            value.sym_value = MUL;
            return new_node(SYM, value, copy_node(node), diff(node->left));
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
        case POW:
        {
            union values value_mul = {};
            union values value_add = {};
            union values value_ln  = {};
            union values value_pow = {};
            union values value_sub = {};
            union values value_num = {};
            value_num.num_value = 1;
            value_sub.sym_value = SUB;
            value_mul.sym_value = MUL;
            value_add.sym_value = ADD;
            value_ln.fun_value  = LN;
            value_pow.fun_value = POW;

            NODE* node_copy_os = copy_node(node->left);
            NODE* node_copy_st = copy_node(node->right);
            NODE* node_diff_os = diff(node->left);
            NODE* node_diff_st = diff(node->right);
            NODE* node_1 = new_node(SYM, value_sub, copy_node(node_copy_st), new_node(NUM, value_num, NULL, NULL));
            NODE* node_2 = new_node(SYM, value_pow, copy_node(node_copy_os), node_1);
            NODE* node_3 = new_node(SYM, value_mul, copy_node(node_copy_st), node_2);
            NODE* node_4 = new_node(SYM, value_mul, node_3,copy_node(node_diff_os));
            NODE* node_5 = copy_node(node);
            NODE* node_6 = new_node(FUN, value_ln, copy_node(node_copy_os), NULL);
            NODE* node_7 = new_node(SYM, value_mul, node_5, node_6);
            NODE* node_8 = new_node(SYM, value_mul, node_7, copy_node(node_diff_st));
            NODE* node_9 = new_node(SYM, value_add, node_4, node_8);
            printf("in dif draw\n");
            DrawTree(node_9);
            return node_9;

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









