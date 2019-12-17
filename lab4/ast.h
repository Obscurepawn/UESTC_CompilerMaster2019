#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct AST ast;
typedef struct AST *ptrast;

typedef struct IF_StatementNode if_statement;
typedef struct IF_StatementNode *ptr_if_statement;

struct AST
{
	char *nodetype;
	int value;
	char *content;
	ptrast next;
	ptrast left;
	ptrast right;
};

struct IF_StatementNode
{
	char *nodetype;
	ptrast judge_exp;
	ptrast if_do_statement;
	ptrast next;
	ptrast else_do_statement;
};

/**interface to the ast.c**/
ptrast newAstNode(char *nodetype, char *content, int value, ptrast left, ptrast right);
ptrast newListNode(ptrast next, ptrast now);
ptrast newIfNode(char *nodetype, ptrast judge_exp, ptrast if_do_statement, ptrast else_do_statement);
void showAst(ptrast root, int depth);
void freeAst(ptrast root);
char *strdup(const char *s);
int checkOperator(ptrast root);
void produceSpace(int depth);
void DecDefPrint(int depth, ptrast root, char *content_title);

/**interface to the lexer**/
extern int yylineno;
extern char *yytext;
int yyerror(char *text);
int yylex(void);
extern FILE *yyin, *yyout;
extern ptrast astRoot;

/**interface to the parser**/
int yyparse();

/**interface to the genLLVM.c**/
void init();

#endif
