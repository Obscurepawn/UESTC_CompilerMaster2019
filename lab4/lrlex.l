%option noyywrap yylineno

%{
    #include"ast.h"
    #include"lrparser.tab.h"
%}

%%

"while"             {return WHILE;}
"int"               {return INT;}
"str"               {return STR;}
"void"              {return VOID;}
"if"                {return IF;} 
"else"              {return ELSE;}
"return"            {return RETURN;}
"print"             {return PRINT;}
"scan"              {return SCAN;}
"<" |
">" |
">=" |
"<=" |
"=="                {yylval.save_yytext=strdup(yytext);return CMP;}
":=" |
"+=" |
"/=" |
"-=" |
"*="                {yylval.save_yytext=strdup(yytext);return ASSIGN;}
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
"," |
"}"                  {yylval.save_yytext=strdup(yytext);return yytext[0];}
[0-9]+               {yylval.save_yytext=strdup(yytext);return NUMBER;}
[a-zA-Z][a-zA-Z0-9_]* {yylval.save_yytext=strdup(yytext);return ID;}
\"(\\.|[^"])*\"     {yylval.save_yytext=strdup(yytext);return STRING;}
("//".*)|("/*".*"*/")  |
\n  |               
[ \t]*      
<<EOF>>             {return EOP;} //EOF:End OF Programme
%%

int yyerror(char *text){
    fprintf(stderr,"error:%s\nline:%d\nyytext:%s",text,yylineno,yytext);
    return 0;
}