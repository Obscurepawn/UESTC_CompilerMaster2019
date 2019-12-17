; ModuleID = 'LLVMReference.c'
source_filename = "LLVMReference.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"ccc\00", align 1
@v = dso_local global i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), align 8
@.str.1 = private unnamed_addr constant [7 x i8] c"kkkkkk\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"aaa\00", align 1
@e = common dso_local global i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @tteesst() #0 {
  %1 = alloca i8*, align 8
  %2 = call noalias i8* @malloc(i64 100) #3
  store i8* %2, i8** %1, align 8
  %3 = load i8*, i8** %1, align 8
  %4 = call i8* @strcpy(i8* %3, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0)) #3
  %5 = load i8*, i8** %1, align 8
  ret i8* %5
}

; Function Attrs: nounwind
declare dso_local noalias i8* @malloc(i64) #1

; Function Attrs: nounwind
declare dso_local i8* @strcpy(i8*, i8*) #1

; Function Attrs: noinline nounwind optnone uwtable
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
  call void @free(i8* %16) #3
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
  %24 = call i64 @strlen(i8* %23) #4
  %25 = call noalias i8* @malloc(i64 %24) #3
  store i8* %25, i8** %8, align 8
  br label %35

; <label>:26:                                     ; preds = %19
  %27 = load i32, i32* %6, align 4
  %28 = icmp ne i32 %27, 0
  br i1 %28, label %29, label %34

; <label>:29:                                     ; preds = %26
  %30 = load i8*, i8** %8, align 8
  call void @free(i8* %30) #3
  %31 = load i8*, i8** %9, align 8
  %32 = call i64 @strlen(i8* %31) #4
  %33 = call noalias i8* @malloc(i64 %32) #3
  store i8* %33, i8** %8, align 8
  br label %34

; <label>:34:                                     ; preds = %29, %26
  br label %35

; <label>:35:                                     ; preds = %34, %22
  %36 = load i8*, i8** %8, align 8
  %37 = load i8*, i8** %9, align 8
  %38 = call i8* @strcpy(i8* %36, i8* %37) #3
  %39 = load i8*, i8** %8, align 8
  store i8* %39, i8** %5, align 8
  br label %40

; <label>:40:                                     ; preds = %35, %17
  %41 = load i8*, i8** %5, align 8
  ret i8* %41
}

; Function Attrs: nounwind
declare dso_local void @free(i8*) #1

; Function Attrs: nounwind readonly
declare dso_local i64 @strlen(i8*) #2

; Function Attrs: noinline nounwind optnone uwtable
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

; Function Attrs: nounwind
declare dso_local i8* @strcat(i8*, i8*) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8** %6, align 8
  %12 = call noalias i8* @malloc(i64 4) #3
  store i8* %12, i8** %7, align 8
  %13 = load i8*, i8** %7, align 8
  %14 = load i8*, i8** %6, align 8
  %15 = call i8* @StrAssign(i32 1, i32 0, i8* %13, i8* %14)
  store i8* %15, i8** %7, align 8
  %16 = call noalias i8* @malloc(i64 100) #3
  store i8* %16, i8** %8, align 8
  %17 = load i8*, i8** %8, align 8
  %18 = load i8*, i8** %6, align 8
  %19 = call i8* @StrAssign(i32 1, i32 0, i8* %17, i8* %18)
  store i8* %19, i8** %8, align 8
  %20 = load i8*, i8** %7, align 8
  %21 = getelementptr inbounds i8, i8* %20, i64 0
  %22 = load i8, i8* %21, align 1
  %23 = load i8*, i8** %8, align 8
  %24 = getelementptr inbounds i8, i8* %23, i64 2
  store i8 %22, i8* %24, align 1
  store i32 9, i32* %9, align 4
  store i32 1, i32* %10, align 4
  %25 = load i32, i32* %9, align 4
  %26 = load i32, i32* %10, align 4
  %27 = sdiv i32 %25, %26
  store i32 %27, i32* %11, align 4
  ret i32 8
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @TEST(i8*) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %5 = load i8*, i8** %2, align 8
  store i8* %5, i8** %3, align 8
  %6 = load i8*, i8** %3, align 8
  store i8* %6, i8** %4, align 8
  %7 = load i8*, i8** %3, align 8
  ret i8* %7
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }
attributes #4 = { nounwind readonly }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 8.0.1-3+b1 (tags/RELEASE_801/final)"}
