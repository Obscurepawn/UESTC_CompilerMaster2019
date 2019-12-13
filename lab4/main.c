#include "lrparser.tab.h"
#include "ast.h"

ptrast astRoot;

int produceAst()
{
	if (!(yyin = fopen("test.c", "r")))
		printf("open fail\n");
	else
		yyparse();
	return 0;
}