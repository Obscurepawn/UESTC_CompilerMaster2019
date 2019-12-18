//#include "ast.h"
#include "queue.h"
#include "makeAst.h"
#include "HashMap.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

// #include "inttypes.h"
// #include "llvm-c/Core.h"
// #include "llvm-c/ExecutionEngine.h"
// #include "llvm-c/Target.h"
// #include "llvm-c/Analysis.h"
// #include "llvm-c/BitWriter.h"

#define MAX_FILENAME 255
#define MAX_NUM 255

extern ptrast astRoot; //astRoot from main.c
extern int tabNum;
pqe CallFunction;   //declarate called function
pqe GlobalContext;  //global context
pqe FuncHead;       //function head
pqe FuncBody;       //funciton body
int GlobalFlag;     //to judge whether the text is included in the global context
int ConstStringNum; //to record the num of the constant string
int tempNum = 0;    //to record the num of the temperary variable in a function
ptrhs symbolTable;  //symbol table
ptrSt stringRecord; //record the local string whether has declared
ptrSt funcRecord;   //record the declared function name,to avoid multy-declaration
char *Tab = NULL;
char *CompilerFile = NULL;
//char *ReturnType = NULL;

void tabSpace();
char *getC_FileName();
char *getllvmFileName(char *filename);
char *getFileName();
char *sampleOsType();
char *ReturnOSType(char *Buffer, char *LLVMcode);
char *Init();
bool isNumber(char *number);

int genCode(ptrast root);
int genFuncDef(ptrast root);
int genVarDec(ptrast root);
int genStatement(ptrast root);
char *genExpr(ptrast root);

int alignJudge(char *bitType);
char *bitTypeJudge(char *Type);
char *getLLVMalloca(char *bitType);
char *getLLVMstore(char *bitType, char *lvalue, int rtemp);
char *getLLVMload(char *bitType, char *serialNum);
char *getLLVMcall(char *bitType, char *funcRef);
char *getLLVMglobalStr();
char *getLLVMglobalInt();
char *getLLVMstaticStr();
char *getLLVMstaticInt();
char *getLLVMmalloc();

char *getLLVMadd(char *bitType, char *lop, char *rop);
char *getLLVMsub(char *bitType, char *lop, char *rop);
char *getLLVMmul(char *bitType, char *lop, char *rop);
char *getLLVMdiv(char *bitType, char *lop, char *rop);
char *getLLVMstrcat(char *bitType, char *lop, char *rop);

bool addString(ptrSt StringRecord, char *str);
bool addSymbol(char *serial, int value, char *type, char *string, char *name);

int putEnd();

char *bitTypeJudge(char *Type)
{
    if (!strcmp(Type, "INT"))
        return "i32";
    else if (!strcmp(Type, "STR"))
        return "i8*";
    else if (!strcmp(Type, "VOID"))
        return "void";
    return NULL;
}

void tabSpace()
{
    if (!Tab)
        Tab = malloc(100);
    else
        Tab[0] = '\0';
    int i = 0;
    for (i = 0; i < tabNum; ++i)
        Tab[i] = '\t';
    Tab[i] = '\0';
}

int putEnd()
{
    printf("attributes #0 = { noinline nounwind optnone uwtable \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+fxsr,+mmx,+sse,+sse2,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\nattributes #1 = { nounwind \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+fxsr,+mmx,+sse,+sse2,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\nattributes #2 = { nounwind readonly \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+fxsr,+mmx,+sse,+sse2,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\nattributes #3 = { nounwind }\nattributes #4 = { nounwind readonly }\n");
    return 0;
}

int alignJudge(char *bitType)
{
    if (!strcmp(bitType, "i8*") || !strcmp(bitType, "double"))
        return 8;
    else if (!strcmp(bitType, "i32"))
        return 4;
}

char *getLLVMalloca(char *bitType)
{
    char *alloca = (char *)malloc(40);
    int align = alignJudge(bitType);
    sprintf(alloca, "%s%%%d = alloca %s, align %d\n", Tab, tempNum, bitType, align);
    return alloca;
}

char *getLLVMstore(char *bitType, char *lvalue, int rtemp)
{
    char *store = (char *)malloc(80);
    int align = alignJudge(bitType);
    sprintf(store, "%sstore %s %s, %s* %%%d, align %d\n", Tab, bitType, lvalue, bitType, rtemp, align);
    return store;
}

char *getLLVMload(char *bitType, char *serialNum)
{
    char *load = (char *)malloc(50);
    int align = alignJudge(bitType);
    sprintf(load, "%s%%%d = load %s, %s* %s, align %d\n", Tab, tempNum++, bitType, bitType, serialNum, align);
    return load;
}

char *getLLVMcall(char *bitType, char *funcRef)
{
    char *call = (char *)malloc(60);
    sprintf(call, "%s%%%d = call %s %s\n", Tab, tempNum, bitType, funcRef);
    free(funcRef);
    return call;
}

char *getLLVMadd(char *bitType, char *lop, char *rop)
{
    char *add = (char *)malloc(100);
    char lBuffer[20];
    char rBuffer[20];
    int flag1 = 0, flag2 = 0;
    if (!isNumber(lop))
    {
        que_push(FuncBody, getLLVMload(bitType, lop));
        sprintf(lBuffer, "%%%d", tempNum - 1);
        flag1 = 1;
    }
    else
        sprintf(lBuffer, lop);
    if (!isNumber(rop))
    {
        que_push(FuncBody, getLLVMload(bitType, rop));
        sprintf(rBuffer, "%%%d", tempNum - 1);
        flag2 = 1;
    }
    else
        sprintf(rBuffer, rop);
    if (!flag1 && !flag2)
    {
        double lvalue = atof(lBuffer);
        double rvalue = atof(rBuffer);
        double sum = lvalue + rvalue;
        char *sumBuffer = malloc(20);
        sprintf(sumBuffer, "%g", sum);
        free(add);
        return sumBuffer;
    }
    else
        sprintf(add, "%s%%%d = add nsw %s %s, %s\n", Tab, tempNum, bitType, lBuffer, rBuffer);
    return add;
}

