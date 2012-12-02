#ifndef wait_H
#define wait_H

//wait.h:
//Para pausar por un instante una aplicación y continuar sin intervención
//del usuario.
//
//Uso: wait(ms);
//Espera ms milisegundos y continúa la ejecución.
//
//Código original por André Stein
//(http://steinsoft.net/index.php?site=Programming/Code Snippets/Cpp/no4)

#include <time.h>

float getElapsedTimeInMs()
{
	//Return clock() as ms
	//1 Second = 1000 milliseconds
	return clock()/(CLOCKS_PER_SEC/1000);
}

void wait(int ms)
{
	float goal;
	goal = ms + getElapsedTimeInMs();
	//Do nothing until goal is greater than the
	//current elapsed time
	while(goal >= getElapsedTimeInMs()){};
}

#endif
