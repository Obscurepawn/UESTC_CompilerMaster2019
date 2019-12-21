obj = lex.yy.c lrparser.tab.h lrparser.tab.c 

$(obj):lrlex.l lrparser.y
	flex  lrlex.l
	bison -d lrparser.y
	mv *.h ../include/
