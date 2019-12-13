//#include "ast.h"
#include "queue.h"
#include "main.h"
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
pqe GlobalContext;     //global context
pqe FuncHead;          //function head
pqe FuncBody;          //funciton body
int GlobalFlag;        //to judge whether the text is included in the global context
int ConstStringNum;    //to record the num of the constant string
int tempNum = 0;       //to record the num of the temperary variable in a function
ptrhs symbolTable;     //symbol table
char *Tab = NULL;

void tabSpace();
char *getC_FileName();
char *getllvmFileName(char *filename);
char *getFileName();
char *sampleOsType();
char *ReturnOSType(char *Buffer, char *LLVMcode);
char *Init();

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
    if(!Tab)
        Tab = malloc(100);
    else
        Tab[0] = '\0';
    int i = 0;
    for(i = 0;i<tabNum;++i)
        Tab[i] = '\t';
    Tab[i] = '\0';
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
    sprintf(alloca, "%s%%%d = alloca %s, align %d\n",Tab, tempNum, bitType, align);
    return alloca;
}

char *getLLVMstore(char *bitType, char *lvalue, int rtemp)
{
    char *store = (char *)malloc(80);
    int align = alignJudge(bitType);
    sprintf(store, "%sstore %s %s, %s* %%%d, align %d\n",Tab, bitType, lvalue, bitType, rtemp, align);
    return store;
}

char *getLLVMload(char *bitType, char *serialNum)
{
    char *load = (char *)malloc(50);
    int align = alignJudge(bitType);
    sprintf(load, "%s%%%d = load %s, %s* %s, align %d\n",Tab,tempNum++, bitType, bitType, serialNum,align);
    return load;
}

char *getLLVMcall(char *bitType, char *funcRef)
{
    char *call = (char *)malloc(60);
    int align = alignJudge(bitType);
    sprintf(call, "%s%%%d = call %s %s\n",Tab,tempNum, bitType, funcRef);
    free(funcRef);
    return call;
}

char *getLLVMadd(char *bitType, char *lop, char *rop)
{
    char *add = (char *)malloc(100);
    int align = alignJudge(bitType);
    que_push(FuncBody,getLLVMload(bitType,lop));
    que_push(FuncBody,getLLVMload(bitType,rop));
    sprintf(add, "%s%%%d = add nsw %s %s, %s\n", Tab,tempNum, bitType, lop, rop);
    return add;
}

char *getLLVMsub(char *bitType, char *lop, char *rop)
{
    char *add = (char *)malloc(100);
    int align = alignJudge(bitType);
    que_push(FuncBody,getLLVMload(bitType,lop));
    que_push(FuncBody,getLLVMload(bitType,rop));
    sprintf(add, "%s%%%d = sub nsw %s %s, %s\n",Tab,tempNum, bitType, lop, rop);
    return add;
}

char *getLLVMmul(char *bitType, char *lop, char *rop)
{
    char *mul = (char *)malloc(100);
    int align = alignJudge(bitType);
    que_push(FuncBody,getLLVMload(bitType,lop));
    que_push(FuncBody,getLLVMload(bitType,rop));
    sprintf(mul, "%s%%%d = mul nsw %s %s, %s\n",Tab, tempNum, bitType, lop, rop);
    return mul;
}

char *getLLVMdiv(char *bitType, char *lop, char *rop)
{
    char *div = (char *)malloc(100);
    int align = alignJudge(bitType);
    que_push(FuncBody,getLLVMload(bitType,lop));
    que_push(FuncBody,getLLVMload(bitType,rop));
    sprintf(div, "%s%%%d = div nsw %s %s, %s\n",Tab, tempNum, bitType, lop, rop);
    return div;
}

char *getLLVMserm(char *bitType, char *lop, char *rop)
{
    char *serm = (char *)malloc(100);
    int align = alignJudge(bitType);
    que_push(FuncBody,getLLVMload(bitType,lop));
    que_push(FuncBody,getLLVMload(bitType,rop));
    sprintf(serm, "%s%%%d = srem %s %s, %s\n",Tab, tempNum, bitType, lop, rop);
    return serm;
}

