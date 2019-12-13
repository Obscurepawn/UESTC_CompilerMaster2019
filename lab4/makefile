FLAGS=$(shell llvm-config --cflags --ldflags --libs)
FILE_NAME = genllvm

genllvm:genllvm.o main.o lrparser.tab.o ast.o lex.yy.o HashMap.o
	gcc -o $(FILE_NAME) genllvm.o main.o lrparser.tab.o ast.o lex.yy.o HashMap.o 
	$(RM) *.o lex.yy.c *.tab.h *.tab.c *.bc

genllvm.o:genllvm.c lrparser.tab.h 
	gcc -c genllvm.c

HashMap.o:HashMap.c HashMap.h
	gcc -c HashMap.c

lrparser.tab.c lrparser.tab.h:lrparser.y
	bison -d lrparser.y

main.o:main.c main.h
	gcc -c main.c

lrparser.tab.o:lrparser.tab.c ast.h
	gcc -c lrparser.tab.c

lex.yy.o:lex.yy.c lrparser.tab.h
	gcc -c lex.yy.c

ast.o:ast.c ast.h
	gcc -c ast.c

lex.yy.c:lrlex.l
	flex lrlex.l

windows_clang_build: 
	clang -target x86_64-pc-windows-gnu test.c -o hello.exe

windows_llvm_build:
	clang -target x86_64-pc-windows-gnu test.c -emit-llvm -S

llvm_api_build:
	clang -c `llvm-config --cflags --includedir` $(FILE_NAME).c
	clang++ $(FILE_NAME).o `llvm-config --libs  --system-libs  --cxxflags --ldflags` -o $(FILE_NAME)
	$(RM) *.o lex.yy.c *.tab.h *.tab.c *.bc

clean:
	$(RM) *.o lex.yy.c *.tab.h *.tab.c *.bc