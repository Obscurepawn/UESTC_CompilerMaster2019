#include "ast.h"
#include "queue.h"
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
// #include "inttypes.h"
// #include "llvm-c/Core.h"
// #include "llvm-c/ExecutionEngine.h"
// #include "llvm-c/Target.h"
// #include "llvm-c/Analysis.h"
// #include "llvm-c/BitWriter.h"

#define MAX_FILENAME 255

extern ptrast astRoot;
pqe GlobalDec;
pqe FuncDec;
pqe FuncBody;

char* getC_FileName();
char* llvmFileName(char *filename);
char *getFileName();
char* sampleOsType();
void init();

bool genCode(ptrast root);
bool genFuncDef(ptrast root);
bool genVarDec(ptrast root);


char *getLLVMalloca();
char *getLLVMstore();
char *getLLVMload();
char *getLLVMglobalStr();
char *getLLVMglobalInt();
char *getLLVMstaticStr();
char *getLLVMstaticInt();

char* getC_FileName()
{
    char *fileName = (char*)malloc(sizeof(MAX_FILENAME));
    sprintf(fileName,__FILE__);
    return fileName;   
}

char* llvmFileName(char *filename)
{
    char *ChangeStart = filename + strlen(filename) - 1;
    ChangeStart[0] = 'l';
    ChangeStart[1] = 'l';
    ChangeStart[2] = '\0';
    return filename;
}

char *getFileName()
{
	char *filename = getC_FileName();
	filename = llvmFileName(filename);
	return filename;	
}

char* sampleOsType()
{
    int fp=0;
    char *Buffer = (char*)malloc(10);
    char *file="/proc/sys/kernel/ostype";
    fp = open(file, O_RDONLY);
    if (fp == 0)
    {
        printf("error to open: %s\n", file);
        exit(EXIT_FAILURE);
    }
    read(fp, (void *)Buffer, 6);
    Buffer[strlen(Buffer)-1]=0;
    close(fp);
    if(strstr("Linux",Buffer))
        return "\"x86_64-pc-linux-gnu\"\n";
    else if(strstr("Mac",Buffer))
        return "\"x86_64-pc-max-gnu\"\n";
    else if(strstr("Windows",Buffer))
        return "\"x86_64-pc-windows-gnu\"\n";
 }

void init()
{
    char *Cname = getC_FileName();
	char *FileName = getllvmFileName(Cname);
    FILE *fp = fopen(FileName,"a+");
    fprintf(fp,"; ModuleID = `%s`\n",Cname);
    fprintf(fp,"source_filename = \"%s\"\n",Cname);
    fprintf(fp,"target datalayout = \"e-m:e-i64:64-f80:128-n8:16:32:64-S128\"\n");
    fprintf(fp,"target triple = %s",sampleOsType());
    fclose(fp);
	return;
}

bool genCode(ptrast root)
{
	if(!root)
	return false;
	init();
	if(!strcmp(root->nodetype,"FunctionDef"))
		genFuncDef(root);
	else if(!strcmp(root->nodetype,"VariableDec"))
		genVarDec(root);
	genCode(root->next);
	return true;
}

int main(int argc,char const *argv[])
{
	return 0;
}



//*** LLVM-C Sample ***/
// int main(int argc, char const *argv[]) {
//     LLVMModuleRef mod = LLVMModuleCreateWithName("my_module");
//     LLVMTypeRef param_types[] = { LLVMInt32Type(), LLVMInt32Type() };
//     LLVMTypeRef ret_type = LLVMFunctionType(LLVMInt32Type(), param_types, 2, 0);
//     LLVMValueRef sum = LLVMAddFunction(mod, "sum", ret_type);

//     LLVMBasicBlockRef entry = LLVMAppendBasicBlock(sum, "entry");

//     LLVMBuilderRef builder = LLVMCreateBuilder();
//     LLVMPositionBuilderAtEnd(builder, entry);
//     LLVMValueRef tmp = LLVMBuildAdd(builder, LLVMGetParam(sum, 0), LLVMGetParam(sum, 1), "tmp");
//     LLVMBuildRet(builder, tmp);

//     char *error = NULL;
//     LLVMVerifyModule(mod, LLVMAbortProcessAction, &error);
//     LLVMDisposeMessage(error);

//     LLVMExecutionEngineRef engine;
//     error = NULL;

// 	/**must needed target**/
//     LLVMInitializeNativeTarget();
//     LLVMInitializeNativeAsmPrinter();
// 	/**********************/

//     LLVMLinkInMCJIT();
//     if (LLVMCreateExecutionEngineForModule(&engine, mod, &error) != 0) {
//         fprintf(stderr, "failed to create execution engine\n");
//         abort();
//     }
//     if (error) {
//         fprintf(stderr, "error: %s\n", error);
//         LLVMDisposeMessage(error);
//         exit(EXIT_FAILURE);
//     }

//     if (argc < 3) {
//         fprintf(stderr, "usage: %s x y\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }
//     long long x = strtoll(argv[1], NULL, 10);
//     long long y = strtoll(argv[2], NULL, 10);
// 	printf("%lld,%lld\n",x,y);

// 	// these codes didn't work
//     // LLVMGenericValueRef args[] = {
//     //     LLVMCreateGenericValueOfInt(LLVMInt32Type(), x, 0),
//     //     LLVMCreateGenericValueOfInt(LLVMInt32Type(), y, 0)
//     // };
//     // LLVMGenericValueRef res = LLVMRunFunction(engine, sum, 2, args);
//     // printf("%d\n", (int)LLVMGenericValueToInt(res, 0));

//     // Write out bitcode to file
// 	int (*sum_func)(int, int) = (int (*)(int, int))LLVMGetFunctionAddress(engine, "sum");
// 	//system("read -p 'Press Enter to continue...' var");
// 	//sum_func(x, y);
// 	printf("%d\n", sum_func(x, y));
//     if (LLVMWriteBitcodeToFile(mod, "sum.bc") != 0) {
//         fprintf(stderr, "error writing bitcode to file, skipping\n");
//     }
//     LLVMDisposeBuilder(builder);
//     LLVMDisposeExecutionEngine(engine);
// 	return 0;
// }

