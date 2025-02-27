#include "differentiator.h"

int print_node(NODE* node, FILE* file_ptr)
{
    assert(node);
    assert(file_ptr);
    if(node->left != NULL)
    {
        printf("in lf\n");
        print_node(node->left, file_ptr);
    }

    if (node->type == VAR)
    {
        //printf("IN var\n");
        printf("%c", 'x');
        fprintf(file_ptr,  "%c", 'x');
    }
    else if (node->type == NUM)
    {
        printf("in num\n");
        //printf("in NUM\n");
        printf("%d", node->value.num_value);
        fprintf(file_ptr, "%d", node->value.num_value);
        printf("after_fprintf\n");
    }
    else if (node->type == SYM)
    {
        //printf("in SYM\n");
        for (int i = 0; i < amount_operations; ++i)
        {
            if (node->value.sym_value == operations[i].code)
            {
                printf("%c", operations[i].name_symbol);
                fprintf(file_ptr, "%c", operations[i].name_symbol);

                break;
            }
        }
    }
    else if (node->type == FUN)
    {
        //printf("in FUN\n");
        for (int i = 0; i < amount_fun; ++i)
        {
            if (node->value.fun_value == funktions[i].code)
            {
                printf("%s", funktions[i].name);
                fprintf(file_ptr, "{%s}", funktions[i].name);
                break;
            }
        }
    }

    if(node->right != NULL)
    {
        printf("rig\n");
        print_node(node->right, file_ptr);
    }

    return 1;
}

void print_latex(NODE* root)
{   
    assert(root);
    FILE* file_ptr = fopen("latex.txt", "w");
    assert(file_ptr);
    printf("in pr_lat\n");
    print_node(root, file_ptr);

}
