; ModuleID = 'LLVMReference.c'
source_filename = "LLVMReference.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"ccc\00", align 1
@v = dso_local global i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), align 8
@main.d = internal global i32 0, align 4
@.str.1 = private unnamed_addr constant [4 x i8] c"aaa\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"bbb\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@__const.test.a = private unnamed_addr constant [10 x i8] c"aaaaaaaaaa", align 1
@e = common dso_local global i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca double, align 8
  %3 = alloca i32, align 4
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  store i32 0, i32* %1, align 4
  store double 0.000000e+00, double* %2, align 8
  store i32 0, i32* %3, align 4
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8** %4, align 8
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8** %5, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = call i64 @strlen(i8* %7) #5
  %9 = load i8*, i8** %5, align 8
  %10 = call i64 @strlen(i8* %9) #5
  %11 = add i64 %8, %10
  %12 = call noalias i8* @malloc(i64 %11) #6
  store i8* %12, i8** %6, align 8
  %13 = load i8*, i8** %6, align 8
  %14 = load i8*, i8** %4, align 8
  %15 = call i8* @strcat(i8* %13, i8* %14) #6
  %16 = load i8*, i8** %6, align 8
  %17 = load i8*, i8** %5, align 8
  %18 = call i8* @strcat(i8* %16, i8* %17) #6
  %19 = load i8*, i8** %6, align 8
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i8* %19)
  ret i32 0
}

; Function Attrs: nounwind
declare dso_local noalias i8* @malloc(i64) #1

; Function Attrs: nounwind readonly
declare dso_local i64 @strlen(i8*) #2

; Function Attrs: nounwind
declare dso_local i8* @strcat(i8*, i8*) #1

declare dso_local i32 @printf(i8*, ...) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local signext i8 @test() #0 {
  %1 = alloca [10 x i8], align 1
  %2 = bitcast [10 x i8]* %1 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %2, i8* align 1 getelementptr inbounds ([10 x i8], [10 x i8]* @__const.test.a, i32 0, i32 0), i64 10, i1 false)
  %3 = getelementptr inbounds [10 x i8], [10 x i8]* %1, i64 0, i64 6
  %4 = load i8, i8* %3, align 1
  ret i8 %4
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #4

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
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readonly }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 8.0.1-3+b1 (tags/RELEASE_801/final)"}
