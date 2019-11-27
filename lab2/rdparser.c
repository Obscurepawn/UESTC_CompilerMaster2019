<<<<<<< HEAD
#include <stdlib.h>
#include <stdbool.h>
#include "lex.yy.c"

int tok;

typedef struct AST ast;
typedef struct AST *ptrast;
struct AST
{
    char *content;
    char *nodeType;
    ptrast left;
    ptrast right;
};

ptrast programme();
ptrast external_declaration();
ptrast decl_or_stmt();
ptrast declarator_list();
ptrast intstr_list();
ptrast initializer();
ptrast declarator();
ptrast parameter_list();
ptrast parameter();
ptrast type();
ptrast statement();
ptrast statement_list();
ptrast expression_statement();
ptrast expr();
ptrast cmp_expr();
ptrast add_expr();
ptrast mul_expr();
ptrast primary_expr();
ptrast expr_list();
ptrast id_list();
void advance();

ptrast CreateNewAstNode(char *content, char *nodeType, ptrast left, ptrast right)
{
    ptrast NewNode = (ptrast)malloc(sizeof(ast));
    NewNode->content = content;
    NewNode->nodeType = nodeType;
    NewNode->left = left;
    NewNode->right = right;
    return NewNode;
}

void ShowAst(ptrast root, int depth)
{
    if (root == NULL)
        return;
    if (!strcmp(root->nodeType, "__list__"))
    {
        ShowAst(root->left, depth);
        ShowAst(root->right, depth);
    }
    else
    {
        for (int i = 0; i < depth * 2; ++i)
            printf(" ");
        printf("%s:%s\n", root->nodeType, root->content);
        ShowAst(root->left, depth + 1);
        ShowAst(root->right, depth + 1);
    }
    return;
}

void FreeAst(ptrast root)
{
    if (!root)
        return;
    FreeAst(root->left);
    FreeAst(root->right);
    free(root->content);
    free(root->nodeType);
    free(root);
    return;
}

void advance()
{
    tok = yylex();
    // printf("tok==%c\n", tok);
    // if (tok == EOF)
    //     return false;
    // return true;
}

// program
//     : external_declaration
//     | program external_declaration
//     ;
ptrast programme()
{
    if (tok == EOF)
        return NULL;
    ptrast root = CreateNewAstNode("", "__list__", NULL, NULL);
    if (root->left = external_declaration())
        root->right = programme();
    return root;
}

// external_declaration
//     : type declarator decl_or_stmt
//     ;
ptrast external_declaration()
{
    if (tok == EOF)
        return NULL;
    ptrast root = CreateNewAstNode("", "external_declaration", NULL, NULL);
    if (root->left = type())
    {
        root->right = CreateNewAstNode("", "decl_stmt", NULL, CreateNewAstNode("", "__list__", NULL, NULL));
        if (root->right->left = declarator())
            root->right->right = decl_or_stmt();
    }
    return root;
}

//  decl_or_stmt
//      : '{' statement_list '}'
//      | '{' '}'
//      | ',' declarator_list ';'
//      | ';'
//      ;
ptrast decl_or_stmt()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == '{')
    {
        advance();
        if (root = statement_list())
            root = CreateNewAstNode("", "ManyStmt", root, NULL);
        else
            return NULL;
        if (tok == '}')
            advance();
        else
            return NULL;
    }
    else if (tok == ',')
    {
        advance();
        if (root = declarator_list())
            if (tok = ';')
                advance();
            else
                return NULL;
        else
            return NULL;
    }
    else if (tok == ';')
        advance();
    return root;
}

//  declarator_list
//      : declarator
//      | declarator_list ',' declarator
//      ;
ptrast declarator_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = declarator())
    {
        root = CreateNewAstNode("", "__list__", root, NULL);
        if (tok == ',')
        {
            advance();
            root->right = declarator_list();
        }
    }
    return root;
}

//  intstr_list
//      : initializer
//      | intstr_list ',' initializer
//      ;
ptrast intstr_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = initializer())
    {
        root = CreateNewAstNode("", "__list__", root, NULL);
        if (tok == ',')
        {
            advance();
            root->right = intstr_list();
        }
    }
    return root;
}

//  initializer
//      : NUMBER
//      | STRING
//      ;
ptrast initializer()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == NUMBER)
    {
        root = CreateNewAstNode(strdup(yytext), "IntegerLiteral", NULL, NULL);
        advance();
    }
    else if (tok == STRING)
    {
        root = CreateNewAstNode(strdup(yytext), "StringLiteral", NULL, NULL);
        advance();
    }
    return root;
}

