OBJS = Debug/Particula.o Debug/Swarm.o Debug/func.o Debug/main.o Debug/utils.o
FLAGS = -Wall
LIBS=

all: Debug Debug/pso.bin

Debug/pso.bin: ${OBJS}
	g++ ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/func.o: func.cpp func.h GNUplot.h utils.h Particula.h
	g++ -c $< -o $@

Debug/main.o: main.cpp Swarm.h Particula.h GNUplot.h
	g++ -c $< -o $@

Debug/Particula.o: Particula.cpp Particula.h func.h
	g++ -c $< -o $@

Debug/Swarm.o: Swarm.cpp Swarm.h Particula.h GNUplot.h utils.h func.h
	g++ -c $< -o $@

Debug/utils.o: utils.cpp utils.h Particula.h
	g++ -c $< -o $@
