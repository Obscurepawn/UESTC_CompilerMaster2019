<<<<<<< HEAD
%option noyywrap yylineno 

%{
    #include<string.h>
    #include<stdio.h>
    enum yytokentype
   {
     NUMBER = 258,
     STRING,
     ID,
     INT,
     STR,
     VOID,
     IF,
     ELSE,
     WHILE,
     RETURN,
     PRINT,
     SCAN,
     CMP,
     ASSIGN
   };
    char *keyword[] = {"str","void","if","else","while","return","print","scan","int"};
    int yycol = 0;
%}

%%

"while"             {yycol += strlen(yytext);return WHILE;}
"int"               {yycol += strlen(yytext);return INT;}
"str"               {yycol += strlen(yytext);return STR;}
"void"              {yycol += strlen(yytext);return VOID;}
"if"                {yycol += strlen(yytext);return IF;}
"else"              {yycol += strlen(yytext);return ELSE;}
"return"            {yycol += strlen(yytext);return RETURN;}
"print"             {yycol += strlen(yytext);return PRINT;}
"scan"              {yycol += strlen(yytext);return SCAN;}
"<" |
">" |
">=" |
"<=" |
"=="                {yycol += strlen(yytext);return CMP;}
":=" |
"+=" |
"/=" |
"-=" |
"*="                {yycol += strlen(yytext);return ASSIGN;}
"+" |
"-" |
"*" |
"/" |
"%" |
";" |
"=" |
"[" |
"]" |
"(" |
")" |
"{" |
"}" |
"," |
"q"                  {yycol += strlen(yytext);return yytext[0];}
[0-9]+               {yycol += strlen(yytext);return NUMBER;}
[a-zA-Z][a-zA-Z0-9_]* {yycol += strlen(yytext);return ID;}
\"(\\.|[^"])*\"     {yycol += strlen(yytext);return STRING;}
("//".*)|("/*".*"*/")  
\n                  {yycol = 0;}
[ \t]*              {yycol += strlen(yytext);}
<<EOF>>             {return EOF;}
%%

int yyerror(char *text){
    fprintf(stderr,"error:%s\n",text);
    return 0;
}

=======
%option noyywrap yylineno 

%{
    #include<string.h>
    #include<stdio.h>
    enum yytokentype
   {
     NUMBER = 258,
     STRING,
     ID,
     INT,
     STR,
     VOID,
     IF,
     ELSE,
     WHILE,
     RETURN,
     PRINT,
     SCAN,
     CMP,
     ASSIGN
   };
    char *keyword[] = {"str","void","if","else","while","return","print","scan","int"};
    int yycol = 0;
%}

%%

"while"             {yycol += strlen(yytext);return WHILE;}
"int"               {yycol += strlen(yytext);return INT;}
"str"               {yycol += strlen(yytext);return STR;}
"void"              {yycol += strlen(yytext);return VOID;}
"if"                {yycol += strlen(yytext);return IF;}
"else"              {yycol += strlen(yytext);return ELSE;}
"return"            {yycol += strlen(yytext);return RETURN;}
"print"             {yycol += strlen(yytext);return PRINT;}
"scan"              {yycol += strlen(yytext);return SCAN;}
"<" |
">" |
">=" |
"<=" |
"=="                {yycol += strlen(yytext);return CMP;}
":=" |
"+=" |
"/=" |
"-=" |
"*="                {yycol += strlen(yytext);return ASSIGN;}
"+" |
"-" |
"*" |
"/" |
"%" |
";" |
"=" |
"[" |
"]" |
"(" |
")" |
"{" |
"}" |
"," |
"q"                  {yycol += strlen(yytext);return yytext[0];}
[0-9]+               {yycol += strlen(yytext);return NUMBER;}
[a-zA-Z][a-zA-Z0-9_]* {yycol += strlen(yytext);return ID;}
\"(\\.|[^"])*\"     {yycol += strlen(yytext);return STRING;}
("//".*)|("/*".*"*/")  
\n                  {yycol = 0;}
[ \t]*              {yycol += strlen(yytext);}
<<EOF>>             {return EOF;}
%%

int yyerror(char *text){
    fprintf(stderr,"error:%s\n",text);
    return 0;
}

>>>>>>> 8dad9ee129215d834500947d610d65c5aead218d