//  declarator
//      : ID
//      | ID '=' expr
//      | ID '(' parameter_list ')'
//      | ID '(' ')'
//      | ID '[' expr ']'
//      | ID '[' ']'
//      | ID '[' expr ']' '=' '{' intstr_list '}'
//      | ID '[' ']' '=' '{' intstr_list '}'
//      ;
ptrast declarator()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == ID)
    {
        root = CreateNewAstNode(strdup(yytext), "VariableDec", NULL, NULL);
        advance();
        if (tok == '=')
        {
            advance();
            root->right = expr();
        }
        else if (tok == '(')
        {
            root->nodeType = "FunctionDecl";
            advance();
            root->left = parameter_list();
            if (tok == ')')
                advance();
        }
        else if (tok == '[')
        {
            root->nodeType = "VariableList";
            advance();
            root->left = expr();
            if (tok == ']')
            {
                advance();
                if (tok == '=')
                {
                    root->content = "=";
                    advance();
                    if (tok == '{')
                    {
                        advance();
                        if (root->right = intstr_list())
                        {
                            root->right = CreateNewAstNode("InitListExpr", "", root->right, NULL);
                            if (tok == '}')
                                advance();
                        }
                    }
                }
            }
        }
    }
    return root;
}

//  parameter_list
//      : parameter
//      | parameter_list ',' parameter
//      ;
ptrast parameter_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = parameter())
    {
        root = CreateNewAstNode("", "__list__", root, NULL);
        if (tok == ',')
        {
            advance();
            root->right = parameter_list();
        }
    }
    return root;
}

//  parameter
//      : type ID
//      ;
ptrast parameter()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = type())
    {
        if (tok == ID)
        {
            root = CreateNewAstNode(strdup(yytext), "parameter", root, CreateNewAstNode(strdup(yytext), "Variable", NULL, NULL));
            advance();
        }
    }
    return root;
}

//  type
//      : INT
//      | STR
//      | VOID
//      ;
ptrast type()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == INT || tok == STR || tok == VOID)
    {
        root = CreateNewAstNode(strdup(yytext), "type", NULL, NULL);
        advance();
    }
    return root;
}

//  statement
//      : type declarator_list ';'
//      | '{' statement_list '}'
//      | expr_statement
//      | IF '(' expr ')' statement
//      | IF '(' expr ')' statement ELSE statement
//      | WHILE '(' expr ')' statement
//      | RETURN ';'
//      | RETURN expr ';'
//      | PRINT ';'
//      | PRINT expr_list ';'
//      | SCAN id_list ';'
//      ;
ptrast statement()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = type())
    {
        root = CreateNewAstNode("", "DeclStmt", root, NULL);
        if (root->right = declarator_list())
        {
            if (tok == ';')
                advance();
        }
    }
    else if (tok == '{')
    {
        advance();
        if (root = statement_list())
        {
            root = CreateNewAstNode("", "ManyStmt", root, NULL);
            if (tok == '}')
                advance();
        }
    }
    else if (root = expression_statement())
    {
        ;
    }
    else if (tok == IF)
    {
        root = CreateNewAstNode("", "IF_Stmt", NULL, CreateNewAstNode("", "__list__", NULL, NULL));
        advance();
        if (tok == '(')
        {
            advance();
            if (root->left = expr())
            {
                if (tok == ')')
                {
                    advance();
                    if (root->right->left = statement())
                    {
                        if (tok == ELSE)
                        {
                            advance();
                            root->right->right = statement();
                        }
                    }
                }
            }
        }
    }
    else if (tok == WHILE)
    {
        root = CreateNewAstNode("", "WhileStmt", NULL, NULL);
        advance();
        if (tok == '(')
        {
            advance();
            if (root->left = expr())
            {
                if (tok == ')')
                {
                    advance();
                    root->right = statement();
                }
            }
        }
    }
    else if (tok == RETURN)
    {
        root = CreateNewAstNode("", "ReturnStmt", NULL, NULL);
        advance();
        root->left = expr();
        if (tok == ';')
            advance();
    }
    else if (tok == PRINT)
    {
        root = CreateNewAstNode("", "PrintStmt", NULL, NULL);
        advance();
        root->left = expr_list();
        if (tok == ';')
            advance();
    }
    else if (tok == SCAN)
    {
        root = CreateNewAstNode("", "ScanStmt", NULL, NULL);
        advance();
        if (root->left = id_list())
            if (tok == ';')
                advance();
    }
    return root;
}

