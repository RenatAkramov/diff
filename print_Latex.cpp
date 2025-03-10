#include "differentiator.h"

int print_node(NODE* node, FILE* file_l)
{
    assert(node);
    assert(file_l);
    printf("%llx\n", node->hash);
    switch(node->type)
    {
        case SYM:
        {
            for (int i = 0; i < amount_operations; ++i)
            {
                if (node->value.sym_value == operations[i].code)
                {
                    printf("%c\n", operations[i].name_symbol);
                    if (node->value.sym_value == POW)
                    {
                        fprintf(file_l,"(");
                        print_node(node->left, file_l);

                        fprintf(file_l, ")%c{", operations[i].name_symbol);
                        print_node(node->right,file_l);
                        fprintf(file_l, "%c", '}');
                        return 1;

                    }
                    else if(node->value.sym_value == DIV)
                    {
                        fprintf(file_l,"%s" ,"\\frac{");
                        print_node(node->left,file_l);
                        fprintf(file_l, "%s","}{");
                        print_node(node->right, file_l);
                        fprintf(file_l, "%c",'}');
                        return 1;
                    }
                    else if (node->value.sym_value == MUL )
                    {
                        fprintf(file_l, "%c", '(');
                        print_node(node->left, file_l);
                        fprintf(file_l, ")%c(", operations[i].name_symbol);
                        print_node(node->right,file_l);
                        fprintf(file_l, "%c", ')');
                        return 1;
                    }
                    else if (node->value.sym_value == SUB)
                    {
                        fprintf(file_l, "%c", '(');
                        print_node(node->left,file_l);
                        fprintf(file_l, ")%c(", operations[i].name_symbol);
                        print_node(node->right, file_l);
                        fprintf(file_l, "%c", ')');
                        return 1;
                    }
                    else if (node->value.sym_value == ADD)
                    {
                        print_node(node->left, file_l);
                        fprintf(file_l, "%c", operations[i].name_symbol);
                        print_node(node->right, file_l);
                        return 1;
                    }
                    break;
                }
            }    
        }
        case NUM:
        {
            fprintf(file_l, "%d", node->value.num_value);
            return 1;
        }
        case VAR:
        {
            fprintf(file_l, "%c", 'x');
            return 1;
        }
        case FUN:
        {
            for (int i = 0; i < amount_fun; ++i)
            {
                if (node->value.fun_value == funktions[i].code)
                {
                    printf("%s\n", funktions[i].name);
                    fprintf(file_l,"\\%s", funktions[i].name );
                    break;
                }
            }
            fprintf(file_l, "(");
            print_node(node->left, file_l);
            fprintf(file_l, ")");
            return 1;    
        }
    }
    
   
}
void create_latex_simplifare_diff(NODE* root)
{   
    assert(root);
    FILE* file_l = fopen("true_Latex.tex", "w"); 
    assert(file_l);

    fprintf(file_l, "\\documentclass[]{article}\n\\usepackage[utf8x]{inputenc}\n\\usepackage[T2A]{fontenc}\n\\title{differentiator}\n\\author{Akramov Renat}\n\\begin{document}\n\\maketitle\n");
    
    fprintf(file_l, "\\section{Any Soviet kindergarten student knows what to do about it.}\n");
    fprintf(file_l, "%c", '$');
    print_node(root, file_l);

    

    fprintf(file_l, "$\n");
    hash_all(root);
    DrawTree(root);
    
    root = diff(root);
    DrawTree(root);

    fprintf(file_l, "\\section{By differentiating , we get}\n");
    fprintf(file_l, "$");
    print_node(root, file_l);
    fprintf(file_l, "$\n");

    for (int i = 0; i < amount_simplifare; i++)
    {
        simplifare(root, root);
    }
    DrawTree(root);

    fprintf(file_l, "\\section{After simplification}\n");
    fprintf(file_l, "%c", '$');
    print_node(root, file_l);
    fprintf(file_l, "$\n");

    fprintf(file_l, "\n\\end{document}");
    DrawTree(root);
    fclose(file_l);
}
