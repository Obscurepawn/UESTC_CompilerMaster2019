#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MaxRaw 2000
#define MaxLex 100
#define LETTER 0
#define DIGIT 1
#define DOLLAR 2
#define UNDERLINE 3
#define QUOTATION 4
#define UNKNOWN -2

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

char *keyword[] =
    {"boolean", "byte", "char", "double", "false", "float", "int", "long",
     "new", "null", "short", "true", "void", "instanceof", "break",
     "case", "catch", "continue", "default", "do", "else", "for", "if",
     "return", "switch", "try", "while", "finally", "throw", "this",
     "super", "abstract", "final", "namtive", "private", "protected",
     "public", "static", "synchronized", "transient", "volatile",
     "class", "extends", "implements", "interface", "package", "import",
     "throws", "END"};

char lexeme[MaxLex];
int LexLength;
int TypeOfLexeme;
int TypeOfChar;
int err;

char *DeleteNote(char *LineCode);
FILE *OpenFile(char *filename);
char *ReadJavaCodeInLine(FILE *fp);
int GetCharFromLineCode(char *LineCode, int last_read);
int CharClassJudgement(char *CharNow);
void PutCharIntoLexeme(char *CharNow);
void CheckKeyword();
int CheckSymbol(char *CharNow);
void LexClassJudgeMent(char *LineCode);

int main()
{
    char *FileName = (char *)malloc(100);
    char *LineCode;
    printf("Please input your filename:");
    scanf("%s", FileName);
    fflush(stdin);
    FILE *fp = OpenFile(FileName);
    if (!fp)
    {
        printf("NO SUCH FILE\n");
        return -1;
    }
    while (feof(fp) == 0)
    {
        err = 0;
        LineCode = ReadJavaCodeInLine(fp);
        LexClassJudgeMent(LineCode);
        free(LineCode);
    }
    system("pause");
    return 0;
}

char *DeleteNote(char *LineCode)
{
    int ReadPlace = 0;
    int buffer_index = 0;
    int length = strlen(LineCode);
    char *buffer = (char *)malloc(MaxRaw);
    while (ReadPlace < length - 1)
    {
        do
        {
            if (LineCode[ReadPlace] == '/')
            {
                if (LineCode[ReadPlace + 1] == '/')
                {
                    buffer[ReadPlace] = '\0';
                    return buffer;
                }
                else
                {
                    ReadPlace++;
                    while (LineCode[ReadPlace] != '/')
                    {
                        ReadPlace++;
                    }
                    ReadPlace++;
                }
            }
        } while (LineCode[ReadPlace] == '/');
        buffer[buffer_index++] = LineCode[ReadPlace++];
    }
    buffer[buffer_index] = '\0';
    return buffer;
}

FILE *OpenFile(char *filename)
{
    // if (strstr(filename, ".java") == NULL)
    // {
    //     printf("Something goes wrong:This file isn't java code");
    // }
    FILE *fp = fopen(filename, "r");
    if (fp)
        return fp;
    else
        return NULL;
}

//this LineCode includes a '\0' in the end of the string(without '\0')
char *ReadJavaCodeInLine(FILE *fp)
{
    char *temp = (char *)malloc(MaxRaw);
    fgets(temp, MaxRaw, fp);
    char *LineCode = DeleteNote(temp);
    free(temp);
    return LineCode;
}

int GetCharFromLineCode(char *LineCode, int last_read)
{
    char *tmp = LineCode + last_read + 1;
    if (!isspace(*tmp))
        return (tmp - LineCode);
    while (isspace((*tmp)))
        tmp++;
    if (isspace(*(tmp - 1)))
        return (tmp - LineCode - 1);
}

int CharClassJudgement(char *CharNow)
{
    if (isdigit(*CharNow))
        return DIGIT;
    else if (isalpha(*CharNow))
        return LETTER;
    else if ((*CharNow) == '$')
        return DOLLAR;
    else if ((*CharNow) == '_')
        return UNDERLINE;
    else if ((*CharNow) == '"')
        return QUOTATION;
    else if ((*CharNow) == EOF)
        return EOF;
    else
        return UNKNOWN;
}

void PutCharIntoLexeme(char *CharNow)
{
    lexeme[LexLength++] = *(CharNow);
    lexeme[LexLength] = '\0';
    return;
}

void CheckKeyword()
{
    int index = 0;
    while (keyword[index] != "END")
    {
        if (strcmp(lexeme, keyword[index]) == 0)
        {
            TypeOfLexeme = 258 + index;
            return;
        }
        index++;
    }
    return;
}

