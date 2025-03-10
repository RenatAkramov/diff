#include "differentiator.h"



int main()
{
    CONVERSIONS* conversion = make_conversion();
    tokens_t* arr_token = create_lec(conversion);

    NODE* root = create_tree(conversion, arr_token);

    hash_all(root);
    create_latex_simplifare_diff(root);

}