// statement_list
//     : statement
//     | statement_list statement
//     ;
ptrast statement_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = statement())
        root = CreateNewAstNode("", "__list__", root, statement_list());
    return root;
}

//  expression_statement
//      : ';'
//      | expr ';'
//      ;
ptrast expression_statement()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == ';')
        advance();
    else if (root = expr())
        if (tok == ';')
            advance();
    return root;
}

//  expr
//      : cmp_expr
//      ;
ptrast expr()
{
    if (tok == EOF)
        return NULL;
    return cmp_expr();
}

//  cmp_expr
//      : add_expr
//      | cmp_expr CMP add_expr
//      ;
ptrast cmp_expr()
{
    if (tok == EOF)
        return NULL;
    ptrast root = add_expr();
    if (root)
    {
        while (tok == CMP)
        {
            root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
            advance();
            root->right = add_expr();
        }
    }
    return root;
}

//  add_expr
//      : mul_expr
//      | add_expr '+' mul_expr
//      | add_expr '-' mul_expr
//      ;
ptrast add_expr()
{
    if (tok == EOF)
        return NULL;
    ptrast root = mul_expr();
    if (root)
    {
        while (tok == '+' || tok == '-')
        {
            root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
            advance();
            root->right = mul_expr();
        }
    }
    return root;
}

//  mul_expr
//      : primary_expr
//      | mul_expr '*' primary_expr
//      | mul_expr '/' primary_expr
//      | mul_expr '%' primary_expr
//      | '-' primary_expr
//      ;
ptrast mul_expr()
{
    if (tok == EOF)
        return NULL;
    ptrast root = primary_expr();
    if (root)
    {
        while (tok == '*' || tok == '/' || tok == '%')
        {
            root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
            advance();
            root->right = primary_expr();
        }
    }
    else if (tok == '-')
    {
        root = CreateNewAstNode(strdup(yytext), "Operator", NULL, NULL);
        advance();
        root->right = primary_expr();
    }
    return root;
}

//  primary_expr
//      | ID
//      | ID '(' ')'
//      : ID '(' expr_list ')'
//      | ID '[' expr ']'
//      | ID '[' expr ']' '=' expr
//      | ID '=' expr
//      | ID ASSIGN expr
//      | '(' expr ')'
//      | NUMBER
//      | STRING
//      ;
ptrast primary_expr()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == ID)
    {
        root = CreateNewAstNode(strdup(yytext), "VariableRef", NULL, NULL);
        advance();
        if (tok == '(')
        {
            root->nodeType = "FunctionRef";
            advance();
            root->left = expr_list();
            if (tok == ')')
                advance();
        }
        else if (tok == '[')
        {
            advance();
            if (root->left = expr())
            {
                root->nodeType = "VariableList";
                if (tok == ']')
                {
                    advance();
                    if (tok == '=')
                    {
                        root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
                        advance();
                        root->right = expr();
                    }
                }
            }
        }
        else if (tok == ASSIGN || tok == '=')
        {
            root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
            advance();
            root->right = expr();
        }
    }
    else if (tok == '(')
    {
        advance();
        if (root = expr())
        {
            if (tok == ')')
                advance();
        }
    }
    else if (tok == NUMBER)
    {
        root = CreateNewAstNode(strdup(yytext), "IntegerLiteral", NULL, NULL);
        advance();
    }
    else if (tok == STRING)
    {
        root = CreateNewAstNode(strdup(yytext), "StringLiteral", NULL, NULL);
        advance();
    }
    return root;
}

ptrast expr_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = expr())
    {
        root = CreateNewAstNode("", "__list__", root, NULL);
        if (tok == ',')
        {
            advance();
            root->right = expr_list();
        }
    }
    return root;
}

ptrast id_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == ID)
    {
        root = CreateNewAstNode("", "__list__", CreateNewAstNode(strdup(yytext), "Variable", NULL, NULL), NULL);
        advance();
        if (tok == ',')
        {
            advance();
            root->right = id_list();
        }
    }
    return root;
}

