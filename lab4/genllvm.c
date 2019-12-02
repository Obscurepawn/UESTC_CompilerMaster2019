#include "ast.h"
//#include "queue.h"
#include "inttypes.h"
#include "llvm-c/Core.h"
#include "llvm-c/ExecutionEngine.h"
#include "llvm-c/Target.h"
#include "llvm-c/Analysis.h"
#include "llvm-c/BitWriter.h"
#include <stdio.h>
#include <stdlib.h>

// extern ptrast astRoot;

// int main(int argc,char const *argv[])
// {
// 	return 0;
// }

// void init()
// {
// 	LLVMModuleRef mod = LLVMModuleCreateWithName("my_module");
//     LLVMDisposeModule(mod);
// 	return;
// }

// bool genCode(ptrast root)
// {
// 	if(!root)
// 	return false;
// 	init();
// 	if(!strcmp(root->nodetype,"FunctionDef"))
// 		genFuncDef(root);
// 	else if(!strcmp(root->nodetype,"VariableDec"))
// 		genVarDec(root);
// 	genCode(root->next);
// 	return true;
// }

// bool genFuncDef(ptrast root)
// {
// 	pqe paramQue;
// 	//pqe paramNameQue;
// 	init_queue(&paramQue,100); // the biggest number of the param is 100 
// 	//init_queue(&paramNameQue,100);
// 	char *ReturnType = root->content;
// 	ptrast FuncInf = root->left;
// 	//char *FunctionName = FuncInf->content;
// 	while(FuncInf->next!=NULL)
// 	{
// 		que_push(paramQue,FuncInf->next->nodetype);
// 		//que_push(paramNameQue,FuncInf->next->content);
// 		FuncInf = FuncInf->next;
// 	}
// 	LLVMTypeRef TypeRef[100];
// 	char *temp = NULL;
// 	int index = 0;
// 	while((temp = que_pop(paramQue))!=NULL)
// 	{
// 		if(!strcmp(temp,"INT"))
// 		TypeRef[index] = LLVMInt32Type();
// 		else if(!strcmp(temp,"VOID"))
// 		TypeRef[index] = LLVMVoidType();
// 		else if(!strcmp(temp,"STR"))
// 		TypeRef[index] = 
// 	}
// }

int main(int argc, char const *argv[]) {
    LLVMModuleRef mod = LLVMModuleCreateWithName("my_module");
    LLVMTypeRef param_types[] = { LLVMInt32Type(), LLVMInt32Type() };
    LLVMTypeRef ret_type = LLVMFunctionType(LLVMInt32Type(), param_types, 2, 0);
    LLVMValueRef sum = LLVMAddFunction(mod, "sum", ret_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(sum, "entry");

    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, entry);
    LLVMValueRef tmp = LLVMBuildAdd(builder, LLVMGetParam(sum, 0), LLVMGetParam(sum, 1), "tmp");
    LLVMBuildRet(builder, tmp);

    char *error = NULL;
    LLVMVerifyModule(mod, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);

    LLVMExecutionEngineRef engine;
    error = NULL;
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMLinkInMCJIT();
    if (LLVMCreateExecutionEngineForModule(&engine, mod, &error) != 0) {
        fprintf(stderr, "failed to create execution engine\n");
        abort();
    }
    if (error) {
        fprintf(stderr, "error: %s\n", error);
        LLVMDisposeMessage(error);
        exit(EXIT_FAILURE);
    }

    if (argc < 3) {
        fprintf(stderr, "usage: %s x y\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    long long x = strtoll(argv[1], NULL, 10);
    long long y = strtoll(argv[2], NULL, 10);
	printf("%lld,%lld\n",x,y);
	// these codes didn't work
    // LLVMGenericValueRef args[] = {
    //     LLVMCreateGenericValueOfInt(LLVMInt32Type(), x, 0),
    //     LLVMCreateGenericValueOfInt(LLVMInt32Type(), y, 0)
    // };
    // LLVMGenericValueRef res = LLVMRunFunction(engine, sum, 2, args);
    // printf("%d\n", (int)LLVMGenericValueToInt(res, 0));

    // Write out bitcode to file
	int (*sum_func)(int, int) = (int (*)(int, int))LLVMGetFunctionAddress(engine, "sum");
	//system("read -p 'Press Enter to continue...' var");
	//sum_func(x, y);
	printf("%d\n", sum_func(x, y));
    if (LLVMWriteBitcodeToFile(mod, "sum.bc") != 0) {
        fprintf(stderr, "error writing bitcode to file, skipping\n");
    }
    LLVMDisposeBuilder(builder);
    LLVMDisposeExecutionEngine(engine);
	return 0;
}

