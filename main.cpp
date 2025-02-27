#include "differentiator.h"



int main()
{
    CONVERSIONS* conversion = make_conversion();
    tokens_t* arr_token = create_lec(conversion);

    NODE* root = create_tree(conversion, arr_token);
    printf("after create ");

    printf("after first sim\n");
    root = diff(root);
    printf("after dif\n");
    hash_all(root);
    for (int i = 0; i < amount_simplifare; i++)
    {
        printf("bububu\n");
        simplifare(root, root);
    }
    printf("after two sim\n");
    hash_all(root);
    printf("after hash\n");
    DrawTree(root);
    print_latex(root);
}
