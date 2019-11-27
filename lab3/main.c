<<<<<<< HEAD
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
=======
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
>>>>>>> 8dad9ee129215d834500947d610d65c5aead218d
}