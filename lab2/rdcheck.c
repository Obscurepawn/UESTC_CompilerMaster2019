<<<<<<< HEAD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lex.yy.c"

int tok;

bool programme();
bool external_declaration();
bool decl_or_stmt();
bool declarator_list();
bool intstr_list();
bool initializer();
bool declarator();
bool parameter_list();
bool parameter();
bool type();
bool statement();
bool statement_list();
bool expression_statement();
bool expr();
bool cmp_expr();
bool add_expr();
bool mul_expr();
bool primary_expr();
bool expr_list();
bool id_list();
bool advance();

bool error_flag;

int main()
{
    error_flag = true;
    yyin = fopen("test.txt", "r");
    //printf("Please input your programme(press q to quit!):\n");
    advance();
    bool result = programme();
    if (result && error_flag)
        puts("Right!");
    else
        puts("Wrong!");
    return 0;
}

bool advance()
{
    tok = yylex();
    //printf("<%s,%d>\n", yytext, tok);
    // if (tok == 'q')
    //     exit(1);
    if (tok == EOF)
        return false;
    return true;
}

// program
//     : external_declaration
//     | program external_declaration
//     ;
bool programme()
{
    if (external_declaration())
    {
        if (tok != EOF)
        {
            while (1)
            {
                if (external_declaration())
                {
                    if (tok != EOF)
                        continue;
                    else
                        return true;
                }
                else
                    return false;
            }
        }
        else
            return true;
    }
    else
        return false;
}