int main()
{
    ptrast root = NULL;
    if (!(yyin = fopen("test.c", "r")))
    {
        printf("open fail\n");
        return -1;
    }
    advance();
    root = programme();
    ShowAst(root, 0);
    FreeAst(root);
    return 0;
=======
#include <stdlib.h>
#include <stdbool.h>
#include "lex.yy.c"

int tok;

typedef struct AST ast;
typedef struct AST *ptrast;
struct AST
{
    char *content;
    char *nodeType;
    ptrast left;
    ptrast right;
};

ptrast programme();
ptrast external_declaration();
ptrast decl_or_stmt();
ptrast declarator_list();
ptrast intstr_list();
ptrast initializer();
ptrast declarator();
ptrast parameter_list();
ptrast parameter();
ptrast type();
ptrast statement();
ptrast statement_list();
ptrast expression_statement();
ptrast expr();
ptrast cmp_expr();
ptrast add_expr();
ptrast mul_expr();
ptrast primary_expr();
ptrast expr_list();
ptrast id_list();
void advance();

ptrast CreateNewAstNode(char *content, char *nodeType, ptrast left, ptrast right)
{
    ptrast NewNode = (ptrast)malloc(sizeof(ast));
    NewNode->content = content;
    NewNode->nodeType = nodeType;
    NewNode->left = left;
    NewNode->right = right;
    return NewNode;
}

void ShowAst(ptrast root, int depth)
{
    if (root == NULL)
        return;
    if (!strcmp(root->nodeType, "__list__"))
    {
        ShowAst(root->left, depth);
        ShowAst(root->right, depth);
    }
    else
    {
        for (int i = 0; i < depth * 2; ++i)
            printf(" ");
        printf("%s:%s\n", root->nodeType, root->content);
        ShowAst(root->left, depth + 1);
        ShowAst(root->right, depth + 1);
    }
    return;
}

void FreeAst(ptrast root)
{
    if (!root)
        return;
    FreeAst(root->left);
    FreeAst(root->right);
    free(root->content);
    free(root->nodeType);
    free(root);
    return;
}

void advance()
{
    tok = yylex();
    // printf("tok==%c\n", tok);
    // if (tok == EOF)
    //     return false;
    // return true;
}

// program
//     : external_declaration
//     | program external_declaration
//     ;
ptrast programme()
{
    if (tok == EOF)
        return NULL;
    ptrast root = CreateNewAstNode("", "__list__", NULL, NULL);
    if (root->left = external_declaration())
        root->right = programme();
    return root;
}

// external_declaration
//     : type declarator decl_or_stmt
//     ;
ptrast external_declaration()
{
    if (tok == EOF)
        return NULL;
    ptrast root = CreateNewAstNode("", "external_declaration", NULL, NULL);
    if (root->left = type())
    {
        root->right = CreateNewAstNode("", "decl_stmt", NULL, CreateNewAstNode("", "__list__", NULL, NULL));
        if (root->right->left = declarator())
            root->right->right = decl_or_stmt();
    }
    return root;
}

//  decl_or_stmt
//      : '{' statement_list '}'
//      | '{' '}'
//      | ',' declarator_list ';'
//      | ';'
//      ;
ptrast decl_or_stmt()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == '{')
    {
        advance();
        if (root = statement_list())
            root = CreateNewAstNode("", "ManyStmt", root, NULL);
        else
            return NULL;
        if (tok == '}')
            advance();
        else
            return NULL;
    }
    else if (tok == ',')
    {
        advance();
        if (root = declarator_list())
            if (tok = ';')
                advance();
            else
                return NULL;
        else
            return NULL;
    }
    else if (tok == ';')
        advance();
    return root;
}

//  declarator_list
//      : declarator
//      | declarator_list ',' declarator
//      ;
ptrast declarator_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = declarator())
    {
        root = CreateNewAstNode("", "__list__", root, NULL);
        if (tok == ',')
        {
            advance();
            root->right = declarator_list();
        }
    }
    return root;
}

//  intstr_list
//      : initializer
//      | intstr_list ',' initializer
//      ;
ptrast intstr_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = initializer())
    {
        root = CreateNewAstNode("", "__list__", root, NULL);
        if (tok == ',')
        {
            advance();
            root->right = intstr_list();
        }
    }
    return root;
}

//  initializer
//      : NUMBER
//      | STRING
//      ;
ptrast initializer()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == NUMBER)
    {
        root = CreateNewAstNode(strdup(yytext), "IntegerLiteral", NULL, NULL);
        advance();
    }
    else if (tok == STRING)
    {
        root = CreateNewAstNode(strdup(yytext), "StringLiteral", NULL, NULL);
        advance();
    }
    return root;
}

