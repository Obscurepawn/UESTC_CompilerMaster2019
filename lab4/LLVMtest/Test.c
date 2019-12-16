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


// #include<stdio.h>
// int putEnd()
// {
//     printf("attributes #0 = { noinline nounwind optnone uwtable \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+fxsr,+mmx,+sse,+sse2,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\nattributes #1 = { nounwind \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+fxsr,+mmx,+sse,+sse2,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\nattributes #2 = { nounwind readonly \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"false\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+fxsr,+mmx,+sse,+sse2,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\nattributes #3 = { nounwind }\nattributes #4 = { nounwind readonly }\n");
//     return 0;
// }