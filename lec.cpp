#include "differentiator.h"


tokens_t* create_lec(CONVERSIONS* conversion)
{
    int len_buf = strlen(conversion->s);
    //printf("len_buf: %d\n", len_buf);
    tokens_t* arr_token = (tokens_t*) calloc(len_buf, sizeof(tokens_t));
    for (int i = 0; i < len_buf; i++)
    {
        arr_token[i].name = (char*) calloc(100, sizeof(char));
    }
    create_tokens(len_buf, conversion, arr_token);
    //printf("LEC OK: %d\n", arr_token[1]. name);
    for (int i = 0; i < len_buf; i++)
    {
        printf("%s", arr_token[i].name);
    }
    printf("\n");
    return arr_token;
}



int create_tokens(int len_buf, CONVERSIONS* conversion, tokens_t* arr_token)
{
    for (int i = 0; i < len_buf;)
    {
        values value = {};
        //printf("i: %d p: %d\n", i, conversion->p);
        if(conversion->s[i] == ' ')
        {
            i++;
        }
        else if (conversion->s[i] == '^')
        {
            value.sym_value = POW;
            arr_token[conversion->p].name = "^";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '(')
        {
            value.sym_value = bracket_left;
            arr_token[conversion->p].name = "(";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == 'x')
        {
            value.var_value = variable_x;
            arr_token[conversion->p].name = "x";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == ')')
        {
            value.sym_value = bracket_right;
            arr_token[conversion->p].value = value;
            arr_token[conversion->p].name = ")";
            conversion->p++;
            i++;
        }
        else if(isdigit(conversion->s[i]))
        {
            int ch = 0, j = 0;
            while (isdigit(conversion->s[i]))
            {
                assert(arr_token[conversion->p].name);
                arr_token[conversion->p].name[j] = conversion->s[i];
                i++;
                j++;
            }
            value.num_value = NUM;
            arr_token[conversion->p].value = value;
            conversion->p++;
        }
        else if(conversion->s[i] == '+')
        {
            value.sym_value = ADD;
            arr_token[conversion->p].name = "+";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '-')
        {
            value.sym_value = SUB;
            arr_token[conversion->p].name = "-";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '*')
        {
            value.sym_value = MUL;
            arr_token[conversion->p].name = "*";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '/')
        {
            value.sym_value = DIV;
            arr_token[conversion->p].name = "/";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == '$')
        {
            value.sym_value = DOLLAR;
            arr_token[conversion->p].name = "$";
            arr_token[conversion->p].value = value;
            conversion->p++;
            i++;
        }
        else if(conversion->s[i] == 's' && conversion->s[i + 1] == 'i' && conversion->s[i + 2] == 'n')
        {
            value.fun_value = SIN;
            arr_token[conversion->p].name[0] = 's';
            arr_token[conversion->p].name[1] = 'i';
            arr_token[conversion->p].name[2] = 'n';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        else if(conversion->s[i] == 'c' && conversion->s[i + 1] == 'o' && conversion->s[i + 2] == 's')
        {
            value.fun_value = COS;
            arr_token[conversion->p].name[0] = 'c';
            arr_token[conversion->p].name[1] = 'o';
            arr_token[conversion->p].name[2] = 's';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        else if(conversion->s[i] == 't' && conversion->s[i + 1] == 'g')
        {
            value.fun_value = TG;
            arr_token[conversion->p].name[0] = 't';
            arr_token[conversion->p].name[1] = 'g';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 2;
        }
        else if(conversion->s[i] == 'c' && conversion->s[i + 1] == 't' && conversion->s[i + 2] == 'g')
        {
            value.fun_value = CTG;
            arr_token[conversion->p].name[0] = 'c';
            arr_token[conversion->p].name[1] = 't';
            arr_token[conversion->p].name[2] = 'g';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        else if(conversion->s[i] == 'l' && conversion->s[i + 1] == 'n')
        {
            value.fun_value = LN;
            arr_token[conversion->p].name[0] = 'l';
            arr_token[conversion->p].name[1] = 'n';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 2;
        }
        else if(conversion->s[i] == 'e' && conversion->s[i + 1] == 'x' && conversion->s[i + 2] == 'p')
        {
            value.fun_value = EXP;
            arr_token[conversion->p].name[0] = 'e';
            arr_token[conversion->p].name[1] = 'x';
            arr_token[conversion->p].name[2] = 'p';
            arr_token[conversion->p].value   = value;
            conversion->p++;
            i = i + 3;
        }
        if(conversion->p - 2 >= 0)
        {
            printf("before: %s now: %s\n", arr_token[conversion->p - 2].name, arr_token[conversion->p - 1].name);
        }
    }
    printf("lec OK\n");
    conversion->p = 0;
    return 1;
}