char *getLLVMsub(char *bitType, char *lop, char *rop)
{
    char *sub = (char *)malloc(100);
    char lBuffer[20];
    char rBuffer[20];
    int flag1 = 0, flag2 = 0;
    if (!isNumber(lop))
    {
        que_push(FuncBody, getLLVMload(bitType, lop));
        sprintf(lBuffer, "%%%d", tempNum - 1);
        flag1 = 1;
    }
    else
        sprintf(lBuffer, lop);
    if (!isNumber(rop))
    {
        que_push(FuncBody, getLLVMload(bitType, rop));
        sprintf(rBuffer, "%%%d", tempNum - 1);
        flag2 = 1;
    }
    else
        sprintf(rBuffer, rop);
    if (!flag1 && !flag2)
    {
        double lvalue = atof(lBuffer);
        double rvalue = atof(rBuffer);
        double valueSub = lvalue - rvalue;
        char *subBuffer = malloc(20);
        sprintf(subBuffer, "%g", valueSub);
        free(sub);
        return subBuffer;
    }
    else
        sprintf(sub, "%s%%%d = sub nsw %s %s, %s\n", Tab, tempNum, bitType, lBuffer, rBuffer);
    return sub;
}

char *getLLVMmul(char *bitType, char *lop, char *rop)
{
    char *mul = (char *)malloc(100);
    char lBuffer[20];
    char rBuffer[20];
    int flag1 = 0, flag2 = 0;
    if (!isNumber(lop))
    {
        que_push(FuncBody, getLLVMload(bitType, lop));
        sprintf(lBuffer, "%%%d", tempNum - 1);
        flag1 = 1;
    }
    else
        sprintf(lBuffer, lop);
    if (!isNumber(rop))
    {
        que_push(FuncBody, getLLVMload(bitType, rop));
        sprintf(rBuffer, "%%%d", tempNum - 1);
        flag2 = 1;
    }
    else
        sprintf(rBuffer, rop);
    if (!flag1 && !flag2)
    {
        double lvalue = atof(lBuffer);
        double rvalue = atof(rBuffer);
        double valueMul = lvalue * rvalue;
        char *mulBuffer = malloc(20);
        sprintf(mulBuffer, "%g", valueMul);
        free(mul);
        return mulBuffer;
    }
    else
        sprintf(mul, "%s%%%d = mul nsw %s %s, %s\n", Tab, tempNum, bitType, lBuffer, rBuffer);
    return mul;
}

char *getLLVMdiv(char *bitType, char *lop, char *rop)
{
    char *div = (char *)malloc(100);
    char lBuffer[20];
    char rBuffer[20];
    int flag1 = 0, flag2 = 0;
    if (!isNumber(lop))
    {
        que_push(FuncBody, getLLVMload(bitType, lop));
        sprintf(lBuffer, "%%%d", tempNum - 1);
        flag1 = 1;
    }
    else
        sprintf(lBuffer, lop);
    if (!isNumber(rop))
    {
        que_push(FuncBody, getLLVMload(bitType, rop));
        sprintf(rBuffer, "%%%d", tempNum - 1);
        flag2 = 1;
    }
    else
        sprintf(rBuffer, rop);
    if (!flag1 && !flag2)
    {
        double lvalue = atof(lBuffer);
        double rvalue = atof(rBuffer);
        double valueDiv = lvalue / rvalue;
        char *divBuffer = malloc(20);
        sprintf(divBuffer, "%g", valueDiv);
        free(div);
        return divBuffer;
    }
    else
        sprintf(div, "%s%%%d = sdiv %s %s, %s\n", Tab, tempNum, bitType, lBuffer, rBuffer);
    return div;
}

char *getLLVMserm(char *bitType, char *lop, char *rop)
{
    char *serm = (char *)malloc(100);
    char lBuffer[20];
    char rBuffer[20];
    int flag1 = 0, flag2 = 0;
    if (!isNumber(lop))
    {
        que_push(FuncBody, getLLVMload(bitType, lop));
        sprintf(lBuffer, "%%%d", tempNum - 1);
        flag1 = 1;
    }
    else
        sprintf(lBuffer, lop);
    if (!isNumber(rop))
    {
        que_push(FuncBody, getLLVMload(bitType, rop));
        sprintf(rBuffer, "%%%d", tempNum - 1);
        flag2 = 1;
    }
    else
        sprintf(rBuffer, rop);
    if (!flag1 && !flag2)
    {
        double lvalue = atof(lBuffer);
        double rvalue = atof(rBuffer);
        int valueSerm = (int)lvalue % (int)rvalue;
        char *sermBuffer = malloc(20);
        sprintf(sermBuffer, "%g", valueSerm);
        free(serm);
        return sermBuffer;
    }
    else
        sprintf(serm, "%s%%%d = serm %s %s, %s\n", Tab, tempNum, bitType, lBuffer, rBuffer);
    return serm;
}

char *getLLVMstrcat(char *bitType, char *lop, char *rop)
{
    bitType = "i8*";
    char *funcRef = malloc(1000);
    if (string_check(funcRecord, "strcat"))
    {
        strcpy(funcRef, "\ndeclare dso_local i8* @strcat(i8*,i8*) #1\n");
        que_push(CallFunction, strdup(funcRef));
        addString(funcRecord, "strcat");
    }
    if (string_check(funcRecord, "strlen"))
    {
        strcpy(funcRef, "\ndeclare dso_local i64 @strlen(i8*) #2\n");
        que_push(CallFunction, strdup(funcRef));
        addString(funcRecord, "strlen");
    }
    if (string_check(funcRecord, "StrSum"))
    {
        strcpy(funcRef, "\ndefine dso_local i8* @StrSum(i8*, i8*) #0 {\r\n\t%3 = alloca i8*, align 8\n\t%4 = alloca i8*, align 8\n\t%5 = alloca i8*, align 8\n\tstore i8* %0, i8** %3, align 8\n\tstore i8* %1, i8** %4, align 8\n\t%6 = load i8*, i8** %3, align 8\n\t%7 = call i64 @strlen(i8* %6) #4\n\t%8 = load i8*, i8** %4, align 8\n\t%9 = call i64 @strlen(i8* %8) #4\n\t%10 = add i64 %7, %9\n\t%11 = call noalias i8* @malloc(i64 %10) #3\n\tstore i8* %11, i8** %5, align 8\n\t%12 = load i8*, i8** %5, align 8\n\t%13 = load i8*, i8** %3, align 8\n\t%14 = call i8* @strcat(i8* %12, i8* %13) #3\n\t%15 = load i8*, i8** %5, align 8\n\t%16 = load i8*, i8** %4, align 8\n\t%17 = call i8* @strcat(i8* %15, i8* %16) #3\n\t%18 = load i8*, i8** %5, align 8\n\tret i8* %18\n}\n\n");
        que_push(CallFunction, strdup(funcRef));
        addString(funcRecord, "StrSum");
    }
    sprintf(funcRef, "@StrSum(i8* %s, i8* %s)", lop, rop);
    return getLLVMcall(bitType, funcRef);
}

