<<<<<<< HEAD
%option noyywrap 

%{
    #include<string.h>
    #include<stdio.h>
    char *keyword[] =
    {"boolean", "byte", "char", "double", "false", "float", "int", "long",
     "new", "null", "short", "true", "void", "instanceof", "break",
     "case", "catch", "continue", "default", "do", "else", "for", "if",
     "return", "switch", "try", "while", "finally", "throw", "this",
     "super", "abstract", "final", "namtive", "private", "protected",
     "public", "static", "synchronized", "transient", "volatile",
     "class", "extends", "implements", "interface", "package", "import",
     "throws", "END"};
     #define INT 306
     #define HEX_INT 307
     #define OCT_INT 308
     #define HEX_FLOAT 309
     #define OCT_FLOAT 310
     #define FLOAT 311
     #define STRING 312
     #define ID 313
     #define EQU 314
     #define GEQU 315
     #define LEQU 316
     #define NEQ 317
     #define ERROR 318
     #define ADDSELF 319
     #define MINUSSELF 320
     #define DIVIDEEQU 321
     #define MULEQU 322
     #define ADDEQU 323
     #define MINUSEQU 324
     #define MODEQU 325
     #define AND 326
     #define OR 327
     #define ANDEQU 328
     #define OREQU 329
     #define NOTEQU 330
     #define RIGHT_BITWISE 331    //always fill in sign symbol(0/1) at the top
     #define LEFT_BITWISE 332     //always fill in 0 at the buttom
     #define LEFT_BITWISE_EQU 333 //after moving the bitwise,let the variable's value to be it .
     #define RIGHT_BITWISE_EQU 334
     #define G_RIGHT_BITWISE 335 //always fill in 0 at the top
     #define G_RIGHT_BITWISE_EQU 336 //after moving the bitwise,let the variable's value to be it .
     #define OVERRIDE 337
     #define COMMENT -3
     #define SPACE -4
     int flag = 1;
%}

%%
\0[xX][0-9]*\.[0-9]+|[0-9]+\. {printf("<  %d  ,  %s  >\n",HEX_FLOAT,yytext);}
\0[0-9]*\.[0-9]+|[0-9]+\.     {printf("<  %d  ,  %s  >\n",OCT_FLOAT,yytext);}
[0-9]*\.[0-9]+|[0-9]+\.       {printf("<  %d  ,  %s  >\n",FLOAT,yytext);}
\0[xX][0-9]*                  {printf("<  %d  ,  %s  >\n",HEX_INT,yytext);}
\0[0-9]*                      {printf("<  %d  ,  %s  >\n",OCT_INT,yytext);}
[0-9]*                        {printf("<  %d  ,  %s  >\n",INT,yytext);}
[a-zA-Z$_]+  {
              flag = 1;
              for (int i = 0;i<48;++i){
                  if(strcmp(yytext,keyword[i])==0){
                      printf("<  %d  ,  %s  >\n",258+i,yytext);
                      flag = 0;
                      break;
                  }
             }
             if (flag){
                      printf("<  %d  ,  %s  >\n",ID,yytext);
                      break;
                  }
            }
