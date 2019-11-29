#ifndef AST_H_
#define AST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* interface to the lexer */
extern int yylineno; /* from lexer */
extern char *yytext;
int yyerror(char *text);
int yylex(void);
extern FILE *yyin, *yyout;
int yyparse();

struct AST
{
    char *content;
    char *nodeType;
    struct AST *left;
    struct AST *right;
};

typedef struct AST ast;
typedef struct AST *ptrast;

ptrast CreateNewAstNode(char *content, char *nodeType, ptrast left, ptrast right);
void ShowAst(ptrast root, int depth);
void FreeAst(ptrast root);

#endif 