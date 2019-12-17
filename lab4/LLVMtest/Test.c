// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>
// #include<unistd.h>
// #include<sys/types.h>
// #include<sys/stat.h>
// #include<fcntl.h>

// char* sampleOsType();
// char* getC_FileName();

// int tempNum;


// #define O_RDONLY 00
// #define EXIT_FAILURE 1
// #define MAX_FILENAME 255

// char* getC_FileName()
// {
//     char *fileName = (char*)malloc(MAX_FILENAME);
//     sprintf(fileName,__FILE__);
//     return fileName;   
// }

// char* getllvmFileName(char *filename)
// {
//     char *ChangeStart = filename + strlen(filename) - 1;
//     ChangeStart[0] = 'l';
//     ChangeStart[1] = 'l';
//     ChangeStart[2] = '\0';
//     return filename;
// }

// char *getFileName()
// {
// 	char *filename = getC_FileName();
// 	filename = getllvmFileName(filename);
// 	return filename;	
// }

// void init()
// {
//     tempNum = 0;
//     char *Cname = getC_FileName();
// 	char *FileName = getFileName(Cname);
//     FILE *fp = fopen(FileName,"a+");
//     fprintf(fp,"; ModuleID = `%s`\n",Cname);
//     fprintf(fp,"source_filename = \"%s\"\n",Cname);
//     fprintf(fp,"target datalayout = \"e-m:e-i64:64-f80:128-n8:16:32:64-S128\"\n");
//     fprintf(fp,"target triple = %s",sampleOsType());
//     fclose(fp);
// 	return;
// }

//  char* sampleOsType(){
//      int fp=0;
//      char *Buffer = (char*)malloc(10);
//      char *file="/proc/sys/kernel/ostype";
//      fp = open(file, O_RDONLY);
//      if (fp == 0)
//      {
//          printf("error to open: %s\n", file);
//          exit(EXIT_FAILURE);
//      }
//      read(fp, (void *)Buffer, 6);
//      Buffer[strlen(Buffer)-1]=0;
//      close(fp);
//      if(strstr("Linux",Buffer))
//         return "\"x86_64-pc-linux-gnu\"\n";
//      else if(strstr("Mac",Buffer))
//         return "\"x86_64-pc-max-gnu\"\n";
//      else if(strstr("Windows",Buffer))
//         return "\"x86_64-pc-windows-gnu\"\n";
//  }
 
// // void test_sampleOSType()
// // {
// //     printf("%s",sampleOsType());
// // } 

// // void test_getC_FILENAME_llvmFileName()
// // {
// // 	char *filename = getC_FileName();
// // 	filename = llvmFileName(filename);
// // 	printf("%s\n",filename);
// // }

// void test_init()
// {
//     init();
//     return;
// }

// int main()
// {
//     test_init();
// 	return 0;
// }


#include<stdio.h>
int main()
{
	printf("\ndefine dso_local i8* @StrAssign(i32, i32, i8*, i8*) #0 {\n\t%5 = alloca i8*, align 8\n\t%6 = alloca i32, align 4\n\t%7 = alloca i32, align 4\n\t%8 = alloca i8*, align 8\n\t%9 = alloca i8*, align 8\n\tstore i32 %0, i32* %6, align 4\n\tstore i32 %1, i32* %7, align 4\n\tstore i8* %2, i8** %8, align 8\n\tstore i8* %3, i8** %9, align 8\n\t%10 = load i32, i32* %7, align 4\n\t%11 = icmp ne i32 %10, 0\n\tbr i1 %11, label %12, label %19\n\t; <label>:12:                                     ; preds = %4\n\t%13 = load i32, i32* %6, align 4\n\t%14 = icmp ne i32 %13, 0\n\tbr i1 %14, label %15, label %17\n\n\t; <label>:15:                                     ; preds = %12\n\t%16 = load i8*, i8** %8, align 8\n\tcall void @free(i8* %16) #4\n\tbr label %17\n\n\t; <label>:17:                                     ; preds = %15, %12\n\t%18 = load i8*, i8** %9, align 8\n\tstore i8* %18, i8** %5, align 8\n\tbr label %40\n\n\t; <label>:19:                                     ; preds = %4\n\t%20 = load i32, i32* %6, align 4\n\t%21 = icmp ne i32 %20, 0\n\tbr i1 %21, label %26, label %22\n\n\t; <label>:22:                                     ; preds = %19\n\t%23 = load i8*, i8** %9, align 8\n\t%24 = call i64 @strlen(i8* %23) #5\n\t%25 = call noalias i8* @malloc(i64 %24) #4\n\tstore i8* %25, i8** %8, align 8\n\tbr label %35\n\n\t; <label>:26:                                     ; preds = %19\n\t%27 = load i32, i32* %6, align 4\n\t%28 = icmp ne i32 %27, 0\n\tbr i1 %28, label %29, label %34\n\n\t; <label>:29:                                     ; preds = %26\n\n\t%30 = load i8*, i8** %8, align 8\n\n\tcall void @free(i8* %30) #4\n\n\t%31 = load i8*, i8** %9, align 8\n\n\t%32 = call i64 @strlen(i8* %31) #5\n\n\t%33 = call noalias i8* @malloc(i64 %32) #4\n\n\tstore i8* %33, i8** %8, align 8\n\tbr label %34\n\n\t; <label>:34:                                     ; preds = %29, %26\n\tbr label %35\n\n\t; <label>:35:                                     ; preds = %34, %22\n\t%36 = load i8*, i8** %8, align 8\n\t%37 = load i8*, i8** %9, align 8\n\t%38 = call i8* @strcpy(i8* %36, i8* %37) #4\n\t%39 = load i8*, i8** %8, align 8\n\tstore i8* %39, i8** %5, align 8\n\tbr label %40\n\n\t; <label>:40:                                     ; preds = %35, %17\n\t%41 = load i8*, i8** %5, align 8\n\tret i8* %41\n}\n\n");
    return 0;
}