char *getLLVMStrAssign(char *bitType, char *lop, char *rop)
{
    bitType = "i8*";
    ptrSb Rsymbol = symbol_get(symbolTable, rop);
    ptrSb Lsymbol = symbol_get(symbolTable, lop);
    char *funcRef = malloc(4096);
    int InitFlag = 1;
    int tempFlag = 0;
    char *Lop;
    char buffer1[10] = "@";
    char buffer2[10] = "@";
    if (string_check(funcRecord, "free"))
    {
        strcpy(funcRef, "\ndeclare dso_local void @free(i8*) #1\n");
        que_push(CallFunction, strdup(funcRef));
        addString(funcRecord, "free");
    }
    if (string_check(funcRecord, "malloc"))
    {
        strcpy(funcRef, "\ndeclare dso_local i8* @malloc(i64) #1\n");
        que_push(CallFunction, strdup(funcRef));
        addString(funcRecord, "malloc");
    }
    if (string_check(funcRecord, "strlen"))
    {
        strcpy(funcRef, "\ndeclare dso_local i64 @strlen(i8*) #2\n");
        que_push(CallFunction, strdup(funcRef));
        addString(funcRecord, "strlen");
    }
    if (string_check(funcRecord, "strcpy"))
    {
        strcpy(funcRef, "\ndeclare dso_local i8* @strcpy(i8*, i8*) #1\n");
        que_push(CallFunction, strdup(funcRef));
        addString(funcRecord, "strcpy");
    }
    if (string_check(funcRecord, "StrAssign"))
    {
        strcpy(funcRef, "\ndefine dso_local i8* @StrAssign(i32, i32, i8*, i8*) #0 {\n\t%5 = alloca i8*, align 8\n\t%6 = alloca i32, align 4\n\t%7 = alloca i32, align 4\n\t%8 = alloca i8*, align 8\n\t%9 = alloca i8*, align 8\n\tstore i32 %0, i32* %6, align 4\n\tstore i32 %1, i32* %7, align 4\n\tstore i8* %2, i8** %8, align 8\n\tstore i8* %3, i8** %9, align 8\n\t%10 = load i32, i32* %7, align 4\n\t%11 = icmp ne i32 %10, 0\n\tbr i1 %11, label %12, label %19\n\t; <label>:12:                                     ; preds = %4\n\t%13 = load i32, i32* %6, align 4\n\t%14 = icmp ne i32 %13, 0\n\tbr i1 %14, label %15, label %17\n\n\t; <label>:15:                                     ; preds = %12\n\t%16 = load i8*, i8** %8, align 8\n\tcall void @free(i8* %16) #4\n\tbr label %17\n\n\t; <label>:17:                                     ; preds = %15, %12\n\t%18 = load i8*, i8** %9, align 8\n\tstore i8* %18, i8** %5, align 8\n\tbr label %40\n\n\t; <label>:19:                                     ; preds = %4\n\t%20 = load i32, i32* %6, align 4\n\t%21 = icmp ne i32 %20, 0\n\tbr i1 %21, label %26, label %22\n\n\t; <label>:22:                                     ; preds = %19\n\t%23 = load i8*, i8** %9, align 8\n\t%24 = call i64 @strlen(i8* %23) #5\n\t%25 = call noalias i8* @malloc(i64 %24) #4\n\tstore i8* %25, i8** %8, align 8\n\tbr label %35\n\n\t; <label>:26:                                     ; preds = %19\n\t%27 = load i32, i32* %6, align 4\n\t%28 = icmp ne i32 %27, 0\n\tbr i1 %28, label %29, label %34\n\n\t; <label>:29:                                     ; preds = %26\n\n\t%30 = load i8*, i8** %8, align 8\n\n\tcall void @free(i8* %30) #4\n\n\t%31 = load i8*, i8** %9, align 8\n\n\t%32 = call i64 @strlen(i8* %31) #5\n\n\t%33 = call noalias i8* @malloc(i64 %32) #4\n\n\tstore i8* %33, i8** %8, align 8\n\tbr label %34\n\n\t; <label>:34:                                     ; preds = %29, %26\n\tbr label %35\n\n\t; <label>:35:                                     ; preds = %34, %22\n\t%36 = load i8*, i8** %8, align 8\n\t%37 = load i8*, i8** %9, align 8\n\t%38 = call i8* @strcpy(i8* %36, i8* %37) #4\n\t%39 = load i8*, i8** %8, align 8\n\tstore i8* %39, i8** %5, align 8\n\tbr label %40\n\n\t; <label>:40:                                     ; preds = %35, %17\n\t%41 = load i8*, i8** %5, align 8\n\tret i8* %41\n}\n\n");
        que_push(CallFunction, strdup(funcRef));
        addString(funcRecord, "StrAssign");
    }
    if (!strcmp(Rsymbol->string, "IntermediateResult"))
        tempFlag = 1;
    if (!strcmp(Lsymbol->string, "UnInited"))
        InitFlag = 0;
    if (strcmp(Rsymbol->serial, "-1"))
        rop = Rsymbol->serial;
    if (strstr(rop,".str"))
    {
        strcat(buffer1,rop);
        rop = buffer1;
    }
    Lop = Lsymbol->serial;
    if (!strcmp(Lop,"-1"))
    {
        Lop = Lsymbol->name;
        strcat(buffer2,Lop);
        Lop = buffer2;
    }
    //printf("%s\n",Lop);
    sprintf(funcRef, "@StrAssign(i32 %d ,i32 %d,i8* %s, i8* %s)", InitFlag, tempFlag, Lop, rop);
    return getLLVMcall(bitType, funcRef);
}

char *getC_FileName()
{
    char *fileName = (char *)malloc(MAX_FILENAME);
    sprintf(fileName, __FILE__);
    return fileName;
}

char *getllvmFileName(char *filename)
{
    char *FN = strdup(filename);
    char *ChangeStart = FN + strlen(filename) - 1;
    ChangeStart[0] = 'l';
    ChangeStart[1] = 'l';
    ChangeStart[2] = '\0';
    return FN;
}

char *getFileName()
{
    char *filename = getC_FileName();
    filename = getllvmFileName(filename);
    return filename;
}