// external_declaration
//     : type declarator decl_or_stmt
//     ;
bool external_declaration()
{
    if (type())
    {
        if (tok != EOF)
        {
            if (declarator())
            {
                if (tok != EOF)
                {
                    if (decl_or_stmt())
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

// decl_or_stmt
//     : '{' statement_list '}'
//     | '{' '}'
//     | ',' declarator_list ';'
//     | ';'
//     ;
bool decl_or_stmt()
{
    if (tok == '{')
    {
        if (advance())
        {
            if (statement_list())
            {
                if (tok == '}')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else if (tok == '}')
            {
                advance();
                return true;
            }
            else
            {
                error_flag = false;
                printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == ',')
    {
        if (advance())
        {
            if (declarator_list())
            {
                if (tok == ';')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
                return false;
        }
        else
            return false;
    }
    else if (tok == ';')
    {
        advance();
        return true;
    }
    return false;
}

// declarator_list
//     : declarator
//     | declarator_list ',' declarator
//     ;
bool declarator_list()
{
    if (declarator())
    {
        while (1)
        {
            if (tok != EOF)
            {
                if (tok == ',')
                {
                    if (advance())
                    {
                        if (declarator())
                            continue;
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return true;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// intstr_list
//     : initializer
//     | intstr_list ',' initializer
//     ;
bool intstr_list()
{
    if (initializer())
    {
        while (1)
        {
            if (tok != EOF)
            {
                if (tok == ',')
                {
                    if (advance())
                    {
                        if (initializer())
                            continue;
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return true;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// initializer
//     : NUMBER
//     | STRING
//     ;
bool initializer()
{
    if (tok == NUMBER || tok == STRING)
    {
        advance();
        return true;
    }
    return false;
}

// declarator
//     : ID
//     | ID '=' expr
//     | ID '(' parameter_list ')'
//     | ID '(' ')'
//     | ID '[' expr ']'
//     | ID '[' ']'
//     | ID '[' expr ']' '=' '{' intstr_list '}'
//     | ID '[' ']' '=' '{' intstr_list '}'
//     ;
bool declarator()
{
    if (tok == ID)
    {
        if (advance())
        {
            if (tok == '=')
            {
                if (advance())
                {
                    if (expr())
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else if (tok == '(')
            {
                if (advance())
                {
                    if (parameter_list())
                    {
                        if (tok != EOF)
                        {
                            if (tok == ')')
                            {
                                advance();
                                return true;
                            }
                            else
                            {
                                error_flag = false;
                                printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                                return false;
                            }
                        }
                        else
                            return false;
                    }
                    else if (tok == ')')
                    {
                        advance();
                        return true;
                    }
                    else
                    {
                        error_flag = false;
                        printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                        return false;
                    }
                }
                else
                    return false;
            }
            else if (tok == '[')
            {
                if (advance())
                {
                    if (expr())
                    {
                        if (tok == ']')
                        {
                            if (advance())
                            {
                                if (tok == '=')
                                {
                                    if (advance())
                                    {
                                        if (tok == '{')
                                        {
                                            if (advance())
                                            {
                                                if (intstr_list())
                                                {
                                                    if (tok == '}')
                                                    {
                                                        advance();
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        error_flag = false;
                                                        printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                                                        return false;
                                                    }
                                                }
                                                else
                                                    return false;
                                            }
                                            else
                                                return false;
                                        }
                                        else
                                        {
                                            error_flag = false;
                                            printf("expect a '{' in line:%d col:%d\n", yylineno, yycol);
                                            return false;
                                        }
                                    }
                                    else
                                        return false;
                                }
                                else
                                    return true;
                            }
                            else
                                return true;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ']' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else if (tok == ']')
                    {
                        if (advance())
                        {
                            if (tok == '=')
                            {
                                if (advance())
                                {
                                    if (tok == '{')
                                    {
                                        if (advance())
                                        {
                                            if (intstr_list())
                                            {
                                                if (tok == '}')
                                                {
                                                    advance();
                                                    return true;
                                                }
                                                else
                                                {
                                                    error_flag = false;
                                                    printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                                                    return false;
                                                }
                                            }
                                            else
                                                return false;
                                        }
                                        else
                                            return false;
                                    }
                                    else
                                    {
                                        error_flag = false;
                                        printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                                        return false;
                                    }
                                }
                                else
                                    return false;
                            }
                            else
                                return true;
                        }
                        return true;
                    }
                    else
                        return false;
                }
                return false;
            }
            else
                return true;
        }
        else
            return true;
    }
    return false;
}

// parameter_list
//         : parameter
//         | parameter_list ',' parameter
//         ;
bool parameter_list()
{
    if (parameter())
    {
        while (1)
        {
            if (tok == ',')
            {
                if (advance())
                {
                    if (parameter())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// parameter
//         : type ID
//         ;
bool parameter()
{
    if (type())
    {
        if (tok == ID)
        {
            advance();
            return true;
        }
        else
        {
            error_flag = false;
            printf("expect a ID in line:%d col:%d\n", yylineno, yycol);
            return false;
        }
    }
    else
        return false;
}

// type
//         : INT
//         | STR
//         | VOID
//         ;
bool type()
{
    if (tok == INT || tok == STR || tok == VOID)
    {
        advance();
        return true;
    }
    return false;
}

// statement
//     : type declarator_list ';'
//     | '{' statement_list '}'
//     | expr_statement
//     | IF '(' expr ')' statement
//     | IF '(' expr ')' statement ELSE statement
//     | WHILE '(' expr ')' statement
//     | RETURN ';'
//     | RETURN expr ';'
//     | PRINT ';'
//     | PRINT expr_list ';'
//     | SCAN id_list ';'
//     ;
bool statement()
{
    if (type())
    {
        if (declarator_list())
        {
            if (tok == ';')
            {
                advance();
                return true;
            }
            else
            {
                error_flag = false;
                printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == '{')
    {
        if (advance())
        {
            if (statement_list())
            {
                if (tok == '}')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
                return false;
        }
        else
            return false;
    }
    else if (expression_statement())
        return true;
    else if (tok == IF)
    {
        if (advance())
        {
            if (tok == '(')
            {
                if (advance())
                {
                    if (expr())
                    {
                        if (tok == ')')
                        {
                            if (advance())
                            {
                                if (statement())
                                {
                                    if (tok == ELSE)
                                    {
                                        if (advance())
                                        {
                                            if (statement())
                                                return true;
                                            else
                                                return false;
                                        }
                                        else
                                            return false;
                                    }
                                    else
                                        return true;
                                }
                                else
                                    return false;
                            }
                            else
                                return false;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
            {
                error_flag = false;
                printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == WHILE)
    {
        if (advance())
        {
            if (tok == '(')
            {
                if (advance())
                {
                    if (expr())
                    {
                        if (tok == ')')
                        {
                            if (advance())
                            {
                                if (statement())
                                    return true;
                                else
                                    return false;
                            }
                            else
                                return false;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
            {
                error_flag = false;
                printf("expect a '(' in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == RETURN)
    {
        if (advance())
        {
            if (tok == ';')
            {
                advance();
                return true;
            }
            else if (expr())
            {
                if (tok == ';')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
            {
                error_flag = false;
                printf("expect a ';' or a expression in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == PRINT)
    {
        if (advance())
        {
            if (tok == ';')
            {
                advance();
                return true;
            }
            else if (expr_list())
            {
                if (tok == ';')
                {
                    advance();
                    return true;
                }
                else
                    return false;
            }
            else
            {
                error_flag = false;
                printf("expect a ';' or a expression_list in line:%d col:%d\n", yylineno-1, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == SCAN)
    {
        if (advance())
        {
            if (id_list())
            {
                if (tok == ';')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
            {
                error_flag = false;
                printf("expect a ID_list in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else
        return false;
}

// statement_list
//     : statement
//     | statement_list statement
//     ;
bool statement_list()
{
    if (statement())
    {
        while (1)
        {
            if (statement())
                continue;
            else
                return true;
        }
    }
    else
        return false;
}

// expression_statement
//     : ';'
//     | expr ';'
//     ;
bool expression_statement()
{
    if (tok == ';')
    {
        advance();
        return true;
    }
    else if (expr())
    {
        if (tok == ';')
        {
            advance();
            return true;
        }
        else
        {
            error_flag = false;
            printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
            return false;
        }
    }
    else
        return false;
}

// expr
//     : cmp_expr
//     ;
bool expr()
{
    return cmp_expr();
}

// cmp_expr
//     : add_expr
//     | cmp_expr CMP add_expr
//     ;
bool cmp_expr()
{
    if (add_expr())
    {
        while (1)
        {
            if (tok == CMP)
            {
                if (advance())
                {
                    if (add_expr())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// add_expr
//     : mul_expr
//     | add_expr '+' mul_expr
//     | add_expr '-' mul_expr
//     ;
bool add_expr()
{
    if (mul_expr())
    {
        while (1)
        {
            if (tok == '+' || tok == '-')
            {
                if (advance())
                {
                    if (mul_expr())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// mul_expr
//     : primary_expr
//     | mul_expr '*' primary_expr
//     | mul_expr '/' primary_expr
//     | mul_expr '%' primary_expr
//     | '-' primary_expr
//     ;
bool mul_expr()
{
    if (primary_expr())
    {
        while (1)
        {
            if (tok == '*' || tok == '/' || tok == '%')
            {
                if (advance())
                {
                    if (primary_expr())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else if (tok == '-')
    {
        if (advance())
        {
            if (primary_expr())
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

// primary_expr
//     : ID '(' expr_list ')'
//     | ID '(' ')'
//     | '(' expr ')'
//     | ID
//     | NUMBER
//     | STRING
//     | ID ASSIGN expr
//     | ID '=' expr
//     | ID '[' expr ']'
//     | ID '[' expr ']' '=' expr
//     ;
bool primary_expr()
{
    if (tok == ID)
    {
        if (advance())
        {
            if (tok == '(')
            {
                if (advance())
                {
                    if (expr_list)
                    {
                        if (tok == ')')
                        {
                            advance();
                            return true;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else if (tok == ')')
                    {
                        advance();
                        return true;
                    }
                    else
                    {
                        error_flag = false;
                        printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                        return false;
                    }
                }
                else
                    return false;
            }
            else if (tok == '=')
            {
                if (advance())
                {
                    if (expr())
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else if (tok == '[')
            {
                if (advance())
                {
                    if (expr())
                    {
                        if (tok == ']')
                        {
                            if (advance())
                            {
                                if (tok == '=')
                                {
                                    if (advance())
                                    {
                                        if (expr())
                                            return true;
                                        else
                                            return false;
                                    }
                                    else
                                        return false;
                                }
                                else
                                    return true;
                            }
                            else
                                return true;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ']' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else if (tok == ASSIGN)
            {
                if (advance())
                {
                    if (expr())
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
        else
            return true;
    }
    else if (tok == NUMBER)
    {
        advance();
        return true;
    }
    else if (tok == STRING)
    {
        advance();
        return true;
    }
    else if (tok == '(')
    {
        if (advance())
        {
            if (expr())
            {
                if (tok == ')')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

// expr_list
//     : expr
//     | expr_list ',' expr
//     ;
bool expr_list()
{
    if (expr())
    {
        while (1)
        {
            if (tok == ',')
            {
                if (advance())
                {
                    if (expr())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// id_list
//     : ID
//     | id_list ',' ID
//     ;
bool id_list()
{
    if (tok == ID)
    {
        while (1)
        {
            if (advance())
            {
                if (tok == ',')
                {
                    if (advance())
                    {
                        if (tok == ID)
                        {
                            advance();
                            continue;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ID in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else
                    return true;
            }
            else
                return true;
        }
    }
    else
        return false;
=======
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lex.yy.c"

int tok;

bool programme();
bool external_declaration();
bool decl_or_stmt();
bool declarator_list();
bool intstr_list();
bool initializer();
bool declarator();
bool parameter_list();
bool parameter();
bool type();
bool statement();
bool statement_list();
bool expression_statement();
bool expr();
bool cmp_expr();
bool add_expr();
bool mul_expr();
bool primary_expr();
bool expr_list();
bool id_list();
bool advance();

bool error_flag;

int main()
{
    error_flag = true;
    yyin = fopen("test.txt", "r");
    //printf("Please input your programme(press q to quit!):\n");
    advance();
    bool result = programme();
    if (result && error_flag)
        puts("Right!");
    else
        puts("Wrong!");
    return 0;
}

bool advance()
{
    tok = yylex();
    //printf("<%s,%d>\n", yytext, tok);
    // if (tok == 'q')
    //     exit(1);
    if (tok == EOF)
        return false;
    return true;
}

// program
//     : external_declaration
//     | program external_declaration
//     ;
bool programme()
{
    if (external_declaration())
    {
        if (tok != EOF)
        {
            while (1)
            {
                if (external_declaration())
                {
                    if (tok != EOF)
                        continue;
                    else
                        return true;
                }
                else
                    return false;
            }
        }
        else
            return true;
    }
    else
        return false;
}

// external_declaration
//     : type declarator decl_or_stmt
//     ;
bool external_declaration()
{
    if (type())
    {
        if (tok != EOF)
        {
            if (declarator())
            {
                if (tok != EOF)
                {
                    if (decl_or_stmt())
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

// decl_or_stmt
//     : '{' statement_list '}'
//     | '{' '}'
//     | ',' declarator_list ';'
//     | ';'
//     ;
bool decl_or_stmt()
{
    if (tok == '{')
    {
        if (advance())
        {
            if (statement_list())
            {
                if (tok == '}')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else if (tok == '}')
            {
                advance();
                return true;
            }
            else
            {
                error_flag = false;
                printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == ',')
    {
        if (advance())
        {
            if (declarator_list())
            {
                if (tok == ';')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
                return false;
        }
        else
            return false;
    }
    else if (tok == ';')
    {
        advance();
        return true;
    }
    return false;
}

// declarator_list
//     : declarator
//     | declarator_list ',' declarator
//     ;
bool declarator_list()
{
    if (declarator())
    {
        while (1)
        {
            if (tok != EOF)
            {
                if (tok == ',')
                {
                    if (advance())
                    {
                        if (declarator())
                            continue;
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return true;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// intstr_list
//     : initializer
//     | intstr_list ',' initializer
//     ;
bool intstr_list()
{
    if (initializer())
    {
        while (1)
        {
            if (tok != EOF)
            {
                if (tok == ',')
                {
                    if (advance())
                    {
                        if (initializer())
                            continue;
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return true;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// initializer
//     : NUMBER
//     | STRING
//     ;
bool initializer()
{
    if (tok == NUMBER || tok == STRING)
    {
        advance();
        return true;
    }
    return false;
}

// declarator
//     : ID
//     | ID '=' expr
//     | ID '(' parameter_list ')'
//     | ID '(' ')'
//     | ID '[' expr ']'
//     | ID '[' ']'
//     | ID '[' expr ']' '=' '{' intstr_list '}'
//     | ID '[' ']' '=' '{' intstr_list '}'
//     ;
bool declarator()
{
    if (tok == ID)
    {
        if (advance())
        {
            if (tok == '=')
            {
                if (advance())
                {
                    if (expr())
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else if (tok == '(')
            {
                if (advance())
                {
                    if (parameter_list())
                    {
                        if (tok != EOF)
                        {
                            if (tok == ')')
                            {
                                advance();
                                return true;
                            }
                            else
                            {
                                error_flag = false;
                                printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                                return false;
                            }
                        }
                        else
                            return false;
                    }
                    else if (tok == ')')
                    {
                        advance();
                        return true;
                    }
                    else
                    {
                        error_flag = false;
                        printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                        return false;
                    }
                }
                else
                    return false;
            }
            else if (tok == '[')
            {
                if (advance())
                {
                    if (expr())
                    {
                        if (tok == ']')
                        {
                            if (advance())
                            {
                                if (tok == '=')
                                {
                                    if (advance())
                                    {
                                        if (tok == '{')
                                        {
                                            if (advance())
                                            {
                                                if (intstr_list())
                                                {
                                                    if (tok == '}')
                                                    {
                                                        advance();
                                                        return true;
                                                    }
                                                    else
                                                    {
                                                        error_flag = false;
                                                        printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                                                        return false;
                                                    }
                                                }
                                                else
                                                    return false;
                                            }
                                            else
                                                return false;
                                        }
                                        else
                                        {
                                            error_flag = false;
                                            printf("expect a '{' in line:%d col:%d\n", yylineno, yycol);
                                            return false;
                                        }
                                    }
                                    else
                                        return false;
                                }
                                else
                                    return true;
                            }
                            else
                                return true;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ']' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else if (tok == ']')
                    {
                        if (advance())
                        {
                            if (tok == '=')
                            {
                                if (advance())
                                {
                                    if (tok == '{')
                                    {
                                        if (advance())
                                        {
                                            if (intstr_list())
                                            {
                                                if (tok == '}')
                                                {
                                                    advance();
                                                    return true;
                                                }
                                                else
                                                {
                                                    error_flag = false;
                                                    printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                                                    return false;
                                                }
                                            }
                                            else
                                                return false;
                                        }
                                        else
                                            return false;
                                    }
                                    else
                                    {
                                        error_flag = false;
                                        printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                                        return false;
                                    }
                                }
                                else
                                    return false;
                            }
                            else
                                return true;
                        }
                        return true;
                    }
                    else
                        return false;
                }
                return false;
            }
            else
                return true;
        }
        else
            return true;
    }
    return false;
}

// parameter_list
//         : parameter
//         | parameter_list ',' parameter
//         ;
bool parameter_list()
{
    if (parameter())
    {
        while (1)
        {
            if (tok == ',')
            {
                if (advance())
                {
                    if (parameter())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// parameter
//         : type ID
//         ;
bool parameter()
{
    if (type())
    {
        if (tok == ID)
        {
            advance();
            return true;
        }
        else
        {
            error_flag = false;
            printf("expect a ID in line:%d col:%d\n", yylineno, yycol);
            return false;
        }
    }
    else
        return false;
}

// type
//         : INT
//         | STR
//         | VOID
//         ;
bool type()
{
    if (tok == INT || tok == STR || tok == VOID)
    {
        advance();
        return true;
    }
    return false;
}

// statement
//     : type declarator_list ';'
//     | '{' statement_list '}'
//     | expr_statement
//     | IF '(' expr ')' statement
//     | IF '(' expr ')' statement ELSE statement
//     | WHILE '(' expr ')' statement
//     | RETURN ';'
//     | RETURN expr ';'
//     | PRINT ';'
//     | PRINT expr_list ';'
//     | SCAN id_list ';'
//     ;
bool statement()
{
    if (type())
    {
        if (declarator_list())
        {
            if (tok == ';')
            {
                advance();
                return true;
            }
            else
            {
                error_flag = false;
                printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == '{')
    {
        if (advance())
        {
            if (statement_list())
            {
                if (tok == '}')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a '}' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
                return false;
        }
        else
            return false;
    }
    else if (expression_statement())
        return true;
    else if (tok == IF)
    {
        if (advance())
        {
            if (tok == '(')
            {
                if (advance())
                {
                    if (expr())
                    {
                        if (tok == ')')
                        {
                            if (advance())
                            {
                                if (statement())
                                {
                                    if (tok == ELSE)
                                    {
                                        if (advance())
                                        {
                                            if (statement())
                                                return true;
                                            else
                                                return false;
                                        }
                                        else
                                            return false;
                                    }
                                    else
                                        return true;
                                }
                                else
                                    return false;
                            }
                            else
                                return false;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
            {
                error_flag = false;
                printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == WHILE)
    {
        if (advance())
        {
            if (tok == '(')
            {
                if (advance())
                {
                    if (expr())
                    {
                        if (tok == ')')
                        {
                            if (advance())
                            {
                                if (statement())
                                    return true;
                                else
                                    return false;
                            }
                            else
                                return false;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
            {
                error_flag = false;
                printf("expect a '(' in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == RETURN)
    {
        if (advance())
        {
            if (tok == ';')
            {
                advance();
                return true;
            }
            else if (expr())
            {
                if (tok == ';')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
            {
                error_flag = false;
                printf("expect a ';' or a expression in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == PRINT)
    {
        if (advance())
        {
            if (tok == ';')
            {
                advance();
                return true;
            }
            else if (expr_list())
            {
                if (tok == ';')
                {
                    advance();
                    return true;
                }
                else
                    return false;
            }
            else
            {
                error_flag = false;
                printf("expect a ';' or a expression_list in line:%d col:%d\n", yylineno-1, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else if (tok == SCAN)
    {
        if (advance())
        {
            if (id_list())
            {
                if (tok == ';')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
            {
                error_flag = false;
                printf("expect a ID_list in line:%d col:%d\n", yylineno, yycol);
                return false;
            }
        }
        else
            return false;
    }
    else
        return false;
}

// statement_list
//     : statement
//     | statement_list statement
//     ;
bool statement_list()
{
    if (statement())
    {
        while (1)
        {
            if (statement())
                continue;
            else
                return true;
        }
    }
    else
        return false;
}

// expression_statement
//     : ';'
//     | expr ';'
//     ;
bool expression_statement()
{
    if (tok == ';')
    {
        advance();
        return true;
    }
    else if (expr())
    {
        if (tok == ';')
        {
            advance();
            return true;
        }
        else
        {
            error_flag = false;
            printf("expect a ';' in line:%d col:%d\n", yylineno, yycol);
            return false;
        }
    }
    else
        return false;
}

// expr
//     : cmp_expr
//     ;
bool expr()
{
    return cmp_expr();
}

// cmp_expr
//     : add_expr
//     | cmp_expr CMP add_expr
//     ;
bool cmp_expr()
{
    if (add_expr())
    {
        while (1)
        {
            if (tok == CMP)
            {
                if (advance())
                {
                    if (add_expr())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// add_expr
//     : mul_expr
//     | add_expr '+' mul_expr
//     | add_expr '-' mul_expr
//     ;
bool add_expr()
{
    if (mul_expr())
    {
        while (1)
        {
            if (tok == '+' || tok == '-')
            {
                if (advance())
                {
                    if (mul_expr())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// mul_expr
//     : primary_expr
//     | mul_expr '*' primary_expr
//     | mul_expr '/' primary_expr
//     | mul_expr '%' primary_expr
//     | '-' primary_expr
//     ;
bool mul_expr()
{
    if (primary_expr())
    {
        while (1)
        {
            if (tok == '*' || tok == '/' || tok == '%')
            {
                if (advance())
                {
                    if (primary_expr())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else if (tok == '-')
    {
        if (advance())
        {
            if (primary_expr())
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

// primary_expr
//     : ID '(' expr_list ')'
//     | ID '(' ')'
//     | '(' expr ')'
//     | ID
//     | NUMBER
//     | STRING
//     | ID ASSIGN expr
//     | ID '=' expr
//     | ID '[' expr ']'
//     | ID '[' expr ']' '=' expr
//     ;
bool primary_expr()
{
    if (tok == ID)
    {
        if (advance())
        {
            if (tok == '(')
            {
                if (advance())
                {
                    if (expr_list)
                    {
                        if (tok == ')')
                        {
                            advance();
                            return true;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else if (tok == ')')
                    {
                        advance();
                        return true;
                    }
                    else
                    {
                        error_flag = false;
                        printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                        return false;
                    }
                }
                else
                    return false;
            }
            else if (tok == '=')
            {
                if (advance())
                {
                    if (expr())
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else if (tok == '[')
            {
                if (advance())
                {
                    if (expr())
                    {
                        if (tok == ']')
                        {
                            if (advance())
                            {
                                if (tok == '=')
                                {
                                    if (advance())
                                    {
                                        if (expr())
                                            return true;
                                        else
                                            return false;
                                    }
                                    else
                                        return false;
                                }
                                else
                                    return true;
                            }
                            else
                                return true;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ']' in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else if (tok == ASSIGN)
            {
                if (advance())
                {
                    if (expr())
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
        else
            return true;
    }
    else if (tok == NUMBER)
    {
        advance();
        return true;
    }
    else if (tok == STRING)
    {
        advance();
        return true;
    }
    else if (tok == '(')
    {
        if (advance())
        {
            if (expr())
            {
                if (tok == ')')
                {
                    advance();
                    return true;
                }
                else
                {
                    error_flag = false;
                    printf("expect a ')' in line:%d col:%d\n", yylineno, yycol);
                    return false;
                }
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

// expr_list
//     : expr
//     | expr_list ',' expr
//     ;
bool expr_list()
{
    if (expr())
    {
        while (1)
        {
            if (tok == ',')
            {
                if (advance())
                {
                    if (expr())
                        continue;
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return true;
        }
    }
    else
        return false;
}

// id_list
//     : ID
//     | id_list ',' ID
//     ;
bool id_list()
{
    if (tok == ID)
    {
        while (1)
        {
            if (advance())
            {
                if (tok == ',')
                {
                    if (advance())
                    {
                        if (tok == ID)
                        {
                            advance();
                            continue;
                        }
                        else
                        {
                            error_flag = false;
                            printf("expect a ID in line:%d col:%d\n", yylineno, yycol);
                            return false;
                        }
                    }
                    else
                        return false;
                }
                else
                    return true;
            }
            else
                return true;
        }
    }
    else
        return false;
>>>>>>> 8dad9ee129215d834500947d610d65c5aead218d
}