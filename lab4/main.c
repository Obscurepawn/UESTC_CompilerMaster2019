#include "lrparser.tab.h"
#include "ast.h"

ptrast astRoot;

int main()
{
	if (!(yyin = fopen("test.c", "r")))
		printf("open fail\n");
	else
		yyparse();
	showAst(astRoot,0);
	freeAst(astRoot);
	return 0;
}