char *LLVMCalBuilder(char *leftOp, char *rightOp, char *(*LLVMBuilder)(char *, char *, char *))
{
    //printf("leftOp:%s\nrightOp:%s\n",leftOp,rightOp);
    ptrSb temp1 = NULL;
    ptrSb temp2 = malloc(sizeof(sb));
    ptrSb temp3 = NULL;
    int flag = 0;
    char *lop, *rop;
    char *temp;
    if (GlobalFlag == 1)
    {
        if (!isNumber(leftOp))
        {
            temp1 = (ptrSb)symbol_get(symbolTable, leftOp);
            if (leftOp[0] != '%')
                lop = temp1->serial;
            else
                lop = leftOp;
        }
        else
        {
            lop = leftOp;
            flag = 1;
        }
        if (!isNumber(rightOp))
        {
            temp3 = (ptrSb)symbol_get(symbolTable, rightOp);
            if (rightOp[0] != '%')
                rop = temp3->serial;
            else
                rop = rightOp;
        }
        else
        {
            rop = rightOp;
            flag = 1;
        }
        //printf("lop:%s\nrop:%s\n",lop,rop);
        if (flag == 1 || !strcmp(temp1->type, "INT"))
        {
            temp = LLVMBuilder("i32", lop, rop);
            if (!isNumber(temp))
                que_push(FuncBody, temp);
            else
            {
                free(temp2);
                return temp;
            }
            strcpy(temp2->type, "INT");
        }
        else if (!strcmp(temp1->type, "STR"))
        {
            que_push(FuncBody, LLVMBuilder("i8*", lop, rop));
            strcpy(temp2->type, "STR");
        }
        sprintf(temp2->name, "%%%d", tempNum++);
        strcpy(temp2->string, "IntermediateResult");
        symbol_push(symbolTable, temp2);
        return temp2->name;
    }
    else if (GlobalFlag == 0)
    {
    }
}

char *ReturnOSType(char *Buffer, char *LLVMcode)
{
    free(Buffer);
    return LLVMcode;
}

char *OsJudge(char *Buffer)
{
    if (strstr("Linux", Buffer))
        return ReturnOSType(Buffer, "\"x86_64-pc-linux-gnu\"\n\n");
    else if (strstr("Mac", Buffer))
        return ReturnOSType(Buffer, "\"x86_64-pc-mac-gnu\"\n\n");
    else if (strstr("Windows", Buffer))
        return ReturnOSType(Buffer, "\"x86_64-pc-windows-gnu\"\n\n");
}

char *sampleOsType()
{
    int fp = 0;
    char *Buffer = (char *)malloc(10);
    char *file = "/proc/sys/kernel/ostype";
    fp = open(file, O_RDONLY);
    if (fp == 0)
    {
        printf("error to open: %s\n", file);
        exit(EXIT_FAILURE);
    }
    read(fp, (void *)Buffer, 6);
    Buffer[strlen(Buffer) - 1] = 0;
    close(fp);
    return OsJudge(Buffer);
}

bool isNumber(char *number)
{
    if (number[0] == '0')
        return isNumber(number + 1);
    else
    {
        int index = 0;
        int flag = 0;
        while (number[index] != '\0')
        {
            if (isdigit(number[index++]))
                continue;
            else if (number[0] == '.')
            {
                if (flag > 1)
                    return false;
                else
                    flag++;
            }
            else
                return false;
        }
        return true;
    }
}

char *Init()
{
    if (!(symbolTable = hash_stack_new()))
        return NULL;
    if (!(stringRecord = hash_str_table_new()))
        return NULL;
    if (!(funcRecord = hash_str_table_new()))
        return NULL;
    tempNum = 1;
    tabNum = 0;
    GlobalFlag = 0;
    ConstStringNum = 0;
    if (NULL == symbolTable)
    {
        printf("Create symbolTable failed\n");
        return NULL;
    }
    init_queue(&CallFunction, MAX_NUM);
    init_queue(&FuncHead, MAX_NUM);
    init_queue(&FuncBody, MAX_NUM);
    init_queue(&GlobalContext, MAX_NUM);
    //char *Cname = getC_FileName();
    char *FileName = getllvmFileName(CompilerFile);
    FILE *fp = fopen(FileName, "w+");
    fprintf(fp, "; ModuleID = `%s`\n", CompilerFile);
    fprintf(fp, "source_filename = \"%s\"\n", CompilerFile);
    fprintf(fp, "target datalayout = \"e-m:e-i64:64-f80:128-n8:16:32:64-S128\"\n");
    fprintf(fp, "target triple = %s", sampleOsType());
    fclose(fp);
    //free(Cname);
    return FileName;
}

void funcPut()
{
    while (!is_que_empty(*FuncHead) && !is_que_empty(*FuncBody))
    {
        printf("%s", que_pop(FuncHead));
        funcbody_put(FuncBody);
    }
    return;
}

bool addSymbol(char *serial, int value, char *type, char *string, char *name)
{
    ptrSb symbol = malloc(sizeof(sb));
    if (!symbol)
        return false;
    symbol->value = value;
    strcpy(symbol->name, name);
    strcpy(symbol->serial, serial);
    strcpy(symbol->type, type);
    strcpy(symbol->string, string);
    symbol_push(symbolTable, symbol);
    return true;
}

bool addString(ptrSt StringRecord, char *str)
{
    ptrSr String = malloc(sizeof(sr));
    if (!String)
        return false;
    String->next = NULL;
    strcpy(String->string, str);
    string_push(StringRecord, String);
    return true;
}

int genCode(ptrast root)
{
    if (!root)
        return -1;
    if (!strcmp(root->nodetype, "FunctionDef"))
        genFuncDef(root);
    else if (!strcmp(root->nodetype, "VariableDec"))
        genVarDec(root);
    genCode(root->next);
    return 0;
}

int genFuncDef(ptrast root)
{
    if (!root)
        return -1;
    if (hash_stack_subScope(symbolTable))
        return -1;
    GlobalFlag = 1;
    tempNum = 0;
    int paraOrder = 0;
    char Buffer[1024];
    char copyParameter[100];
    char *dataType = NULL;
    char *ReturnType = strdup(root->content);
    char *FuncName = strdup(root->left->content);
    char funcHead[4096];
    Buffer[0] = '(';
    Buffer[1] = '\0';
    ptrast statement = root->right;
    ptrast parameter = root->left;
    ptrast parameterHead = parameter;
    char serial[10];
    while ((parameter = parameter->next) != NULL)
        ++tempNum;
    ++tempNum;
    if (!strcmp(FuncName, "main"))
    {
        sprintf(copyParameter, "%s%%%d = alloca i32, align 4\n", Tab, tempNum++);
        que_push(FuncBody, strdup(copyParameter));
        sprintf(copyParameter, "%sstore i32 0, i32* %%%d, align 4\n", Tab, tempNum - 1);
        que_push(FuncBody, strdup(copyParameter));
    }
    while ((parameterHead = parameterHead->next) != NULL)
    {
        sprintf(serial, "%%%d", tempNum++);
        addSymbol(serial, 0, parameterHead->nodetype, "\0", parameterHead->content);
        dataType = bitTypeJudge(parameterHead->nodetype);
        int align = alignJudge(dataType);
        if (!strcmp(dataType, "void"))
            continue;
        else
        {
            sprintf(copyParameter, "%s%s = alloca %s, align %d\n", Tab, serial, dataType, align);
            que_push(FuncBody, strdup(copyParameter));
            sprintf(copyParameter, "%sstore %s %%%d, %s* %s, align %d\n", Tab, dataType, paraOrder++, dataType, serial, align);
            que_push(FuncBody, strdup(copyParameter));
        }
        strcat(Buffer, dataType);
        strcat(Buffer, ",");
    }
    int bufferLen = strlen(Buffer);
    if (bufferLen > 1)
        Buffer[bufferLen - 1] = ')';
    else
    {
        Buffer[bufferLen] = ')';
        Buffer[bufferLen + 1] = '\0';
    }
    sprintf(funcHead, "define dso_local %s @%s%s #0 {\t\n", bitTypeJudge(ReturnType), FuncName, Buffer);
    que_push(FuncHead, strdup(funcHead));
    genStatement(statement);
    hash_stack_pop(symbolTable);
    que_push(FuncBody, "}\n\n");
    free(ReturnType);
    ReturnType = NULL;
    return 0;
}

