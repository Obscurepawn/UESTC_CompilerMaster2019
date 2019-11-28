#include"lrparser.tab.h"
#include"ast.h"

int main()
{
  if(!(yyin=fopen("test.c","r")))
      printf("open fail\n");
  else
      yyparse();
  ShowAst(astRoot,0);
  FreeAst(astRoot);
  return 0;
}