//  declarator
//      : ID
//      | ID '=' expr
//      | ID '(' parameter_list ')'
//      | ID '(' ')'
//      | ID '[' expr ']'
//      | ID '[' ']'
//      | ID '[' expr ']' '=' '{' intstr_list '}'
//      | ID '[' ']' '=' '{' intstr_list '}'
//      ;
ptrast declarator()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == ID)
    {
        root = CreateNewAstNode(strdup(yytext), "VariableDec", NULL, NULL);
        advance();
        if (tok == '=')
        {
            advance();
            root->right = expr();
        }
        else if (tok == '(')
        {
            root->nodeType = "FunctionDecl";
            advance();
            root->left = parameter_list();
            if (tok == ')')
                advance();
        }
        else if (tok == '[')
        {
            root->nodeType = "VariableList";
            advance();
            root->left = expr();
            if (tok == ']')
            {
                advance();
                if (tok == '=')
                {
                    root->content = "=";
                    advance();
                    if (tok == '{')
                    {
                        advance();
                        if (root->right = intstr_list())
                        {
                            root->right = CreateNewAstNode("InitListExpr", "", root->right, NULL);
                            if (tok == '}')
                                advance();
                        }
                    }
                }
            }
        }
    }
    return root;
}

//  parameter_list
//      : parameter
//      | parameter_list ',' parameter
//      ;
ptrast parameter_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = parameter())
    {
        root = CreateNewAstNode("", "__list__", root, NULL);
        if (tok == ',')
        {
            advance();
            root->right = parameter_list();
        }
    }
    return root;
}

//  parameter
//      : type ID
//      ;
ptrast parameter()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = type())
    {
        if (tok == ID)
        {
            root = CreateNewAstNode(strdup(yytext), "parameter", root, CreateNewAstNode(strdup(yytext), "Variable", NULL, NULL));
            advance();
        }
    }
    return root;
}

//  type
//      : INT
//      | STR
//      | VOID
//      ;
ptrast type()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == INT || tok == STR || tok == VOID)
    {
        root = CreateNewAstNode(strdup(yytext), "type", NULL, NULL);
        advance();
    }
    return root;
}

//  statement
//      : type declarator_list ';'
//      | '{' statement_list '}'
//      | expr_statement
//      | IF '(' expr ')' statement
//      | IF '(' expr ')' statement ELSE statement
//      | WHILE '(' expr ')' statement
//      | RETURN ';'
//      | RETURN expr ';'
//      | PRINT ';'
//      | PRINT expr_list ';'
//      | SCAN id_list ';'
//      ;
ptrast statement()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = type())
    {
        root = CreateNewAstNode("", "DeclStmt", root, NULL);
        if (root->right = declarator_list())
        {
            if (tok == ';')
                advance();
        }
    }
    else if (tok == '{')
    {
        advance();
        if (root = statement_list())
        {
            root = CreateNewAstNode("", "ManyStmt", root, NULL);
            if (tok == '}')
                advance();
        }
    }
    else if (root = expression_statement())
    {
        ;
    }
    else if (tok == IF)
    {
        root = CreateNewAstNode("", "IF_Stmt", NULL, CreateNewAstNode("", "__list__", NULL, NULL));
        advance();
        if (tok == '(')
        {
            advance();
            if (root->left = expr())
            {
                if (tok == ')')
                {
                    advance();
                    if (root->right->left = statement())
                    {
                        if (tok == ELSE)
                        {
                            advance();
                            root->right->right = statement();
                        }
                    }
                }
            }
        }
    }
    else if (tok == WHILE)
    {
        root = CreateNewAstNode("", "WhileStmt", NULL, NULL);
        advance();
        if (tok == '(')
        {
            advance();
            if (root->left = expr())
            {
                if (tok == ')')
                {
                    advance();
                    root->right = statement();
                }
            }
        }
    }
    else if (tok == RETURN)
    {
        root = CreateNewAstNode("", "ReturnStmt", NULL, NULL);
        advance();
        root->left = expr();
        if (tok == ';')
            advance();
    }
    else if (tok == PRINT)
    {
        root = CreateNewAstNode("", "PrintStmt", NULL, NULL);
        advance();
        root->left = expr_list();
        if (tok == ';')
            advance();
    }
    else if (tok == SCAN)
    {
        root = CreateNewAstNode("", "ScanStmt", NULL, NULL);
        advance();
        if (root->left = id_list())
            if (tok == ';')
                advance();
    }
    return root;
}

