#include "lrparser.tab.h"
#include "ast.h"
#include "makeAst.h"

ptrast astRoot;
extern char *CompilerFile;

int produceAst()
{
	if (!(yyin = fopen(CompilerFile, "r")))
		printf("open fail\n");
	else
		yyparse();
	return 0;
}