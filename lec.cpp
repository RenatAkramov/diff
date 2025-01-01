#include "differentiator.h"

void create_tree_l(CONVERSIONS* conversion)
{
    int len_buf = strlen(conversion->s);
    printf("len_buf: %d\n", len_buf);
    tokens_t* arr_token = (tokens_t*) calloc(len_buf, sizeof(tokens_t));
    create_tokens(len_buf, conversion, arr_token);
    printf("LEC OK %c\n", arr_token[1]. name);
    for (int i = 0; i < len_buf; i++)
    {
        printf("%s", arr_token[i].name);
    }
    printf("\n");
}



int create_tokens(int len_buf, CONVERSIONS* conversion, tokens_t* arr_token)
{
    for (int i = 0; i < len_buf;)
    {
        printf("i: %d p: %d\n", i, conversion->p);
        if(conversion->s[i] == ' ')
        {
            i++;
        }
        else if(conversion->s[i] == '(')
        {
            printf("PEPEPEPEP\n");
            arr_token[conversion->p].name = "(";
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == 'x')
        {
            arr_token[conversion->p].name = "x";
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == ')')
        {
            arr_token[conversion->p].name = ")";
            conversion->p++;
            i++;
        }
        else if(isdigit(conversion->s[i]))
        {
            int ch = 0;
            while(isdigit(conversion->s[i]))
            {
                ch = ch * 10 + conversion->s[i] - '0';
                i++;
            }
            char str[100];
            sprintf(str, "%d", ch);
            arr_token[conversion->p].name = str;
            printf("in num after str: %s\n", arr_token[conversion->p].name);
            conversion->p++;
        }
        else if(conversion->s[i] == '+')
        {
            arr_token[conversion->p].name = "+";
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '-')
        {
            arr_token[conversion->p].name = "-";
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '*')
        {
            arr_token[conversion->p].name = "*";
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '/')
        {
            arr_token[conversion->p].name = "/";
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '$')
        {
            arr_token[conversion->p].name = "$";
            conversion->p++;
            i++;
            break;
        }
    }
    printf("lec OK\n");
    conversion->p = 0;
    return 1;
}