char *getLLVMstrcat(char *bitType, char *lop, char *rop)
{
    bitType = "i8*";
    char *funcRef = malloc(100);
    sprintf(funcRef, "@strcat(i8* %s, i8* %s)", lop, rop);
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
    ptrSb temp1;
    ptrSb temp2 = malloc(sizeof(sb));
    ptrSb temp3;
    if (GlobalFlag == 1)
    {
        temp1 = (ptrSb)symbol_get(symbolTable, leftOp);
        temp3 = (ptrSb)symbol_get(symbolTable, rightOp);
        if(leftOp[0]!='%')
            leftOp = temp1->serial;
        if(rightOp[0]!='%')
            rightOp = temp3->serial;
        if (!strcmp(temp1->type, "INT"))
        {
            if(leftOp[0]=='%')
                que_push(FuncBody, LLVMBuilder("i32", leftOp, rightOp));
            else 
                que_push(FuncBody, LLVMBuilder("i32", temp1->serial, temp2->serial));
            strcpy(temp2->type, "INT");
        }
        else if (!strcmp(temp1->type, "STR"))
        {
            que_push(FuncBody, LLVMBuilder("i8*", leftOp, rightOp));
            strcpy(temp2->type, "STR");
        }
        sprintf(temp2->name, "%%%d", tempNum++);
        symbol_push(symbolTable, temp2);
       // printf("%s\n",temp2->name);
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
    if(number[0]=='0')
        return isNumber(number+1);
    else
    {
        int index = 0;
        int flag = 0;
        while (number[index]!='\0')
        {
            if(isdigit(number[index++]))
                continue;
            else if(number[0]=='.')
            {
                if(flag>1)
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
    tempNum = 1;
    tabNum = 0;
    GlobalFlag = 0;
    ConstStringNum = 0;
    if (NULL == symbolTable)
    {
        printf("Create symbolTable failed\n");
        return NULL;
    }
    init_queue(&FuncHead, MAX_NUM);
    init_queue(&FuncBody, MAX_NUM);
    init_queue(&GlobalContext, MAX_NUM);
    char *Cname = getC_FileName();
    char *FileName = getllvmFileName(Cname);
    FILE *fp = fopen(FileName, "w+");
    fprintf(fp, "; ModuleID = `%s`\n", Cname);
    fprintf(fp, "source_filename = \"%s\"\n", Cname);
    fprintf(fp, "target datalayout = \"e-m:e-i64:64-f80:128-n8:16:32:64-S128\"\n");
    fprintf(fp, "target triple = %s", sampleOsType());
    fclose(fp);
    free(Cname);
    return FileName;
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
    strcpy(symbol->string,string);
    symbol_push(symbolTable, symbol);
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
    ptrast parameterHead  = parameter;
    char serial[10];
    while ((parameter = parameter->next) != NULL)
        ++tempNum;
    ++tempNum;
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
            sprintf(copyParameter,"%s%s = alloca %s, align %d\n",Tab,serial,dataType,align);
            que_push(FuncBody,strdup(copyParameter));
            sprintf(copyParameter,"%sstore %s %%%d, %s* %s, align %d\n",Tab,dataType,paraOrder++,dataType,serial,align);
            que_push(FuncBody,strdup(copyParameter));
        }
        strcat(Buffer, dataType);
        strcat(Buffer, ",");
    }
    int bufferLen = strlen(Buffer);
    if(bufferLen>1)
        Buffer[bufferLen - 1] = ')';
    else
    {
        Buffer[bufferLen] = ')';
        Buffer[bufferLen+1] = '\0';
    }
    sprintf(funcHead, "define dso_local %s @%s%s #0 {\t", bitTypeJudge(ReturnType), FuncName, Buffer);
    que_push(FuncHead, funcHead);
    genStatement(statement);
    hash_stack_pop(symbolTable);
    que_push(FuncBody,"}\n\n");
    return 0;
}

int genStatement(ptrast root)
{
    if(!root)
        return -1;
    if (!strcmp(root->nodetype, "IF_Stmt"))
    {
    }
    else if (!strcmp(root->nodetype, "WhileStmt"))
    {
    }
    else if (!strcmp(root->nodetype, "ReturnStmt"))
    {
    }
    else if (!strcmp(root->nodetype, "PrintStmt"))
    {
    }
    else if (!strcmp(root->nodetype, "ScanStmt"))
    {
    }
    else if (!strcmp(root->nodetype, "VariableDec"))
    {
        while (root)
        {
            genVarDec(root);
            root = root->next;
        }
    }
    else
        genExpr(root);
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
                if (!addSymbol("-1", 0, VarType, "\0", VarName))
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
                if (!strcmp(VarType, "STR"))
                {
                    symbol = (ptrSb)symbol_get(symbolTable, rightValue);
                    int length = strlen(symbol->string);
                    sprintf(Buffer, "@%s = dso_local global i8* getelementptr inbounds ([%d x i8], [%d x i8]* @%s, i32 0, i32 0), align 8\n", VarName, length+1, length+1, rightValue);
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
                sprintf(serial,"%%%d",tempNum++);
                if (!addSymbol(strdup(serial), 0, VarType, "\0", VarName))
                    return false;
                sprintf(Buffer, "%s%s = alloca %s, align %d\n",Tab,serial, bitCode, align);
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
                    sprintf(serial,"%%%d",tempNum++);
                    sprintf(Buffer,"%s%s = alloca i8*, align 8\n",Tab,serial);
                    que_push(FuncBody,strdup(Buffer));
                    if(rightValue[0] == '.')
                        sprintf(Buffer, "%sstore i8* getelementptr inbounds ([%d x i8], [%d x i8]* @%s, i32 0, i32 0), i8** %s, align 8\n",Tab ,length+1, length+1, rightValue,serial);
                    else
                    {
                        sprintf(Buffer,"%s%%%d = load i8*, i8** %s, align 8\n",Tab,tempNum++,symbol->serial);
                        que_push(FuncBody,strdup(Buffer));
                        sprintf(Buffer,"%sstore i8* %%%d, i8** %s, align 8\n",Tab,tempNum-1,serial);
                    }
                    if (!addSymbol(serial, 0, VarType, symbol->string, VarName))
                        return false;
                }
                else if (!strcmp(VarType, "INT"))
                {
                    sprintf(serial,"%%%d",tempNum++);
                    sprintf(Buffer,"%s%s = alloca i32, align 4\n",Tab ,serial);
                    que_push(FuncBody,strdup(Buffer));
                   // printf("%s\n",rightValue);
                    if(isNumber(rightValue))
                    {
                        sprintf(Buffer, "%sstore i32 %s, i32* %s, align 4\n",Tab ,rightValue, serial);
                        if (!addSymbol(serial, atof(rightValue), VarType, "\0", VarName))
                            return false;
                    }
                    else if(rightValue[0]=='%')
                    {
                        sprintf(Buffer,"%sstore i32 %s, i32* %s, align 4\n",Tab ,rightValue,serial);
                        if (!addSymbol(serial, 0, VarType, "\0", VarName))
                            return false;
                    }
                    else
                    {
                        symbol = (ptrSb)symbol_get(symbolTable,rightValue);
                        sprintf(Buffer,"%sstore i32 %s, i32* %s, align 4\n",Tab ,symbol->serial,serial);
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
        //symbol2 = (ptrSb)symbol_get(symbolTable,rightOp);
        if (strcmp(symbol->type, "STR") != 0)
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
    else if (!strcmp(root->nodetype, "%%"))
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
        char *temp = malloc(4000);
        temp = strdup(root->content);
        temp[strlen(temp)-1] = '\0';
        ++temp;
       // printf("TEMP:%s\n",temp);
        if (ConstStringNum == 0)
        {
            sprintf(buffer, "@.str = private unnamed_addr constant [%d x i8] c\"%s\\00\", align 1\n", strlen(temp) + 1, temp);
            ConstStringNum++;
            que_push(GlobalContext, buffer);
            addSymbol("-1", 0, "STR", temp, ".str");
            return ".str";
        }
        else
        {
            char *strName = malloc(30);
            sprintf(strName, ".str.%d", ConstStringNum++);
            sprintf(buffer, "@%s = private unnamed_addr constant [%d x i8] c\"%s\\00\", align 1\n", strName, strlen(temp) + 1, temp);
            que_push(GlobalContext, buffer);
            addSymbol("-1", 0, "STR", temp, strName);
            return strName;
        }
    }
    else if (!strcmp(root->nodetype,"VariableRef"))
    {
        return root->content;
    }
}

void outputLLVM()
{
    char *fileName = Init();
    //freopen(fileName, "a+", stdout);
    produceAst();
    //showAst(astRoot,0);
    genCode(astRoot);
    outputQue(*GlobalContext);
    outputQue(*FuncHead);
    outputQue(*FuncBody); 
    Destroy_que(&GlobalContext);
    Destroy_que(&FuncHead);
    Destroy_que(&FuncBody);
    free(fileName);
    return;
}

int main()
{
    outputLLVM();
    freeAst(astRoot);
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
