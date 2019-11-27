<<<<<<< HEAD
%{
  #include"ast.h"
  //int yydebug=1;
  extern ast_node astRoot;
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

%type <ast_node> program external_declaration function_definition declaration init_declarator_list init_declarator intstr_list initializer declarator direct_declarator parameter_list parameter type statement compound_statement statement_list expression_statement selection_statement iteration_statement jump_statement print_statement scan_statement expr expr_list add_expr assign_expr cmp_expr mul_expr primary_expr id_list begin_scope end_scope

%%
program: external_declaration  {$$ = $1;}
       | program external_declaration  {$$ = CreateNewAstNode("","__list__",$1,$2);}
       | program EOP {astRoot = $1;return;}
       ;
external_declaration: function_definition {$$ = CreateNewAstNode("","ExternalDeclaration",$1,NULL);}
                    | declaration {$$ = CreateNewAstNode("","ExternalDeclaration",$1,NULL);}
                    ;
function_definition: type declarator compound_statement {$$ = CreateNewAstNode("","FunctionDefinition",$1,CreateNewAstNode("","__list__",$2,$3));}
                    ;
declaration: type init_declarator_list ';' {$$ = CreateNewAstNode("","__list__",$1,$2);}
           ;
init_declarator_list: init_declarator {$$ = CreateNewAstNode("","__list__",$1,NULL);}
                    | init_declarator_list ',' init_declarator {$$ = CreateNewAstNode("","__list__",$1,$3);}
                    ;
init_declarator: declarator {$$ = CreateNewAstNode("","InitDeclarator",$1,NULL);}
               | declarator '=' add_expr {$$ = CreateNewAstNode("","InitDeclarator",$1,$3);}
               | declarator '=' '{' intstr_list '}' {$$ = CreateNewAstNode("","InitDeclarator",$1,$4);}
               ;
intstr_list: initializer {$$ = CreateNewAstNode("","__list__",$1,NULL);}
           | intstr_list ',' initializer {$$ = CreateNewAstNode("","__list__",$1,$3);}
           ;
initializer: NUMBER {$$ = CreateNewAstNode(strdup($1),"IntergerInteral",NULL,NULL);}
           | STRING {$$ = CreateNewAstNode(strdup($1),"StringInteral",NULL,NULL);}
           ;
declarator: direct_declarator {$$ = CreateNewAstNode("","__list__",$1,NULL);}
          ;
direct_declarator: ID {$$ = CreateNewAstNode(strdup($1),"VariableDeclarator",NULL,NULL);}
                 | direct_declarator '(' parameter_list ')' {$$ = CreateNewAstNode("","FunctionDeclarator",$1,$3);}
                 | direct_declarator '(' ')'  {$$ = CreateNewAstNode("","FunctionDeclarator",$1,NULL);}
                 | ID '[' expr ']' {$$ = CreateNewAstNode("","ListDeclarator",CreateNewAstNode(strdup($1),"VariableDeclarator",NULL,NULL),$3);}
                 | ID '[' ']' {$$ = CreateNewAstNode(strdup($1),"ListDeclarator",NULL,NULL);}
                 ;
parameter_list: parameter {$$ = CreateNewAstNode("","__list__",$1,NULL);}
              | parameter_list ',' parameter {$$ = CreateNewAstNode("","__list__",$1,$3);}
              ;
parameter: type ID {$$ = CreateNewAstNode("","FunctionParameter",$1,CreateNewAstNode(strdup($2),"ParameterName",NULL,NULL));}
         ;
type: INT {$$ = CreateNewAstNode("INT","type",NULL,NULL);}
    | STR {$$ = CreateNewAstNode("STR","type",NULL,NULL);}
    | VOID {$$ = CreateNewAstNode("VOID","type",NULL,NULL);}
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
compound_statement: begin_scope end_scope {$$ = CreateNewAstNode("","CompoundStatement",NULL,NULL);}
                  | begin_scope statement_list end_scope {$$ = CreateNewAstNode("","CompoundStatement",$2,NULL);}
                  ;
begin_scope: '{' {$$=NULL;}
           ;
end_scope: '}'  {$$=NULL;}
         ;
statement_list: statement {$$ = $1;}
             | statement_list statement {$$ = CreateNewAstNode("","__list__",$1,$2);}
             ;
expression_statement: ';' {$$=NULL;}
                    | expr ';' {$$ = $1;}
                    ;
selection_statement: IF '(' expr ')' statement {$$ = CreateNewAstNode("","IF_Stmt",$3,$5);}
                   | IF '(' expr ')' statement ELSE statement {$$ = CreateNewAstNode("","IF_ELSE_Stmt",$3,CreateNewAstNode("","__list__",$5,$7));}
                   ;
iteration_statement: WHILE '(' expr ')' statement {$$ = CreateNewAstNode("","WhileStmt",$3,$5);}
                   ;
jump_statement: RETURN ';' {$$ = CreateNewAstNode("","ReturnStmt",NULL,NULL);}
              | RETURN expr ';' {$$ = CreateNewAstNode("","ReturnStmt",$2,NULL);}
              ;
print_statement: PRINT ';' {$$ = CreateNewAstNode("","PrintStmt",NULL,NULL);}
               | PRINT expr_list ';' {$$ = CreateNewAstNode("","PrintStmt",$2,NULL);}
               ;
scan_statement: SCAN id_list ';' {$$ = CreateNewAstNode("","ScanStmt",$2,NULL);}
              ;
expr: assign_expr {$$ = $1;}
    ;
assign_expr: cmp_expr {$$ = $1;}
           | ID ASSIGN assign_expr {$$ = CreateNewAstNode(strdup($2),"VariableAssign",CreateNewAstNode(strdup($1),"VariableRef",NULL,NULL),$3);}
           | ID '=' assign_expr {$$ = CreateNewAstNode("=","VariableEvalue",CreateNewAstNode(strdup($1),"VariableRef",NULL,NULL),$3);}
           | ID '[' expr ']' '=' assign_expr {$$ = CreateNewAstNode("=","ListEvalue",CreateNewAstNode(strdup($1),"ListRef",NULL,NULL),CreateNewAstNode("","__list__",$3,$6));}
           ;
cmp_expr: add_expr {$$ = $1;}
        | cmp_expr CMP add_expr {$$ = CreateNewAstNode(strdup($2),"Operator",$1,$3);}
        ;
add_expr: mul_expr {$$ = $1;}
        | add_expr '+' mul_expr {$$ = CreateNewAstNode("+","Operator",$1,$3);}
        | add_expr '-' mul_expr {$$ = CreateNewAstNode("-","Operator",$1,$3);}
        ;
mul_expr: primary_expr {$$ = $1;}
        | mul_expr '*' primary_expr {$$ = CreateNewAstNode("*","Operator",$1,$3);}
        | mul_expr '/' primary_expr {$$ = CreateNewAstNode("/","Operator",$1,$3);}
        | mul_expr '%' primary_expr {$$ = CreateNewAstNode("%","Operator",$1,$3);}
        | '-' primary_expr {$$ = CreateNewAstNode("-","Operator",$2,NULL);}
        ;
primary_expr: ID '(' expr_list ')' {$$ = CreateNewAstNode("","FunctionRef",CreateNewAstNode(strdup($1),"FunctionName",NULL,NULL),$3);}
            | ID '(' ')' {$$ = CreateNewAstNode(strdup($1),"FunctionRef",NULL,NULL);}
            | '(' expr ')' {$$ = $2;}
            | ID {$$ = CreateNewAstNode(strdup($1),"VariableRef",NULL,NULL);}
            | initializer {$$ = $1;}
            | ID '[' expr ']' {$$ = CreateNewAstNode(strdup($1),"ListRef",$3,NULL);}
            ;
expr_list: expr {$$ = $1;}
         | expr_list ',' expr {$$ = CreateNewAstNode("","__list__",$1,$3);}

id_list: ID {$$ = CreateNewAstNode(strdup($1),"VariableRef",NULL,NULL);}
       | id_list ',' ID {$$ = CreateNewAstNode("","__list__",$1,CreateNewAstNode(strdup($3),"VariableRef",NULL,NULL));}
       ;
%%

// void yyerror(char *s, ...)
// {
//   fprintf(stderr, "%d: error: ", yylineno);
// }
=======
%{
  #include"ast.h"
  //int yydebug=1;
  extern ast_node astRoot;
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

%type <ast_node> program external_declaration function_definition declaration init_declarator_list init_declarator intstr_list initializer declarator direct_declarator parameter_list parameter type statement compound_statement statement_list expression_statement selection_statement iteration_statement jump_statement print_statement scan_statement expr expr_list add_expr assign_expr cmp_expr mul_expr primary_expr id_list begin_scope end_scope

%%
program: external_declaration  {$$ = $1;}
       | program external_declaration  {$$ = CreateNewAstNode("","__list__",$1,$2);}
       | program EOP {astRoot = $1;return;}
       ;
external_declaration: function_definition {$$ = CreateNewAstNode("","ExternalDeclaration",$1,NULL);}
                    | declaration {$$ = CreateNewAstNode("","ExternalDeclaration",$1,NULL);}
                    ;
function_definition: type declarator compound_statement {$$ = CreateNewAstNode("","FunctionDefinition",$1,CreateNewAstNode("","__list__",$2,$3));}
                    ;
declaration: type init_declarator_list ';' {$$ = CreateNewAstNode("","__list__",$1,$2);}
           ;
init_declarator_list: init_declarator {$$ = CreateNewAstNode("","__list__",$1,NULL);}
                    | init_declarator_list ',' init_declarator {$$ = CreateNewAstNode("","__list__",$1,$3);}
                    ;
init_declarator: declarator {$$ = CreateNewAstNode("","InitDeclarator",$1,NULL);}
               | declarator '=' add_expr {$$ = CreateNewAstNode("","InitDeclarator",$1,$3);}
               | declarator '=' '{' intstr_list '}' {$$ = CreateNewAstNode("","InitDeclarator",$1,$4);}
               ;
intstr_list: initializer {$$ = CreateNewAstNode("","__list__",$1,NULL);}
           | intstr_list ',' initializer {$$ = CreateNewAstNode("","__list__",$1,$3);}
           ;
initializer: NUMBER {$$ = CreateNewAstNode(strdup($1),"IntergerInteral",NULL,NULL);}
           | STRING {$$ = CreateNewAstNode(strdup($1),"StringInteral",NULL,NULL);}
           ;
declarator: direct_declarator {$$ = CreateNewAstNode("","__list__",$1,NULL);}
          ;
direct_declarator: ID {$$ = CreateNewAstNode(strdup($1),"VariableDeclarator",NULL,NULL);}
                 | direct_declarator '(' parameter_list ')' {$$ = CreateNewAstNode("","FunctionDeclarator",$1,$3);}
                 | direct_declarator '(' ')'  {$$ = CreateNewAstNode("","FunctionDeclarator",$1,NULL);}
                 | ID '[' expr ']' {$$ = CreateNewAstNode("","ListDeclarator",CreateNewAstNode(strdup($1),"VariableDeclarator",NULL,NULL),$3);}
                 | ID '[' ']' {$$ = CreateNewAstNode(strdup($1),"ListDeclarator",NULL,NULL);}
                 ;
parameter_list: parameter {$$ = CreateNewAstNode("","__list__",$1,NULL);}
              | parameter_list ',' parameter {$$ = CreateNewAstNode("","__list__",$1,$3);}
              ;
parameter: type ID {$$ = CreateNewAstNode("","FunctionParameter",$1,CreateNewAstNode(strdup($2),"ParameterName",NULL,NULL));}
         ;
type: INT {$$ = CreateNewAstNode("INT","type",NULL,NULL);}
    | STR {$$ = CreateNewAstNode("STR","type",NULL,NULL);}
    | VOID {$$ = CreateNewAstNode("VOID","type",NULL,NULL);}
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
compound_statement: begin_scope end_scope {$$ = CreateNewAstNode("","CompoundStatement",NULL,NULL);}
                  | begin_scope statement_list end_scope {$$ = CreateNewAstNode("","CompoundStatement",$2,NULL);}
                  ;
begin_scope: '{' {$$=NULL;}
           ;
end_scope: '}'  {$$=NULL;}
         ;
statement_list: statement {$$ = $1;}
             | statement_list statement {$$ = CreateNewAstNode("","__list__",$1,$2);}
             ;
expression_statement: ';' {$$=NULL;}
                    | expr ';' {$$ = $1;}
                    ;
selection_statement: IF '(' expr ')' statement {$$ = CreateNewAstNode("","IF_Stmt",$3,$5);}
                   | IF '(' expr ')' statement ELSE statement {$$ = CreateNewAstNode("","IF_ELSE_Stmt",$3,CreateNewAstNode("","__list__",$5,$7));}
                   ;
iteration_statement: WHILE '(' expr ')' statement {$$ = CreateNewAstNode("","WhileStmt",$3,$5);}
                   ;
jump_statement: RETURN ';' {$$ = CreateNewAstNode("","ReturnStmt",NULL,NULL);}
              | RETURN expr ';' {$$ = CreateNewAstNode("","ReturnStmt",$2,NULL);}
              ;
print_statement: PRINT ';' {$$ = CreateNewAstNode("","PrintStmt",NULL,NULL);}
               | PRINT expr_list ';' {$$ = CreateNewAstNode("","PrintStmt",$2,NULL);}
               ;
scan_statement: SCAN id_list ';' {$$ = CreateNewAstNode("","ScanStmt",$2,NULL);}
              ;
expr: assign_expr {$$ = $1;}
    ;
assign_expr: cmp_expr {$$ = $1;}
           | ID ASSIGN assign_expr {$$ = CreateNewAstNode(strdup($2),"VariableAssign",CreateNewAstNode(strdup($1),"VariableRef",NULL,NULL),$3);}
           | ID '=' assign_expr {$$ = CreateNewAstNode("=","VariableEvalue",CreateNewAstNode(strdup($1),"VariableRef",NULL,NULL),$3);}
           | ID '[' expr ']' '=' assign_expr {$$ = CreateNewAstNode("=","ListEvalue",CreateNewAstNode(strdup($1),"ListRef",NULL,NULL),CreateNewAstNode("","__list__",$3,$6));}
           ;
cmp_expr: add_expr {$$ = $1;}
        | cmp_expr CMP add_expr {$$ = CreateNewAstNode(strdup($2),"Operator",$1,$3);}
        ;
add_expr: mul_expr {$$ = $1;}
        | add_expr '+' mul_expr {$$ = CreateNewAstNode("+","Operator",$1,$3);}
        | add_expr '-' mul_expr {$$ = CreateNewAstNode("-","Operator",$1,$3);}
        ;
mul_expr: primary_expr {$$ = $1;}
        | mul_expr '*' primary_expr {$$ = CreateNewAstNode("*","Operator",$1,$3);}
        | mul_expr '/' primary_expr {$$ = CreateNewAstNode("/","Operator",$1,$3);}
        | mul_expr '%' primary_expr {$$ = CreateNewAstNode("%","Operator",$1,$3);}
        | '-' primary_expr {$$ = CreateNewAstNode("-","Operator",$2,NULL);}
        ;
primary_expr: ID '(' expr_list ')' {$$ = CreateNewAstNode("","FunctionRef",CreateNewAstNode(strdup($1),"FunctionName",NULL,NULL),$3);}
            | ID '(' ')' {$$ = CreateNewAstNode(strdup($1),"FunctionRef",NULL,NULL);}
            | '(' expr ')' {$$ = $2;}
            | ID {$$ = CreateNewAstNode(strdup($1),"VariableRef",NULL,NULL);}
            | initializer {$$ = $1;}
            | ID '[' expr ']' {$$ = CreateNewAstNode(strdup($1),"ListRef",$3,NULL);}
            ;
expr_list: expr {$$ = $1;}
         | expr_list ',' expr {$$ = CreateNewAstNode("","__list__",$1,$3);}

id_list: ID {$$ = CreateNewAstNode(strdup($1),"VariableRef",NULL,NULL);}
       | id_list ',' ID {$$ = CreateNewAstNode("","__list__",$1,CreateNewAstNode(strdup($3),"VariableRef",NULL,NULL));}
       ;
%%

// void yyerror(char *s, ...)
// {
//   fprintf(stderr, "%d: error: ", yylineno);
// }
>>>>>>> 8dad9ee129215d834500947d610d65c5aead218d
