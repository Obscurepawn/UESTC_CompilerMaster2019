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

define dso_local i8* @f(i8*) #0 {	
	%2 = alloca i8*, align 8
	store i8* %0, i8** %2, align 8
	%3 = alloca i8*, align 8
	%4 = call noalias i8* @malloc(i64 4) #3
	store i8* %4, i8** %3, align 8
	%5 = load i8*, i8** %3, align 8
	%6 = call i8* @strcpy(i8* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0)) #3
	%6 = alloca i8*, align 8
	%7 = call noalias i8* @malloc(i64 4) #3
	store i8* %7, i8** %6, align 8
	%8 = load i8*, i8** %6, align 8
	%9 = call i8* @strcpy(i8* %8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0)) #3
	%9 = alloca i8*, align 8
	%10 = load i8*, i8** %2, align 8
	store i8* %10, i8** %9, align 8
}

define dso_local i8* @mm(i8*) #0 {	
	%2 = alloca i8*, align 8
	store i8* %0, i8** %2, align 8
	%3 = alloca i32, align 4
	store i32 1, i32* %3, align 4
	%4 = alloca i32, align 4
	store i32 1, i32* %4, align 4
	%5 = load i32, i32* %3, align 4
	%6 = load i32, i32* %4, align 4
	%7 = add nsw i32 %3, %4
	%8 = alloca i32, align 4
	store i32 %7, i32* %8, align 4
	%9 = load i32, i32* %8, align 4
	%10 = load i32, i32* %3, align 4
	%11 = mul nsw i32 %8, %3
	%12 = alloca i32, align 4
	store i32 %11, i32* %12, align 4
	%13 = load i32, i32* %8, align 4
	%14 = load i32, i32* %3, align 4
	%15 = div nsw i32 %8, %3
	%16 = alloca i32, align 4
	store i32 %15, i32* %16, align 4
	%17 = load i32, i32* %8, align 4
	%18 = load i32, i32* %3, align 4
	%19 = sub nsw i32 %8, %3
	%20 = alloca i32, align 4
	store i32 %19, i32* %20, align 4
	%21 = load i32, i32* %8, align 4
	%22 = load i32, i32* %3, align 4
	%23 = srem i32 %8, %3
	%24 = alloca i32, align 4
	store i32 %23, i32* %24, align 4
}

