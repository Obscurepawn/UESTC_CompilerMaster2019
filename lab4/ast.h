#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AST ast;
typedef struct AST *ptrast;

typedef struct IF_StatementNode if_statement;
typedef struct IF_StatementNode *ptr_if_statement;

enum datatype
{
	INT,
	VOID,
	STR
};

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
	ptrast else_do_statement;
};

/**interface to the ast.c**/
ptrast newAstNode(char *nodetype, char *content, int value, ptrast left, ptrast right);
ptrast newListNode(ptrast now, ptrast next);
ptrast newIfNode(char *nodetype, ptrast judge_exp, ptrast if_do_statement, ptrast else_do_statement);
void showAst(ptrast root, int depth);
void freeAst(ptrast root);
char *strdup(const char *s);
char *Operator[] = {
	"<",
	">",
	"=",
	">=",
	"<=",
	"==",
	"==",
	":=",
	"+=",
	"/=",
	"-=",
	"*="};

/**interface to the lexer**/
extern int yylineno;
extern char *yytext;
int yyerror(char *text);
int yylex(void);
extern FILE *yyin, *yyout;

/**interface to the parser**/
int yyparse();

#endif
