; ModuleID = `test.c`
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@aa = common dso_local global i8* null, align 8
@.str = private unnamed_addr constant [6 x i8] c"12345\00", align 1
@bbbb = dso_local global i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), align 8
@.str.1 = private unnamed_addr constant [4 x i8] c"ccc\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"aaa\00", align 1


declare dso_local void @free(i8*) #1

declare dso_local i8* @malloc(i64) #1

declare dso_local i64 @strlen(i8*) #2

declare dso_local i8* @strcpy(i8*, i8*) #1

define dso_local i8* @StrAssign(i32, i32, i8*, i8*) #0 {
	%5 = alloca i8*, align 8
	%6 = alloca i32, align 4
	%7 = alloca i32, align 4
	%8 = alloca i8*, align 8
	%9 = alloca i8*, align 8
	store i32 %0, i32* %6, align 4
	store i32 %1, i32* %7, align 4
	store i8* %2, i8** %8, align 8
	store i8* %3, i8** %9, align 8
	%10 = load i32, i32* %7, align 4
	%11 = icmp ne i32 %10, 0
	br i1 %11, label %12, label %19
	; <label>:12:                                     ; preds = %4
	%13 = load i32, i32* %6, align 4
	%14 = icmp ne i32 %13, 0
	br i1 %14, label %15, label %17

	; <label>:15:                                     ; preds = %12
	%16 = load i8*, i8** %8, align 8
	call void @free(i8* %16) #4
	br label %17

	; <label>:17:                                     ; preds = %15, %12
	%18 = load i8*, i8** %9, align 8
	store i8* %18, i8** %5, align 8
	br label %40

	; <label>:19:                                     ; preds = %4
	%20 = load i32, i32* %6, align 4
	%21 = icmp ne i32 %20, 0
	br i1 %21, label %26, label %22

	; <label>:22:                                     ; preds = %19
	%23 = load i8*, i8** %9, align 8
	%24 = call i64 @strlen(i8* %23) #5
	%25 = call noalias i8* @malloc(i64 %24) #4
	store i8* %25, i8** %8, align 8
	br label %35

	; <label>:26:                                     ; preds = %19
	%27 = load i32, i32* %6, align 4
	%28 = icmp ne i32 %27, 0
	br i1 %28, label %29, label %34

	; <label>:29:                                     ; preds = %26

	%30 = load i8*, i8** %8, align 8

	call void @free(i8* %30) #4

	%31 = load i8*, i8** %9, align 8

	%32 = call i64 @strlen(i8* %31) #5

	%33 = call noalias i8* @malloc(i64 %32) #4

	store i8* %33, i8** %8, align 8
	br label %34

	; <label>:34:                                     ; preds = %29, %26
	br label %35

	; <label>:35:                                     ; preds = %34, %22
	%36 = load i8*, i8** %8, align 8
	%37 = load i8*, i8** %9, align 8
	%38 = call i8* @strcpy(i8* %36, i8* %37) #4
	%39 = load i8*, i8** %8, align 8
	store i8* %39, i8** %5, align 8
	br label %40

	; <label>:40:                                     ; preds = %35, %17
	%41 = load i8*, i8** %5, align 8
	ret i8* %41
}


declare dso_local i8* @strcat(i8*,i8*) #1

define dso_local i8* @StrSum(i8*, i8*) #0 {
	%3 = alloca i8*, align 8
	%4 = alloca i8*, align 8
	%5 = alloca i8*, align 8
	store i8* %0, i8** %3, align 8
	store i8* %1, i8** %4, align 8
	%6 = load i8*, i8** %3, align 8
	%7 = call i64 @strlen(i8* %6) #4
	%8 = load i8*, i8** %4, align 8
	%9 = call i64 @strlen(i8* %8) #4
	%10 = add i64 %7, %9
	%11 = call noalias i8* @malloc(i64 %10) #3
	store i8* %11, i8** %5, align 8
	%12 = load i8*, i8** %5, align 8
	%13 = load i8*, i8** %3, align 8
	%14 = call i8* @strcat(i8* %12, i8* %13) #3
	%15 = load i8*, i8** %5, align 8
	%16 = load i8*, i8** %4, align 8
	%17 = call i8* @strcat(i8* %15, i8* %16) #3
	%18 = load i8*, i8** %5, align 8
	ret i8* %18
}


define dso_local i32 @main() #0 {	
	%1 = alloca i32, align 4
	store i32 0, i32* %1, align 4
	%2 = alloca i32, align 4
	store i32 1, i32* %2, align 4
	%3 = alloca i32, align 4
	store i32 1, i32* %3, align 4
	%4 = load i32, i32* %3, align 4
	%5 = mul nsw i32 %4, 3
	store i32 %5, i32* %2, align 4
	%6 = load i32, i32* %2, align 4
	%7 = load i32, i32* %2, align 4
	%8 = add nsw i32 %6, %7
	store i32 %8, i32* %3, align 4
	%9 = load i32, i32* %2, align 4
	%10 = load i32, i32* %3, align 4
	%11 = sdiv nsw i32 %9, %10
	store i32 %11, i32* %3, align 4
	%12 = load i32, i32* %3, align 4
	%13 = load i32, i32* %3, align 4
	%14 = add nsw i32 %12, %13
	%15 = load i32, i32* %14, align 4
	%16 = load i32, i32* %3, align 4
	%17 = add nsw i32 %15, %16
	%18 = load i32, i32* %17, align 4
	%19 = load i32, i32* %3, align 4
	%20 = add nsw i32 %18, %19
	store i32 %20, i32* %2, align 4
	%21 = load i32, i32* %2, align 4
	%22 = sdiv nsw i32 %21, 1
	store i32 %22, i32* %2, align 4
	%23 = load i32, i32* %3, align 4
	%24 = load i32, i32* a, align 4
	%25 = mul nsw i32 %23, %24
	store i32 %25, i32* %3, align 4
	%26 = load i32, i32* %3, align 4
	%27 = load i32, i32* b, align 4
	%28 = add nsw i32 %26, %27
	store i32 %28, i32* %3, align 4
	%29 = load i32, i32* %2, align 4
	%30 = load i32, i32* %3, align 4
	%31 = add nsw i32 %29, %30
	%32 = load i32, i32* %3, align 4
	%33 = load i32, i32* %31, align 4
	%34 = sub nsw i32 %32, %33
	store i32 %34, i32* %3, align 4
	store i32 900, i32* %2, align 4
	%35 = call i8* @StrAssign(i32 0 ,i32 0,i8* -1, i8* .str.1)
	store i8* %35, i8** -1, align 8
	ret i32 0
}

define dso_local void @f(i8*) #0 {	
	%2 = alloca i8*, align 8
	store i8* %0, i8** %2, align 8
	%3 = alloca i8*, align 8
	%4 = call i8* @StrAssign(i32 1 ,i32 0,i8* %3, i8* .str.2)
	store i8* %4, i8** %3, align 8
	%5 = alloca i8*, align 8
	%6 = call noalias i8* @malloc(i64 4) #3
	store i8* %6, i8** %5, align 8
	%7 = load i8*, i8** %5, align 8
	%8 = call i8* @strcpy(i8* %7, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0)) #3
	%9 = call i8* @StrSum(i8* %3, i8* %5)
	%10 = alloca i8*, align 8
	store i8* %9, i8** %10, align 8
	%11 = call i8* @StrAssign(i32 1 ,i32 0,i8* %10, i8* %2)
	store i8* %11, i8** %10, align 8
}

define dso_local i8* @mm(i8*) #0 {	
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
	ret i8* %2
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }
attributes #4 = { nounwind readonly }
