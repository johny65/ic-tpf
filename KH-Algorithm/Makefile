GPP=g++
GCC=gcc
FLAGS=  -g2 -Wall -O0  -D_DEBUG 
LIBS=  
OBJS=Debug/main.o Debug/Krill.o Debug/herd.o Debug/func.o Debug/utils.o 

all: Debug Debug/krill.bin

clean:
	rm -rf ${OBJS} Debug/krill.bin

Debug/krill.bin: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/main.o: main.cpp herd.h Krill.h func.h
	${GPP} ${FLAGS} -c main.cpp -o $@

Debug/Krill.o: Krill.cpp Krill.h func.h
	${GPP} ${FLAGS} -c Krill.cpp -o $@

Debug/herd.o: herd.cpp herd.h Krill.h func.h
	${GPP} ${FLAGS} -c herd.cpp -o $@

Debug/func.o: func.cpp func.h Krill.h
	${GPP} ${FLAGS} -c func.cpp -o $@

Debug/utils.o: utils.cpp utils.h
	${GPP} ${FLAGS} -c utils.cpp -o $@