int genStatement(ptrast root)
{
    if (!root)
        return -1;
    while (root)
    {
        if (!strcmp(root->nodetype, "IF_Stmt"))
        {
        }
        else if (!strcmp(root->nodetype, "WhileStmt"))
        {
        }
        else if (!strcmp(root->nodetype, "ReturnStmt"))
        {
            char *returnValue = genExpr(root->left);
            char Buffer[100];
            if (returnValue == NULL)
            {
                sprintf(Buffer, "%sret void\n", Tab);
                que_push(FuncBody, strdup(Buffer));
            }
            else
            {
                char *returnType;
                if (isNumber(returnValue))
                    returnType = "i32";
                else
                {
                    ptrSb symbol = symbol_get(symbolTable, returnValue);
                    returnType = symbol->type;
                    returnType = bitTypeJudge(returnType);
                    if (strcmp(symbol->serial, "-1"))
                        returnValue = symbol->serial;
                    else
                        returnValue = symbol->name;
                }
                sprintf(Buffer, "%sret %s %s\n", Tab, returnType, returnValue);
                que_push(FuncBody, strdup(Buffer));
            }
        }
        else if (!strcmp(root->nodetype, "PrintStmt"))
        {
        }
        else if (!strcmp(root->nodetype, "ScanStmt"))
        {
        }
        else if (!strcmp(root->nodetype, "VariableDec"))
            genVarDec(root);
        else
            genExpr(root);
        root = root->next;
    }
    return 0;
}

int genVarDec(ptrast root)
{
    if (!root)
        return -1;
    char Buffer[1024];
    char *VarType = root->content;
    char *VarName = NULL;
    ptrSb symbol;
    if (!(symbol = malloc(sizeof(sb))))
        return false;
    root = root->left;
    if (GlobalFlag == 0)
    {
        while (root)
        {
            if (NULL == root->left && NULL == root->right)
            {
                char *bitCode = bitTypeJudge(VarType);
                int align = alignJudge(bitCode);
                VarName = root->content;
                if (!addSymbol("-1", 0, VarType, "UnInited", VarName))
                    return false;
                if (strcmp(VarType, "STR") != 0)
                    sprintf(Buffer, "@%s = common dso_local global %s 0, align %d\n", VarName, bitCode, align);
                else
                    sprintf(Buffer, "@%s = common dso_local global %s null, align %d\n", VarName, bitCode, align);
                que_push(GlobalContext, strdup(Buffer));
            }
            else if (!strcmp("VariableInit", root->nodetype))
            {
                VarName = root->left->content;
                char *rightValue = genExpr(root->right);
                // printf("%s\n",rightValue);
                if (!strcmp(VarType, "STR"))
                {
                    symbol = (ptrSb)symbol_get(symbolTable, rightValue);
                    int length = strlen(symbol->string) + 1;
                    sprintf(Buffer, "@%s = dso_local global i8* getelementptr inbounds ([%d x i8], [%d x i8]* @%s, i32 0, i32 0), align 8\n", VarName, length, length, rightValue);
                    if (strlen(rightValue) > 4)
                        free(rightValue);
                    if (!addSymbol("-1", 0, VarType, symbol->string, VarName))
                        return false;
                }
                else if (!strcmp(VarType, "INT"))
                {
                    sprintf(Buffer, "@%s = dso_local global i32 %s, align 4\n", VarName, rightValue);
                    if (!addSymbol("-1", atof(rightValue), VarType, "\0", VarName))
                        return false;
                }
                que_push(GlobalContext, strdup(Buffer));
            }
            else if (!strcmp("Listinit", root->nodetype))
            {
            }
            root = root->next;
        }
    }
    else if (GlobalFlag == 1)
    {
        char *serial = malloc(sizeof(30));
        while (root)
        {
            if (NULL == root->left && NULL == root->right)
            {
                char *bitCode = bitTypeJudge(VarType);
                int align = alignJudge(bitCode);
                VarName = root->content;
                sprintf(serial, "%%%d", tempNum++);
                if (!addSymbol(strdup(serial), 0, VarType, "\0", VarName))
                    return false;
                sprintf(Buffer, "%s%s = alloca %s, align %d\n", Tab, serial, bitCode, align);
                que_push(FuncBody, strdup(Buffer));
            }
            else if (!strcmp("VariableInit", root->nodetype))
            {
                VarName = root->left->content;
                char *rightValue = genExpr(root->right);
                if (!strcmp(VarType, "STR"))
                {
                    symbol = (ptrSb)symbol_get(symbolTable, rightValue);
                    int length = strlen(symbol->string);
                    sprintf(serial, "%%%d", tempNum++);
                    sprintf(Buffer, "%s%s = alloca i8*, align 8\n", Tab, serial);
                    que_push(FuncBody, strdup(Buffer));
                    if (rightValue[0] == '.')
                    {
                        if (string_check(funcRecord, "malloc"))
                        {
                            sprintf(Buffer, "\ndeclare dso_local noalias i8* @malloc(i64) #1\n");
                            que_push(CallFunction, strdup(Buffer));
                            addString(funcRecord, "malloc");
                        }
                        if (string_check(funcRecord, "strcpy"))
                        {
                            sprintf(Buffer, "\ndeclare dso_local i8* @strcpy(i8*, i8*) #1\n");
                            que_push(CallFunction, strdup(Buffer));
                            addString(funcRecord, "strcpy");
                        }
                        sprintf(Buffer, "%s%%%d = call noalias i8* @malloc(i64 %d) #3\n", Tab, tempNum++, length + 1);
                        que_push(FuncBody, strdup(Buffer));
                        sprintf(Buffer, "%sstore i8* %%%d, i8** %s, align 8\n", Tab, tempNum - 1, serial);
                        que_push(FuncBody, strdup(Buffer));
                        sprintf(Buffer, "%s%%%d = load i8*, i8** %s, align 8\n", Tab, tempNum++, serial);
                        que_push(FuncBody, strdup(Buffer));
                        sprintf(Buffer, "%s%%%d = call i8* @strcpy(i8* %%%d, i8* getelementptr inbounds ([%d x i8], [%d x i8]* @%s, i32 0, i32 0)) #3\n", Tab, tempNum, tempNum - 1, length + 1, length + 1, rightValue);
                        tempNum++;
                    }
                    else
                    {
                        char *Tmp;
                        if (symbol->name[0] == '%')
                            Tmp = symbol->name;
                        else
                            Tmp = symbol->serial;
                        if (!strcmp(symbol->string, "IntermediateResult"))
                            sprintf(Buffer, "%sstore i8* %%%d, i8** %s, align 8\n", Tab, tempNum - 2, serial);
                        else
                        {
                            sprintf(Buffer, "%s%%%d = load i8*, i8** %s, align 8\n", Tab, tempNum++, Tmp);
                            que_push(FuncBody, strdup(Buffer));
                            sprintf(Buffer, "%sstore i8* %%%d, i8** %s, align 8\n", Tab, tempNum - 1, serial);
                        }
                    }
                    if (!addSymbol(serial, 0, VarType, symbol->string, VarName))
                        return false;
                    if (strlen(rightValue) > 4)
                    {
                        //printf("%s\n",rightValue);                 
                        free(rightValue);
                        //system("pause");
                    }
                }
                else if (!strcmp(VarType, "INT"))
                {
                    sprintf(serial, "%%%d", tempNum++);
                    sprintf(Buffer, "%s%s = alloca i32, align 4\n", Tab, serial);
                    que_push(FuncBody, strdup(Buffer));
                    // printf("%s\n",rightValue);
                    if (isNumber(rightValue))
                    {
                        sprintf(Buffer, "%sstore i32 %s, i32* %s, align 4\n", Tab, rightValue, serial);
                        if (!addSymbol(serial, atof(rightValue), VarType, "\0", VarName))
                            return false;
                    }
                    else if (rightValue[0] == '%')
                    {
                        sprintf(Buffer, "%sstore i32 %s, i32* %s, align 4\n", Tab, rightValue, serial);
                        if (!addSymbol(serial, 0, VarType, "\0", VarName))
                            return false;
                    }
                    else
                    {
                        symbol = (ptrSb)symbol_get(symbolTable, rightValue);
                        sprintf(Buffer, "%sstore i32 %s, i32* %s, align 4\n", Tab, symbol->serial, serial);
                        if (!addSymbol(serial, symbol->value, VarType, "\0", VarName))
                            return false;
                    }
                }
                //printf("Buffer:%s\n",Buffer);
                que_push(FuncBody, strdup(Buffer));
            }
            else if (!strcmp("Listinit", root->nodetype))
            {
            }
            root = root->next;
        }
    }
    return 0;
}

