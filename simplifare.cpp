#include "differentiator.h"

NODE* simplifare(NODE* node, NODE* root)
{
    hash_all(root);
    DrawTree(root);
    printf("hash sim %llx \n", node->hash);
    if (node->type == SYM)
    {

        union values value = {};
        switch(node->value.sym_value)
        {
            case ADD:
            {
                printf("in add\n");
                if(node->left->type == NUM && node->left->value.num_value == 0)
                {
                    printf("f\n");
                    NODE* node_r = node->right;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                }
                else if(node->right->type == NUM && node->right->value.num_value == 0)
                {
                    printf("t\n");
                    NODE* node_r = node->left;
                    assert(node_r);
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                    printf("t after\n");
                    //DrawTree(root);
                }
                else if(node->right->type == NUM && node->left->type == NUM)
                {
                    printf("3\n");
                    node->type = NUM;
                    value.num_value = node->right->value.num_value + node->left->value.num_value;
                    node->value = value;

                    node->left = NULL;
                    node->right = NULL;
                }
                else if(node->left->value.sym_value == ADD || node->left->value.sym_value == SUB)
                {

                    if(node->left->value.sym_value == ADD )
                    {
                        if(node->left->left->type == NUM && node->right->type == NUM)
                        {

                            int arg_1 = node->right->value.num_value;
                            int arg_2 = node->left->left->value.num_value;
                            int arg = arg_1 + arg_2;
                            printf("%d my arg\n", arg);
                            NODE* node_r = node->left;
                            assert(node->left);
                            node->left  = node_r->left;
                            node->right = node_r->right;
                            node->type  = node_r->type;
                            node->value = node_r->value;
                            node->left->value.num_value = arg;
                        }
                        else if(node->left->right->type == NUM && node->right->type == NUM)
                        {
                            int arg_1 = node->right->value.num_value;
                            int arg_2 = node->left->right->value.num_value;
                            int arg = arg_1 + arg_2;
                            NODE* node_r = node->left;
                            assert(node->left);
                            node->left  = node_r->left;
                            node->right = node_r->right;
                            node->type  = node_r->type;
                            node->value = node_r->value;
                            node->left->value.num_value = arg;
                        }
                    }
                    if(node->left->value.sym_value == SUB )
                    {
                        if(node->left->left->type == NUM && node->right->type == NUM)
                        {
                            int arg_1 = node->right->value.num_value;
                            int arg_2 = node->left->left->value.num_value;
                            int arg = arg_1 - arg_2;
                            NODE* node_r = node->left;
                            assert(node->left);
                            node->left  = node_r->left;
                            node->right = node_r->right;
                            node->type  = node_r->type;
                            if (arg > 0)
                            {
                                node->value.sym_value = ADD;
                            }
                            else
                            {
                                node->value.sym_value = SUB;
                            }
                            node->left->value.num_value = arg;
                        }
                        else if(node->left->right->type == NUM && node->right->type == NUM)
                        {
                            int arg_1 = node->right->value.num_value;
                            int arg_2 = node->left->right->value.num_value;
                            int arg = arg_1 - arg_2; NODE* node_r = node->left;
                            assert(node->left);
                            node->left  = node_r->left;
                            node->right = node_r->right;
                            node->type  = node_r->type;
                            if (arg > 0)
                            {
                                node->value.sym_value = ADD;
                            }
                            else
                            {
                                node->value.sym_value = SUB;
                            }
                            node->left->value.num_value = arg;
                        }
                    }


                }
                break;
            }
            case SUB:
            {
                printf("in SUB\n");
                if(node->left->type == NUM && node->left->value.num_value == 0)
                {
                    printf("in 1\n");
                    NODE* node_r = node->right;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                    break;
                }
                else if(node->right->type == NUM && node->right->value.num_value == 0)
                {
                    printf("in 2\n");
                    NODE* node_r = node->left;
                    assert(node_r);
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                    break;
                }
                else if(node->right->type == NUM && node->left->type == NUM)
                {
                    printf("in 3\n");
                    node->type = NUM;
                    value.num_value = node->left->value.num_value - node->right->value.num_value;
                    node->value = value;

                    node->left = NULL;
                    node->right = NULL;
                    DrawTree(root);
                    break;
                }
                else if(node->left->type == SYM)//
                {
                    printf("in my uslovie\n");
                    if(node->left->value.sym_value == ADD )
                    {
                        if(node->left->left->type == NUM && node->right->type == NUM)
                        {
                           int arg_1 = node->right->value.num_value;
                            int arg_2 = node->left->left->value.num_value;
                            int arg = arg_2 - arg_1;
                            NODE* node_r = node->left;
                            node->left  = node_r->left;
                            node->right = node_r->right;
                            node->type  = node_r->type;
                            node->value = node_r->value;
                            if (arg > 0)
                            {
                                node->value.sym_value = ADD;
                            }
                            else
                            {
                                node->value.sym_value = SUB;
                            }
                            node->left->value.num_value = arg;
                            break;
                        }
                        else if(node->left->right->type == NUM && node->right->type == NUM)
                        {
                            int arg_1 = node->right->value.num_value;
                            int arg_2 = node->left->right->value.num_value;
                            int arg = arg_2 - arg_1;
                            NODE* node_r = node->left;
                            node->left  = node_r->left;
                            node->right = node_r->right;
                            node->type  = node_r->type;
                            node->value = node_r->value;
                            if (arg > 0)
                            {
                                node->value.sym_value = ADD;
                            }
                            else
                            {
                                node->value.sym_value = SUB;
                            }
                            node->left->value.num_value = arg;
                            break;
                        }
                    }
                    else if(node->left->value.sym_value == SUB )
                    {
                        if(node->left->left->type == NUM && node->right->type == NUM)
                        {
                            int arg_1 = node->right->value.num_value;
                            int arg_2 = node->left->left->value.num_value;
                            int arg = arg_1 + arg_2;
                            NODE* node_r = node->left;
                            node->left  = node_r->left;
                            node->right = node_r->right;
                            node->type  = node_r->type;
                            node->value = node_r->value;
                            node->left->value.num_value = arg;
                            break;
                        }
                        else if(node->left->right->type == NUM && node->right->type == NUM)
                        {
                            int arg_1 = node->right->value.num_value;
                            int arg_2 = node->left->right->value.num_value;
                            int arg = arg_1 + arg_2;
                            NODE* node_r = node->left;
                            node->left  = node_r->left;
                            node->right = node_r->right;
                            node->type  = node_r->type;
                            node->value = node_r->value;
                            node->left->value.num_value = arg;
                            break;
                        }
                    }
                    //
                break;
            }
            case MUL:
            {
                printf("in MUUUUUUUUUL\n");
                printf("h: %llx\n " , node->hash);
                assert(node->left);
                assert(node->right);
                if(node->left->type == NUM && node->left->value.num_value == 1)
                {
                    printf("m1\n");
                    NODE* node_r = node->right;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                    break;
                }
                else if(node->right->type == NUM && node->right->value.num_value == 1)
                {
                    printf("m2\n");
                    NODE* node_r = node->left;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
                    break;
                }
                else if(node->right->type == NUM && node->left->type == NUM)
                {
                    printf("m3\n");
                    node->type = NUM;
                    value.num_value = node->right->value.num_value * node->left->value.num_value;
                    node->value = value;

                    node->left = NULL;
                    node->right = NULL;
                    break;
                }
                
                printf("after 4 var mul\n");
                break;
            }
            case DIV:
            {
                printf("in DIV\n");
                if(node->right->type == NUM && node->right->value.num_value == 1)
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
            case POW:
            {
                printf("in POW\n");
                if(node->right->value.num_value == 1)
                {
                    NODE* node_r = node->left;
                    node->left  = node_r->left;
                    node->right = node_r->right;
                    node->type  = node_r->type;
                    node->value = node_r->value;
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
    printf("in end fun sim\n");
    if (node->left != NULL)
    {
        simplifare(node->left, root);
    }
    if (node->right != NULL)
    {
        simplifare(node->right, root);
    }
    printf("return\n");
    return node;
    }
    
}

