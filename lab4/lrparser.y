%{
  #include"ast.h"
  //int yydebug=1;
  extern struct AST *astRoot;
%}

%union {
  struct AST *ast_node;
  char *save_yytext;
}

/* declare tokens */
%token <save_yytext> NUMBER
%token WHILE
%token <save_yytext> STRING
%token <save_yytext> ID
%token INT
%token STR
%token VOID
%token IF
%token ELSE
%token RETURN
%token PRINT
%token SCAN
%token <save_yytext> CMP
%token <save_yytext> ASSIGN
%token EOP

%type <ast_node> initializer program external_declaration function_definition declaration init_declarator_list init_declarator intstr_list  declarator direct_declarator parameter_list parameter statement compound_statement statement_list expression_statement selection_statement iteration_statement jump_statement print_statement scan_statement expr expr_list add_expr assign_expr cmp_expr mul_expr primary_expr id_list
%type <char *> type
%type <int> begin_scope end_scope

%%
program: external_declaration  {$$ = $1;}
       | program external_declaration  {$$ = newListNode($1,$2);}
       | program EOP {astRoot = $1;return 1;}
       ;
external_declaration: function_definition {$$ = $1;}
                    | declaration {$$ = $1;}
                    ;
function_definition: type ID compound_statement {$$ = newAstNode("FunctionDef",strdup($2),0,$3,newAstNode("ReturnType",strdup($1),0,NULL,NULL));}
                    ;
declaration: type init_declarator_list ';' {$$ = newAstNode("VariableDec",strdup($1),0,$2,NULL);}
           ;
init_declarator_list: init_declarator {$$ = $1;}
                    | init_declarator_list ',' init_declarator {$$ = newListNode($1,$3);}
                    ;
init_declarator: declarator {$$ = $1;}
               | declarator '=' add_expr {$$ = newAstNode("VariableInit",NULL,0,$1,$3);}
               | declarator '=' '{' intstr_list '}' {$$ = newAstNode("ListInit",NULL,0,$1,$4);}
               ;
intstr_list: initializer {$$ = $1;}
           | intstr_list ',' initializer {$$ = newListNode($1,$3);}
           ;
initializer: NUMBER {$$ = newAstNode("Number",NULL,atof($1),NULL,NULL);}
           | STRING {$$ = newAstNode("String",strdup($1),0,NULL,NULL);}
           ;
declarator: direct_declarator {$$ = $1;}
          ;
direct_declarator: ID {$$ = newAstNode("VariableName",strdup($1),0,NULL,NULL);}
                 | direct_declarator '(' parameter_list ')' {$$ = newAstNode("FunctionDec",NULL,0,$1,$3);}
                 | direct_declarator '(' ')'  {$$ = newAstNode("FunctionDec",NULL,0,$1,NULL);}
                 | ID '[' expr ']' {$$ = newAstNode("ListDec",strdup($1),0,$3,NULL);}
                 | ID '[' ']' {$$ = newAstNode("ListDec",strdup($1),0,NULL,NULL);}
                 ;
parameter_list: parameter {$$ = $1;}
              | parameter_list ',' parameter {$$ = newListNode($1,$3);}
              ;
parameter: type ID {$$ = newAstNode($1,strdup($2),0,NULL,NULL);}
         ;
type: INT {$$ = "INT";}
    | STR {$$ = "STR";}
    | VOID {$$ = "VOID";}
    ;
statement: compound_statement {$$ = $1;}
         | expression_statement {$$ = $1;}
         | selection_statement {$$ = $1;}
         | iteration_statement {$$ = $1;}
         | jump_statement {$$ = $1;}
         | print_statement {$$ = $1;}
         | scan_statement {$$ = $1;}
         | declaration {$$ = $1;}
         ;
compound_statement: begin_scope end_scope {$$ = NULL;}
                  | begin_scope statement_list end_scope {$$ = $2;}
                  ;
begin_scope: '{' {$$ = '{';}
           ;
end_scope: '}'  {$$ = '}';}
         ;
statement_list: statement {$$ = $1;}
             | statement_list statement {$$ = newListNode($1,$2);}
             ;
expression_statement: ';' {$$=NULL;}
                    | expr ';' {$$ = $1;}
                    ;
selection_statement: IF '(' expr ')' statement {$$ = newIfNode("IF_Stmt",$3,$5,NULL);}
                   | IF '(' expr ')' statement ELSE statement {$$ = newIfNode("IF_Stmt",$3,$5,$7);}
                   ;
iteration_statement: WHILE '(' expr ')' statement {$$ = newAstNode("WhileStmt",NULL,0,$3,$5);}
                   ;
jump_statement: RETURN ';' {$$ = NULL;}
              | RETURN expr ';' {$$ = newAstNode("ReturnStmt",NULL,0,$2,NULL);}
              ;
print_statement: PRINT ';' {$$ = NULL;}
               | PRINT expr_list ';' {$$ = newAstNode("PrintStmt",NULL,0,$2,NULL);}
               ;
scan_statement: SCAN id_list ';' {$$ = newAstNode("ScanStmt",NULL,0,$2,NULL);}
              ;
expr: assign_expr {$$ = $1;}
    ;
assign_expr: cmp_expr {$$ = $1;}
           | ID ASSIGN assign_expr {$$ = newAstNode(strdup($2),strdup($1),0,$3,NULL);}
           | ID '=' assign_expr {$$ = newAstNode("=","strdup($1)",0,$3,NULL);}
           | ID '[' expr ']' '=' assign_expr {$$ = newAstNode("=",strdup($1),0,$3,$6);}
           ;
cmp_expr: add_expr {$$ = $1;}
        | cmp_expr CMP add_expr {$$ = newAstNode(strdup($2),NULL,0,$1,$3);}
        ;
add_expr: mul_expr {$$ = $1;}
        | add_expr '+' mul_expr {$$ = newAstNode("+",NULL,0,$1,$3);}
        | add_expr '-' mul_expr {$$ = newAstNode("-",NULL,0,$1,$3);}
        ;
mul_expr: primary_expr {$$ = $1;}
        | mul_expr '*' primary_expr {$$ = newAstNode("*",NULL,0,$1,$3);}
        | mul_expr '/' primary_expr {$$ = newAstNode("/",NULL,0,$1,$3);}
        | mul_expr '%' primary_expr {$$ = newAstNode("%",NULL,0,$1,$3);}
        | '-' primary_expr {$$ = newAstNode("-","Minus",0,$2,NULL);}
        ;
primary_expr: ID '(' expr_list ')' {$$ = newAstNode("FunctionRef",strdup($1),0,$3,NULL);}
            | ID '(' ')' {$$ = newAstNode("FunctionRef",strdup($1),0,NULL,NULL);}
            | '(' expr ')' {$$ = $2;}
            | ID {$$ = newAstNode("VariableRef",strdup($1),0,NULL,NULL);}
            | initializer {$$ = $1;}
            | ID '[' expr ']' {$$ = newAstNode("ListRef",strdup($1),0,$3,NULL);}
            ;
expr_list: expr {$$ = $1;}
         | expr_list ',' expr {$$ = newListNode($1,$3);}

id_list: ID {$$ = newAstNode("VariableName",strdup($1),0,NULL,NULL);}
       | id_list ',' ID {$$ = newListNode($1,$3);}
       ;
%%