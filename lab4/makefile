FLAGS=$(shell llvm-config --cflags --ldflags --libs)
FILE_NAME = genllvm

lrparser:main.o lrparser.tab.o ast.o lex.yy.o  
	gcc -o lrparser main.o lrparser.tab.o ast.o lex.yy.o
	$(RM) *.o lex.yy.c *.tab.h *.tab.c *.bc

main.o:main.c lrparser.tab.h ast.h
	gcc -c main.c

lrparser.tab.o:lrparser.tab.c ast.h
	gcc -c lrparser.tab.c

lex.yy.o:lex.yy.c lrparser.tab.h
	gcc -c lex.yy.c

ast.o:ast.c ast.h
	gcc -c ast.c

lex.yy.c:lrlex.l
	flex lrlex.l

lrparser.tab.c lrparser.tab.h:lrparser.y
	bison -d lrparser.y

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