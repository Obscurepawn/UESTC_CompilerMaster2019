; ModuleID = `test.c`
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = dso_local global i32 33, align 4
@b = common dso_local global i32 0, align 4
@c = dso_local global i32 44, align 4
@bb = dso_local global i32 3, align 4
@.str = private unnamed_addr constant [6 x i8] c"12345\00", align 1
@aaa = dso_local global i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), align 8
@bbb = common dso_local global i8* null, align 8
@.str.1 = private unnamed_addr constant [4 x i8] c"aaa\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"ccc\00", align 1

define dso_local i32 @main() #0 {	
	%1 = alloca i32, align 4
	store i32 0, i32* %1, align 4
	%2 = alloca i32, align 4
	store i32 1, i32* %2, align 4
	%3 = alloca i32, align 4
	store i32 1, i32* %3, align 4
	%4 = load i32, i32* %2, align 4
	%5 = sdiv nsw i32 %4, 1
	store i32 %5, i32* %2, align 4
	%6 = load i32, i32* %3, align 4
	%7 = load i32, i32* a, align 4
	%8 = mul nsw i32 %6, %7
	store i32 %8, i32* %3, align 4
	%9 = load i32, i32* %3, align 4
	%10 = load i32, i32* b, align 4
	%11 = add nsw i32 %9, %10
	store i32 %11, i32* %3, align 4
	%12 = load i32, i32* %2, align 4
	%13 = load i32, i32* %3, align 4
	%14 = add nsw i32 %12, %13
	%15 = load i32, i32* %3, align 4
	%16 = load i32, i32* %14, align 4
	%17 = sub nsw i32 %15, %16
	store i32 %17, i32* %3, align 4
}

define dso_local void @f(i8*) #0 {	
	%2 = alloca i8*, align 8
	store i8* %0, i8** %2, align 8
	%3 = alloca i8*, align 8
	%4 = call noalias i8* @malloc(i64 4) #3
	store i8* %4, i8** %3, align 8
	%5 = load i8*, i8** %3, align 8
	%6 = call i8* @strcpy(i8* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0)) #3
	%7 = alloca i8*, align 8
	%8 = call noalias i8* @malloc(i64 4) #3
	store i8* %8, i8** %7, align 8
	%9 = load i8*, i8** %7, align 8
	%10 = call i8* @strcpy(i8* %9, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0)) #3
	%11 = alloca i8*, align 8
	%12 = load i8*, i8** %2, align 8
	store i8* %12, i8** %11, align 8
}

define dso_local void @mm(i8*) #0 {	
	%2 = alloca i8*, align 8
	store i8* %0, i8** %2, align 8
	%3 = alloca i32, align 4
	store i32 1, i32* %3, align 4
	%4 = alloca i32, align 4
	store i32 1, i32* %4, align 4
	%5 = load i32, i32* %4, align 4
	%6 = mul nsw i32 %5, 2
	store i32 %6, i32* %3, align 4
	%7 = load i32, i32* %3, align 4
	%8 = load i32, i32* %4, align 4
	%9 = add nsw i32 %7, %8
	%10 = alloca i32, align 4
	store i32 %9, i32* %10, align 4
	%11 = load i32, i32* %10, align 4
	%12 = load i32, i32* %3, align 4
	%13 = mul nsw i32 %11, %12
	%14 = alloca i32, align 4
	store i32 %13, i32* %14, align 4
	%15 = load i32, i32* %10, align 4
	%16 = load i32, i32* %3, align 4
	%17 = sdiv nsw i32 %15, %16
	%18 = alloca i32, align 4
	store i32 %17, i32* %18, align 4
	%19 = load i32, i32* %10, align 4
	%20 = load i32, i32* %3, align 4
	%21 = sub nsw i32 %19, %20
	%22 = alloca i32, align 4
	store i32 %21, i32* %22, align 4
	%23 = alloca i32, align 4
	store i32 2, i32* %23, align 4
	%24 = alloca i32, align 4
	store i32 8, i32* %24, align 4
	%25 = alloca i32, align 4
	store i32 2, i32* %25, align 4
	%26 = alloca i32, align 4
	store i32 0, i32* %26, align 4
	%27 = load i32, i32* %10, align 4
	%28 = load i32, i32* %3, align 4
	%29 = serm i32 %27, %28
	%30 = alloca i32, align 4
	store i32 %29, i32* %30, align 4
}

