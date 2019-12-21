CC = gcc

DIR_SRC := ./src
DIR_OBJ := ./obj
DIR_BIN := ./bin
DIR_INC := ./include

vpath %.c src
vpath %.h include
vpath %.o obj
vpath %.exe %.out bin

FILE = 
SRC := $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir $(SRC)))
parser =  lrparser.tab
lex = lex.yy

TARGET = genllvm.out

BIN_TARGET = ${DIR_BIN}/${TARGET}

CFLAGS = -g -O2 -I${DIR_INC} 

${BIN_TARGET}:  ${OBJ}  ${DIR_OBJ}/${parser}.o  ${DIR_OBJ}/${lex}.o
	${CC} ${CFLAGS} ${OBJ} ${DIR_OBJ}/${parser}.o  ${DIR_OBJ}/${lex}.o -o $@
	$(RM) ${DIR_OBJ}/*.o ${DIR_INC}/*.tab.h ${DIR_SRC}/*.tab.c ${DIR_SRC}/*.yy.c ${DIR_SRC}/*.tab.h *.o 

${OBJ}: ${SRC}  ${DIR_SRC}/${parser}.c  ${DIR_SRC}/${lex}.c  
	${CC} ${CFLAGS} -c $?
	mv *.o ${DIR_OBJ}/

${DIR_SRC}/${parser}.c  ${DIR_SRC}/${lex}.c:  ${DIR_SRC}/lrparser.y  ${DIR_SRC}/lrlex.l
	$(MAKE) -C ${DIR_SRC}

clean:
	$(RM) ${DIR_OBJ}/*.o ${DIR_INC}/*.tab.h ${DIR_SRC}/*.tab.c ${DIR_SRC}/*.yy.c ${DIR_SRC}/*.tab.h *.o 

run:
	${BIN_TARGET}  ${FILE}

 