char *genExpr(ptrast root)
{
    if (!root)
        return NULL;
    char *leftOp, *rightOp;
    ptrSb symbol;
    //ptrSb symbol2;
    if (!strcmp(root->nodetype, "+"))
    {
        leftOp = genExpr(root->left);
        rightOp = genExpr(root->right);
        symbol = (ptrSb)symbol_get(symbolTable, leftOp);
        if (isNumber(rightOp) || isNumber(leftOp) || strcmp(symbol->type, "STR") != 0)
            return LLVMCalBuilder(leftOp, rightOp, getLLVMadd);
        else
            return LLVMCalBuilder(leftOp, rightOp, getLLVMstrcat);
    }
    else if (!strcmp(root->nodetype, "*"))
    {
        leftOp = genExpr(root->left);
        rightOp = genExpr(root->right);
        return LLVMCalBuilder(leftOp, rightOp, getLLVMmul);
    }
    else if (!strcmp(root->nodetype, "/"))
    {
        leftOp = genExpr(root->left);
        rightOp = genExpr(root->right);
        return LLVMCalBuilder(leftOp, rightOp, getLLVMdiv);
    }
    else if (!strcmp(root->nodetype, "-") && root->right != NULL)
    {
        leftOp = genExpr(root->left);
        rightOp = genExpr(root->right);
        return LLVMCalBuilder(leftOp, rightOp, getLLVMsub);
    }
    else if (!strcmp(root->nodetype, "%"))
    {
        leftOp = genExpr(root->left);
        rightOp = genExpr(root->right);
        return LLVMCalBuilder(leftOp, rightOp, getLLVMserm);
    }
    else if (!strcmp(root->nodetype, "Number"))
    {
        double value = root->value;
        char *number = malloc(20);
        sprintf(number, "%g", value);
        //printf("%sOKOKOKOK\n",number);
        return number;
    }
    else if (!strcmp(root->nodetype, "String"))
    {
        char *buffer = malloc(4096);
        char *temp;
        temp = strdup(root->content);
        temp[strlen(temp) - 1] = '\0';
        ++temp;
        //printf("%s\n",temp);
        if (string_check(stringRecord, temp))
        {
            if (ConstStringNum == 0)
            {
                sprintf(buffer, "@.str = private unnamed_addr constant [%d x i8] c\"%s\\00\", align 1\n", (int)strlen(temp) + 1, temp);
                ConstStringNum++;
                que_push(GlobalContext, buffer);
                addSymbol("-1", 0, "STR", temp, ".str");
                addString(stringRecord, temp);
                free(--temp);
                return ".str";
            }
            else
            {
                char *strName = malloc(30);
                sprintf(strName, ".str.%d", ConstStringNum++);
                sprintf(buffer, "@%s = private unnamed_addr constant [%d x i8] c\"%s\\00\", align 1\n", strName, (int)strlen(temp) + 1, temp);
                que_push(GlobalContext, buffer);
                addSymbol("-1", 0, "STR", temp, strName);
                addString(stringRecord, temp);
                free(--temp);
                return strName;
            }
        }
        else
        {
            for (int i = 0; i < ConstStringNum; ++i)
            {
                if (i == 0)
                {
                    symbol = (ptrSb)symbol_get(symbolTable, ".str");
                    if (!strcmp(symbol->string, temp))
                    {
                        free(--temp);
                        return ".str";
                    }
                }
                else
                {
                    char buffer[30];
                    sprintf(buffer, ".str.%d", i);
                    symbol = (ptrSb)symbol_get(symbolTable, buffer);
                    if (!strcmp(symbol->string, temp))
                    {
                        free(--temp);
                        return strdup(symbol->name);
                    }
                }
            }
        }
        if (temp)
            free(--temp);
    }
    else if (!strcmp(root->nodetype, ":="))
    {
        char *dataType;
        int align;
        ptrSb temSymbol;
        char *buffer = malloc(4096);
        leftOp = root->content;
        rightOp = genExpr(root->left);
        temSymbol = symbol_get(symbolTable, rightOp);
        if (rightOp[0] != '%' && !isNumber(rightOp))
        {
            if (strcmp(temSymbol->serial, "-1"))
                rightOp = temSymbol->serial;
            else if (!strcmp(temSymbol->type, "STR"))
            {
                char subBuffer[1024];
                char *record = rightOp;
                rightOp = subBuffer;
                if (strlen(record) > 4)
                    free(record);
                int length = strlen(temSymbol->string) + 1;
                sprintf(subBuffer, "getelementptr inbounds ([%d x i8], [%d x i8]* @%s, i32 0, i32 0)", length, length, temSymbol->name);
            }
        }
        if (!isNumber(rightOp) && strcmp(temSymbol->string, "IntermediateResult"))
        {
            sprintf(buffer, "%s%%%d = load %s, %s* %s, align %d\n", Tab, tempNum, dataType, dataType, rightOp, align);
            que_push(FuncBody, strdup(buffer));
            char temBuffer[8];
            sprintf(temBuffer, "%%%d", tempNum++);
            rightOp = temBuffer;
        }
        symbol = symbol_get(symbolTable, leftOp);
        dataType = bitTypeJudge(symbol->type);
        align = alignJudge(dataType);
        sprintf(buffer, "%sstore %s %s, %s* %s, align %d\n", Tab, dataType, rightOp, dataType, symbol->serial, align);
        que_push(FuncBody, buffer);
        return symbol->serial;
    }
    else if (!strcmp(root->nodetype, "="))
    {
        char *dataType;
        int align;
        ptrSb temSymbol;
        char *buffer = malloc(4096);
        leftOp = root->content;
        //printf("%s\n",leftOp);
        symbol = symbol_get(symbolTable, leftOp);
        dataType = bitTypeJudge(symbol->type);
        align = alignJudge(dataType);
        if (root->right == NULL)
        {
            rightOp = genExpr(root->left);
            temSymbol = symbol_get(symbolTable, rightOp);
            if (!strcmp(symbol->type, "INT"))
            {
                if (!isNumber(rightOp) && strcmp(temSymbol->string, "IntermediateResult"))
                {
                    sprintf(buffer, "%s%%%d = load %s, %s* %s, align %d\n", Tab, tempNum, dataType, dataType, rightOp, align);
                    que_push(FuncBody, strdup(buffer));
                    char temBuffer[8];
                    sprintf(temBuffer, "%%%d", tempNum++);
                    rightOp = temBuffer;
                }
                sprintf(buffer, "%sstore %s %s, %s* %s, align %d\n", Tab, dataType, rightOp, dataType, symbol->serial, align);
            }
            else if (!strcmp(symbol->type, "STR"))
            {
                char BUFFER[10]="@";
                char *TEMP = symbol->serial;
                que_push(FuncBody, getLLVMStrAssign(dataType, leftOp, rightOp));
                if(!strcmp(symbol->serial,"-1"))
                {
                    strcat(BUFFER,symbol->name);
                    TEMP = BUFFER;
                }
                sprintf(buffer, "%sstore %s %%%d, %s* %s, align %d\n", Tab, dataType, tempNum++, dataType, TEMP, align);
            }
            que_push(FuncBody, buffer);
            return symbol->serial;
        }
        else if (root->right != NULL)
        {
            char *temVar = genExpr(root->right);
            rightOp = genExpr(root->left);
            temSymbol = symbol_get(symbolTable, rightOp);
            if (!strcmp(symbol->type, "STR"))
            {
                if (strcmp(symbol->serial, "-1"))
                {
                    sprintf(buffer, "%s%%%d = load i8*, i8** %s, align 8\n", Tab, tempNum++, symbol->serial);
                    que_push(FuncBody, strdup(buffer));
                    sprintf(buffer, "%s%%%d = getelementptr inbounds i8, i8* %%%d, i64 %s\n", Tab, tempNum++, tempNum - 2, rightOp);
                    que_push(FuncBody, strdup(buffer));
                    sprintf(buffer, "%sstore i8 %s, i8* %%%d, align 1\n", Tab, temVar, tempNum - 1);
                    que_push(FuncBody, buffer);
                    return temVar;
                }
                else if (strstr(symbol->name, "."))
                {
                }
            }
            else if (!strcmp(symbol->type, "INT"))
            {
            }
        }
    }
    else if (!strcmp(root->nodetype, "/="))
    {
        char *dataType;
        int align;
        char *buffer = malloc(4096);
        leftOp = root->content;
        symbol = symbol_get(symbolTable, leftOp);
        dataType = bitTypeJudge(symbol->type);
        align = alignJudge(dataType);
        rightOp = genExpr(root->left);
        que_push(FuncBody, getLLVMdiv(dataType, symbol->serial, rightOp));
        sprintf(buffer, "%sstore %s %%%d, %s* %s, align %d\n", Tab, dataType, tempNum++, dataType, symbol->serial, align);
        que_push(FuncBody, buffer);
        return symbol->serial;
    }
    else if (!strcmp(root->nodetype, "*="))
    {
        char *dataType;
        int align;
        char *buffer = malloc(4096);
        leftOp = root->content;
        symbol = symbol_get(symbolTable, leftOp);
        dataType = bitTypeJudge(symbol->type);
        align = alignJudge(dataType);
        rightOp = genExpr(root->left);
        que_push(FuncBody, getLLVMmul(dataType, symbol->serial, rightOp));
        sprintf(buffer, "%sstore %s %%%d, %s* %s, align %d\n", Tab, dataType, tempNum++, dataType, symbol->serial, align);
        que_push(FuncBody, buffer);
        return symbol->serial;
    }
    else if (!strcmp(root->nodetype, "+="))
    {
        char *dataType;
        int align;
        char *buffer = malloc(4096);
        leftOp = root->content;
        symbol = symbol_get(symbolTable, leftOp);
        dataType = bitTypeJudge(symbol->type);
        align = alignJudge(dataType);
        rightOp = genExpr(root->left);
        que_push(FuncBody, getLLVMadd(dataType, symbol->serial, rightOp));
        sprintf(buffer, "%sstore %s %%%d, %s* %s, align %d\n", Tab, dataType, tempNum++, dataType, symbol->serial, align);
        que_push(FuncBody, buffer);
        return symbol->serial;
    }
    else if (!strcmp(root->nodetype, "-="))
    {
        char *dataType;
        int align;
        char *buffer = malloc(4096);
        leftOp = root->content;
        symbol = symbol_get(symbolTable, leftOp);
        dataType = bitTypeJudge(symbol->type);
        align = alignJudge(dataType);
        rightOp = genExpr(root->left);
        que_push(FuncBody, getLLVMsub(dataType, symbol->serial, rightOp));
        sprintf(buffer, "%sstore %s %%%d, %s* %s, align %d\n", Tab, dataType, tempNum++, dataType, symbol->serial, align);
        que_push(FuncBody, buffer);
        return symbol->serial;
    }
    else if (!strcmp(root->nodetype, "%="))
    {
        char *dataType;
        int align;
        char *buffer = malloc(4096);
        leftOp = root->content;
        symbol = symbol_get(symbolTable, leftOp);
        dataType = bitTypeJudge(symbol->type);
        align = alignJudge(dataType);
        rightOp = genExpr(root->left);
        que_push(FuncBody, getLLVMserm(dataType, symbol->serial, rightOp));
        sprintf(buffer, "%sstore %s %%%d, %s* %s, align %d\n", Tab, dataType, tempNum++, dataType, symbol->serial, align);
        que_push(FuncBody, buffer);
        return symbol->serial;
    }
    else if (!strcmp(root->nodetype, "VariableRef"))
        return root->content;
    else if (!strcmp(root->content, "ListRef"))
    {
        char *buffer = malloc(4096);
        char *listName = root->content;
        char *index = genExpr(root->left);
        symbol = symbol_get(symbolTable, listName);
        if (!strcmp(symbol->type, "STR"))
        {
            sprintf(buffer, "%%%d = load i8*, i8** %s, align 8", tempNum, symbol->serial);
            que_push(FuncBody, strdup(buffer));
            sprintf(buffer, "%%%d = getelementptr inbounds i8, i8* %%%d, i64 %s", ++tempNum, tempNum - 1, index);
            que_push(FuncBody, strdup(buffer));
            sprintf(buffer, "%%%d = load i8, i8* %%%d, align 1", ++tempNum, tempNum - 1);
            que_push(FuncBody, buffer);
            tempNum++;
            ptrSb temSym = malloc(sizeof(sb));
            sprintf(temSym->serial, "%%%d", tempNum - 1);
            sprintf(temSym->name, "%%%d", tempNum - 1);
            sprintf(temSym->string, "IntermediateResult");
            sprintf(temSym->type, "STR");
            temSym->value = 0;
            symbol_push(symbolTable, temSym);
            return temSym->serial;
        }
    }
}