int CheckSymbol(char *CharNow)
{
    switch ((*CharNow))
    {
    case '"':
    case '.':
    case '(':
    case ')':
    case '{':
    case '}':
    case ',':
    case ';':
    case '[':
    case ']':
    case '?':
    case ':':
        TypeOfLexeme = *CharNow;
        break;
    case '%':
        TypeOfLexeme = '%';
        if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = MODEQU;
        }
        break;
    case '^':
        TypeOfLexeme = '^';
        if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = NOTEQU;
        }
        break;
    case '*':
        TypeOfLexeme = '*';
        if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = MULEQU;
        }
        break;
    case '/':
        TypeOfLexeme = '/';
        if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = DIVIDEEQU;
        }
        break;
    case '+':
        TypeOfLexeme = '+';
        if (*(CharNow + 1) == '+')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = ADDSELF;
        }
        else if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = ADDEQU;
        }
        break;
    case '-':
        TypeOfLexeme = '-';
        if (*(CharNow + 1) == '-')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = MINUSSELF;
        }
        else if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = MINUSEQU;
        }
        break;
    case '>':
        TypeOfLexeme = '>';
        if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = GEQU;
        }
        else if (*(CharNow + 1) == '>')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = RIGHT_BITWISE;
            if (*(CharNow + 2) == '>')
            {
                PutCharIntoLexeme(CharNow + 2);
                TypeOfLexeme = G_RIGHT_BITWISE;
                if (*(CharNow + 3) == '=')
                {
                    PutCharIntoLexeme(CharNow + 3);
                    TypeOfLexeme = G_RIGHT_BITWISE_EQU;
                }
            }
            else if (*(CharNow + 2) == '=')
            {
                PutCharIntoLexeme(CharNow + 2);
                TypeOfLexeme = RIGHT_BITWISE_EQU;
            }
        }
        break;
    case '<':
        TypeOfLexeme = '<';
        if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = LEQU;
        }
        else if (*(CharNow + 1) == '<')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = LEFT_BITWISE;
            if (*(CharNow + 2) == '=')
            {
                PutCharIntoLexeme(CharNow + 2);
                TypeOfLexeme = LEFT_BITWISE_EQU;
            }
        }
        break;
    case '=':
        TypeOfLexeme = '=';
        if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = EQU;
        }
        break;
    case '!':
        TypeOfLexeme = '!';
        if (*(CharNow + 1) == '=')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = NEQ;
        }
        break;
    case '&':
        TypeOfLexeme = '&';
        if (*(CharNow + 1) == '&')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = AND;
        }
        break;
    case '|':
        TypeOfLexeme = '|';
        if (*(CharNow + 1) == '|')
        {
            PutCharIntoLexeme(CharNow + 1);
            TypeOfLexeme = EQU;
        }
    case EOF:
        TypeOfLexeme = EOF;
        break;
    default:
        err = 1;
        // printf("\nERROR:unknown word:%c\n", *CharNow);
        TypeOfLexeme = ERROR;
        break;
    }
    return TypeOfLexeme;
}

void LexClassJudgeMent(char *LineCode)
{
    int ReadPlace = -1;
    int Length = strlen(LineCode);
    LexLength = 0;
    ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
    if (*(ReadPlace + LineCode) == ' ' || *(ReadPlace + LineCode) == '\t' || *(LineCode + ReadPlace) == '\n' || *(LineCode + ReadPlace) == EOF)
        ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
    TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
    PutCharIntoLexeme(LineCode + ReadPlace);
    while (ReadPlace < Length)
    {
        switch (TypeOfChar)
        {
        case LETTER:
        case DOLLAR:
        case UNDERLINE:
            while (1)
            {
                ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
                TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
                if (TypeOfChar != LETTER && TypeOfChar != DOLLAR && TypeOfChar != UNDERLINE && TypeOfLexeme != DIGIT)
                    break;
                PutCharIntoLexeme(LineCode + ReadPlace);
            }
            TypeOfLexeme = ID;
            CheckKeyword();
            break;
        case DIGIT:
            while (1)
            {
                ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
                TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
                if (TypeOfChar != DIGIT || TypeOfChar != LETTER)
                    break;
                PutCharIntoLexeme(LineCode + ReadPlace);
            }
            if (lexeme[0] == '0')
            {
                TypeOfLexeme = OCT_INT;
                if (strchr(lexeme, '.'))
                    TypeOfLexeme = OCT_FLOAT;
            }
            if (strstr(lexeme, "0x"))
            {
                TypeOfChar = HEX_INT;
                if (strchr(lexeme, '.'))
                    TypeOfLexeme = HEX_FLOAT;
            }
            else
            {
                TypeOfLexeme = INT;
                if (strchr(lexeme, '.'))
                    TypeOfLexeme = FLOAT;
            }
            break;
        case QUOTATION:
            while (1)
            {
                ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
                TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
                if (TypeOfChar == QUOTATION)
                    break;
                PutCharIntoLexeme(LineCode + ReadPlace);
            }
            char temp = '"';
            PutCharIntoLexeme(&temp);
            TypeOfLexeme = STRING;
        case UNKNOWN:
            CheckSymbol(LineCode + ReadPlace);
            ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
            TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
            break;
        case EOF:
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = '\0';
            TypeOfLexeme = EOF;
            break;
        }
        if (!err)
            printf("<%3d,%s>\n\n", TypeOfLexeme, lexeme);
        LexLength = 0;
        if (TypeOfLexeme == EQU || TypeOfLexeme == GEQU || TypeOfLexeme == LEQU || TypeOfLexeme == NEQ || TypeOfLexeme == ADDSELF || TypeOfLexeme == MINUSSELF || TypeOfLexeme == AND || TypeOfLexeme == OR || TypeOfLexeme == RIGHT_BITWISE || TypeOfLexeme == LEFT_BITWISE || TypeOfLexeme == DIVIDEEQU || TypeOfLexeme == MULEQU || TypeOfLexeme == ADDEQU || TypeOfLexeme == MINUSEQU || TypeOfLexeme == MODEQU || TypeOfLexeme == ANDEQU || TypeOfLexeme == OREQU || TypeOfLexeme == NOTEQU)
        {
            ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
            TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
        }
        else if (TypeOfLexeme == G_RIGHT_BITWISE || TypeOfLexeme == LEFT_BITWISE_EQU || TypeOfLexeme == RIGHT_BITWISE_EQU)
        {
            ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
            ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
            TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
        }
        else if (TypeOfLexeme == G_RIGHT_BITWISE_EQU)
        {
            ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
            ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
            ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
            TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
        }
        if (*(LineCode + ReadPlace) == ' ' || *(LineCode + ReadPlace) == '\t')
        {
            ReadPlace = GetCharFromLineCode(LineCode, ReadPlace);
            TypeOfChar = CharClassJudgement(LineCode + ReadPlace);
        }
        PutCharIntoLexeme(LineCode + ReadPlace);
    }
    return;
}