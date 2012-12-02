GPP=g++
GCC=gcc
FLAGS=  -g2 -Wall -O0  -D_DEBUG 
LIBS=  
OBJS=Debug/Network.o Debug/utils.o Debug/Perceptron.o Debug/func.o Debug/genetic.o Debug/main.o 

all: Debug Debug/red-ga.bin

clean:
	rm -rf ${OBJS} Debug/red-ga.bin

Debug/red-ga.bin: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/Network.o: Network.cpp Network.h Perceptron.h GNUplot.h utils.h func.h
	${GPP} ${FLAGS} -c Network.cpp -o $@

Debug/utils.o: utils.cpp GNUplot.h
	${GPP} ${FLAGS} -c utils.cpp -o $@

Debug/Perceptron.o: Perceptron.cpp Perceptron.h GNUplot.h utils.h func.h wait.h
	${GPP} ${FLAGS} -c Perceptron.cpp -o $@

Debug/func.o: func.cpp
	${GPP} ${FLAGS} -c func.cpp -o $@

Debug/genetic.o: genetic.cpp genetic.h GNUplot.h utils.h
	${GPP} ${FLAGS} -c genetic.cpp -o $@

Debug/main.o: main.cpp genetic.h GNUplot.h func.h
	${GPP} ${FLAGS} -c main.cpp -o $@