void outputLLVM()
{
    char *fileName = Init();
    freopen(fileName, "a+", stdout);
    produceAst();
    //showAst(astRoot,0);
    genCode(astRoot);
    outputQue(*GlobalContext);
    outputQue(*CallFunction);
    funcPut();
    putEnd();
    Destroy_que(&GlobalContext);
    Destroy_que(&FuncHead);
    Destroy_que(&FuncBody);
    free(fileName);
    return;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        CompilerFile = argv[i];
        outputLLVM();
        freeAst(astRoot);
    }
    return 0;
}

// //*** LLVM-C Sample ***/
// // int main(int argc, char const *argv[]) {
// //     LLVMModuleRef mod = LLVMModuleCreateWithName("my_module");
// //     LLVMTypeRef param_types[] = { LLVMInt32Type(), LLVMInt32Type() };
// //     LLVMTypeRef ret_type = LLVMFunctionType(LLVMInt32Type(), param_types, 2, 0);
// //     LLVMValueRef sum = LLVMAddFunction(mod, "sum", ret_type);

// //     LLVMBasicBlockRef entry = LLVMAppendBasicBlock(sum, "entry");

// //     LLVMBuilderRef builder = LLVMCreateBuilder();
// //     LLVMPositionBuilderAtEnd(builder, entry);
// //     LLVMValueRef tmp = LLVMBuildAdd(builder, LLVMGetParam(sum, 0), LLVMGetParam(sum, 1), "tmp");
// //     LLVMBuildRet(builder, tmp);

