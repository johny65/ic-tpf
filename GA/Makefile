GPP=g++
GCC=gcc
FLAGS= -g2 -Wall -O0  -D_DEBUG 
LIBS=  
OBJS=Debug/genetic.o Debug/main.o Debug/func.o Debug/utils.o

all: Debug bin/GA.bin

clean:
	rm -rf ${OBJS} bin/GA.bin

bin/GA.bin: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/genetic.o: genetic.cpp genetic.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/main.o: main.cpp genetic.h func.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/func.o: func.cpp func.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/utils.o: utils.cpp utils.h
	${GPP} ${FLAGS} -c $< -o $@