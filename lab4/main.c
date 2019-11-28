#include "lrparser.tab.h"
#include "ast.h"

int main()
{
	if (!(yyin = fopen("test.c", "r")))
		printf("open fail\n");
	else
		yyparse();
	showAst(astRoot);
	freeAst(astRoot);
	return 0;
}