// //     char *error = NULL;
// //     LLVMVerifyModule(mod, LLVMAbortProcessAction, &error);
// //     LLVMDisposeMessage(error);

// //     LLVMExecutionEngineRef engine;
// //     error = NULL;

// // 	/**must needed target**/
// //     LLVMInitializeNativeTarget();
// //     LLVMInitializeNativeAsmPrinter();
// // 	/**********************/

// //     LLVMLinkInMCJIT();
// //     if (LLVMCreateExecutionEngineForModule(&engine, mod, &error) != 0) {
// //         fprintf(stderr, "failed to create execution engine\n");
// //         abort();
// //     }
// //     if (error) {
// //         fprintf(stderr, "error: %s\n", error);
// //         LLVMDisposeMessage(error);
// //         exit(EXIT_FAILURE);
// //     }

// //     if (argc < 3) {
// //         fprintf(stderr, "usage: %s x y\n", argv[0]);
// //         exit(EXIT_FAILURE);
// //     }
// //     long long x = strtoll(argv[1], NULL, 10);
// //     long long y = strtoll(argv[2], NULL, 10);
// // 	printf("%lld,%lld\n",x,y);

// // 	// these codes didn't work
// //     // LLVMGenericValueRef args[] = {
// //     //     LLVMCreateGenericValueOfInt(LLVMInt32Type(), x, 0),
// //     //     LLVMCreateGenericValueOfInt(LLVMInt32Type(), y, 0)
// //     // };
// //     // LLVMGenericValueRef res = LLVMRunFunction(engine, sum, 2, args);
// //     // printf("%d\n", (int)LLVMGenericValueToInt(res, 0));

// //     // Write out bitcode to file
// // 	int (*sum_func)(int, int) = (int (*)(int, int))LLVMGetFunctionAddress(engine, "sum");
// // 	//system("read -p 'Press Enter to continue...' var");
// // 	//sum_func(x, y);
// // 	printf("%d\n", sum_func(x, y));
// //     if (LLVMWriteBitcodeToFile(mod, "sum.bc") != 0) {
// //         fprintf(stderr, "error writing bitcode to file, skipping\n");
// //     }
// //     LLVMDisposeBuilder(builder);
// //     LLVMDisposeExecutionEngine(engine);
// // 	return 0;
// // }