// statement_list
//     : statement
//     | statement_list statement
//     ;
ptrast statement_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = statement())
        root = CreateNewAstNode("", "__list__", root, statement_list());
    return root;
}

//  expression_statement
//      : ';'
//      | expr ';'
//      ;
ptrast expression_statement()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == ';')
        advance();
    else if (root = expr())
        if (tok == ';')
            advance();
    return root;
}

//  expr
//      : cmp_expr
//      ;
ptrast expr()
{
    if (tok == EOF)
        return NULL;
    return cmp_expr();
}

//  cmp_expr
//      : add_expr
//      | cmp_expr CMP add_expr
//      ;
ptrast cmp_expr()
{
    if (tok == EOF)
        return NULL;
    ptrast root = add_expr();
    if (root)
    {
        while (tok == CMP)
        {
            root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
            advance();
            root->right = add_expr();
        }
    }
    return root;
}

//  add_expr
//      : mul_expr
//      | add_expr '+' mul_expr
//      | add_expr '-' mul_expr
//      ;
ptrast add_expr()
{
    if (tok == EOF)
        return NULL;
    ptrast root = mul_expr();
    if (root)
    {
        while (tok == '+' || tok == '-')
        {
            root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
            advance();
            root->right = mul_expr();
        }
    }
    return root;
}

//  mul_expr
//      : primary_expr
//      | mul_expr '*' primary_expr
//      | mul_expr '/' primary_expr
//      | mul_expr '%' primary_expr
//      | '-' primary_expr
//      ;
ptrast mul_expr()
{
    if (tok == EOF)
        return NULL;
    ptrast root = primary_expr();
    if (root)
    {
        while (tok == '*' || tok == '/' || tok == '%')
        {
            root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
            advance();
            root->right = primary_expr();
        }
    }
    else if (tok == '-')
    {
        root = CreateNewAstNode(strdup(yytext), "Operator", NULL, NULL);
        advance();
        root->right = primary_expr();
    }
    return root;
}

//  primary_expr
//      | ID
//      | ID '(' ')'
//      : ID '(' expr_list ')'
//      | ID '[' expr ']'
//      | ID '[' expr ']' '=' expr
//      | ID '=' expr
//      | ID ASSIGN expr
//      | '(' expr ')'
//      | NUMBER
//      | STRING
//      ;
ptrast primary_expr()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == ID)
    {
        root = CreateNewAstNode(strdup(yytext), "VariableRef", NULL, NULL);
        advance();
        if (tok == '(')
        {
            root->nodeType = "FunctionRef";
            advance();
            root->left = expr_list();
            if (tok == ')')
                advance();
        }
        else if (tok == '[')
        {
            advance();
            if (root->left = expr())
            {
                root->nodeType = "VariableList";
                if (tok == ']')
                {
                    advance();
                    if (tok == '=')
                    {
                        root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
                        advance();
                        root->right = expr();
                    }
                }
            }
        }
        else if (tok == ASSIGN || tok == '=')
        {
            root = CreateNewAstNode(strdup(yytext), "Operator", root, NULL);
            advance();
            root->right = expr();
        }
    }
    else if (tok == '(')
    {
        advance();
        if (root = expr())
        {
            if (tok == ')')
                advance();
        }
    }
    else if (tok == NUMBER)
    {
        root = CreateNewAstNode(strdup(yytext), "IntegerLiteral", NULL, NULL);
        advance();
    }
    else if (tok == STRING)
    {
        root = CreateNewAstNode(strdup(yytext), "StringLiteral", NULL, NULL);
        advance();
    }
    return root;
}

ptrast expr_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (root = expr())
    {
        root = CreateNewAstNode("", "__list__", root, NULL);
        if (tok == ',')
        {
            advance();
            root->right = expr_list();
        }
    }
    return root;
}

ptrast id_list()
{
    if (tok == EOF)
        return NULL;
    ptrast root = NULL;
    if (tok == ID)
    {
        root = CreateNewAstNode("", "__list__", CreateNewAstNode(strdup(yytext), "Variable", NULL, NULL), NULL);
        advance();
        if (tok == ',')
        {
            advance();
            root->right = id_list();
        }
    }
    return root;
}

int main()
{
    ptrast root = NULL;
    if (!(yyin = fopen("test.c", "r")))
    {
        printf("open fail\n");
        return -1;
    }
    advance();
    root = programme();
    ShowAst(root, 0);
    FreeAst(root);
    return 0;
>>>>>>> 8dad9ee129215d834500947d610d65c5aead218d
}