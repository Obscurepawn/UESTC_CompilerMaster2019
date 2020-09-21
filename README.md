Firstly,this file is simple LCC IR_Generator(Unfinished)  
But the LLVM-C API is independent from the parser;  
You can still use it with other language's parser to generate other LLVM_IR  

Compiler way:  
1.cd <This Dir>  
2.make  

Run way:  
1.make run FILE=PATH/<YOUR TEST FILE NAMES>  
2.sample: make fun file=./example/test.c  
  [test.c has been already prepared,you can directly run to see what will happened]  
  
Something should be paied attention to:  
1.My makefile still has some bugs.Once I leave the files which are *.o,  
  the second Compiler will go somethin wrong.  :() But I don't know why.  
2.Dir explain:  
  ./obj:objective files,which are compiled but not linked.  
  ./src:source codes  
  ./include:head files  
  ./example:test codes  
  ./bin:LLVM IR && executable binary files  
3.Contact with me:  
  QQ:1025532090  
  WeChat:ltclookatme  
  look forward to learning from you!  


things has been finished:  
1.basic calculation  
2.string type's declaration and calculation  
3.change characters of string.  
4.distinguish quotint and assigning(to avoid the memory mistakes)  
5.produce IR head(OS information) and tail(attribute information)  
6.make sure about memory safety  
7.correctly parameter passing  
8.finish the subscope mechanism  