"++"        {printf("<  %d  ,  ++  >\n",ADDSELF);}
"+="        {printf("<  %d  ,  +=  >\n",ADDEQU);}
"--"        {printf("<  %d  ,  --  >\n",MINUSSELF);}
"-="        {printf("<  %d  ,  -=  >\n",MINUSEQU);}
"/="        {printf("<  %d  ,  -=  >\n",DIVIDEEQU);}
"*="        {printf("<  %d  ,  -=  >\n",MULEQU);}
"%="        {printf("<  %d  ,  -=  >\n",MODEQU);}
"^="        {printf("<  %d  ,  -=  >\n",NOTEQU);}
"&="        {printf("<  %d  ,  -=  >\n",ANDEQU);}
"|="        {printf("<  %d  ,  -=  >\n",OREQU);}
">="        {printf("<  %d  ,  >=  >\n",GEQU);}
"<="        {printf("<  %d  ,  <=  >\n",LEQU);}
"=="        {printf("<  %d  ,  ==  >\n",EQU);}
"!="        {printf("<  %d  ,  !=  >\n",NEQ);}
"&&"        {printf("<  %d  ,  &&  >\n",AND);}
"||"        {printf("<  %d  ,  ||  >\n",OR);} 
">>>"       {printf("<  %d  ,  >>>  >\n",G_RIGHT_BITWISE);} 
">>"        {printf("<  %d  ,  >>  >\n",RIGHT_BITWISE);} 
"<<"        {printf("<  %d  ,  <<  >\n",LEFT_BITWISE);} 
">>="       {printf("<  %d  ,  >>  >\n",RIGHT_BITWISE_EQU);} 
"<<="       {printf("<  %d  ,  <<  >\n",LEFT_BITWISE_EQU);} 
">>>="      {printf("<  %d  ,  >>>  >\n",G_RIGHT_BITWISE_EQU);} 
\"(\\.|[^"])*\"     {printf("<  %d  ,  %s  >\n",STRING,yytext);} 
[\+\-\*&().{}[,;\]\\=<>""] {printf("<  %d  ,  %s  >\n",yytext[0],yytext);}
[ \t]+      {printf("");}
("//".*)|("/*".*"*/")  {printf("");}
\n          {printf("");}
"@override" {printf("<  %d  ,  @override  >\n",OVERRIDE);}
.           {printf("Disallowed word\n");return ERROR;}  
%%

