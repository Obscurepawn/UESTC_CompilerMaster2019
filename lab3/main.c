#include"lrparser.tab.h"
#include"ast.h"

int main()
{
  if(!(yyin=fopen("test.c","r")))
      printf("open fail\n");
  else
      yyparse();
  ShowAst(astRoot);
  FreeAst(astRoot);
  return 0;
}