int main(int argc,char **argv){
    if(argc<2){
        printf("NEED FILENAME\n");
        return -1;
    }
    if(!(yyin = fopen(argv[1],"r"))){
        printf("ERROR:NO SUCH FILE!\n");
        return -2;
    }
    yylex();
    return 0;
=======
%option noyywrap 

%{
    #include<string.h>
    #include<stdio.h>
    char *keyword[] =
    {"boolean", "byte", "char", "double", "false", "float", "int", "long",
     "new", "null", "short", "true", "void", "instanceof", "break",
     "case", "catch", "continue", "default", "do", "else", "for", "if",
     "return", "switch", "try", "while", "finally", "throw", "this",
     "super", "abstract", "final", "namtive", "private", "protected",
     "public", "static", "synchronized", "transient", "volatile",
     "class", "extends", "implements", "interface", "package", "import",
     "throws", "END"};
     #define INT 306
     #define HEX_INT 307
     #define OCT_INT 308
     #define HEX_FLOAT 309
     #define OCT_FLOAT 310
     #define FLOAT 311
     #define STRING 312
     #define ID 313
     #define EQU 314
     #define GEQU 315
     #define LEQU 316
     #define NEQ 317
     #define ERROR 318
     #define ADDSELF 319
     #define MINUSSELF 320
     #define DIVIDEEQU 321
     #define MULEQU 322
     #define ADDEQU 323
     #define MINUSEQU 324
     #define MODEQU 325
     #define AND 326
     #define OR 327
     #define ANDEQU 328
     #define OREQU 329
     #define NOTEQU 330
     #define RIGHT_BITWISE 331    //always fill in sign symbol(0/1) at the top
     #define LEFT_BITWISE 332     //always fill in 0 at the buttom
     #define LEFT_BITWISE_EQU 333 //after moving the bitwise,let the variable's value to be it .
     #define RIGHT_BITWISE_EQU 334
     #define G_RIGHT_BITWISE 335 //always fill in 0 at the top
     #define G_RIGHT_BITWISE_EQU 336 //after moving the bitwise,let the variable's value to be it .
     #define OVERRIDE 337
     #define COMMENT -3
     #define SPACE -4
     int flag = 1;
%}

%%
\0[xX][0-9]*\.[0-9]+|[0-9]+\. {printf("<  %d  ,  %s  >\n",HEX_FLOAT,yytext);}
\0[0-9]*\.[0-9]+|[0-9]+\.     {printf("<  %d  ,  %s  >\n",OCT_FLOAT,yytext);}
[0-9]*\.[0-9]+|[0-9]+\.       {printf("<  %d  ,  %s  >\n",FLOAT,yytext);}
\0[xX][0-9]*                  {printf("<  %d  ,  %s  >\n",HEX_INT,yytext);}
\0[0-9]*                      {printf("<  %d  ,  %s  >\n",OCT_INT,yytext);}
[0-9]*                        {printf("<  %d  ,  %s  >\n",INT,yytext);}
[a-zA-Z$_]+  {
              flag = 1;
              for (int i = 0;i<48;++i){
                  if(strcmp(yytext,keyword[i])==0){
                      printf("<  %d  ,  %s  >\n",258+i,yytext);
                      flag = 0;
                      break;
                  }
             }
             if (flag){
                      printf("<  %d  ,  %s  >\n",ID,yytext);
                      break;
                  }
            }
"++"        {printf("<  %d  ,  ++  >\n",ADDSELF);}
"+="        {printf("<  %d  ,  +=  >\n",ADDEQU);}
"--"        {printf("<  %d  ,  --  >\n",MINUSSELF);}
"-="        {printf("<  %d  ,  -=  >\n",MINUSEQU);}
"/="        {printf("<  %d  ,  -=  >\n",DIVIDEEQU);}
"*="        {printf("<  %d  ,  -=  >\n",MULEQU);}
"%="        {printf("<  %d  ,  -=  >\n",MODEQU);}
"^="        {printf("<  %d  ,  -=  >\n",NOTEQU);}
"&="        {printf("<  %d  ,  -=  >\n",ANDEQU);}
"|="        {printf("<  %d  ,  -=  >\n",OREQU);}
">="        {printf("<  %d  ,  >=  >\n",GEQU);}
"<="        {printf("<  %d  ,  <=  >\n",LEQU);}
"=="        {printf("<  %d  ,  ==  >\n",EQU);}
"!="        {printf("<  %d  ,  !=  >\n",NEQ);}
"&&"        {printf("<  %d  ,  &&  >\n",AND);}
"||"        {printf("<  %d  ,  ||  >\n",OR);} 
">>>"       {printf("<  %d  ,  >>>  >\n",G_RIGHT_BITWISE);} 
">>"        {printf("<  %d  ,  >>  >\n",RIGHT_BITWISE);} 
"<<"        {printf("<  %d  ,  <<  >\n",LEFT_BITWISE);} 
">>="       {printf("<  %d  ,  >>  >\n",RIGHT_BITWISE_EQU);} 
"<<="       {printf("<  %d  ,  <<  >\n",LEFT_BITWISE_EQU);} 
">>>="      {printf("<  %d  ,  >>>  >\n",G_RIGHT_BITWISE_EQU);} 
\"(\\.|[^"])*\"     {printf("<  %d  ,  %s  >\n",STRING,yytext);} 
[\+\-\*&().{}[,;\]\\=<>""] {printf("<  %d  ,  %s  >\n",yytext[0],yytext);}
[ \t]+      {printf("");}
("//".*)|("/*".*"*/")  {printf("");}
\n          {printf("");}
"@override" {printf("<  %d  ,  @override  >\n",OVERRIDE);}
.           {printf("Disallowed word\n");return ERROR;}  
%%

int main(int argc,char **argv){
    if(argc<2){
        printf("NEED FILENAME\n");
        return -1;
    }
    if(!(yyin = fopen(argv[1],"r"))){
        printf("ERROR:NO SUCH FILE!\n");
        return -2;
    }
    yylex();
    return 0;
>>>>>>> 8dad9ee129215d834500947d610d65c5aead218d
}