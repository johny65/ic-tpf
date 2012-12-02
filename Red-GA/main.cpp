#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>
#include "genetic.h"
#include "func.h"
#include "Network.h"

using namespace std;

int N; //dimensión (número total de pesos en la red)
int L; //longitud del cromosoma (N * BT)
const static int BT = 5; //bits totales por valor real
const static int BE = 5; //bits para la parte entera
Network Red;

double fitness_red(Individuo &ind)
{
	//codificación:
	//N valores reales, cada uno usa 5 bits para la parte entera (de -16 a 16)
	//y 3 bits para la parte decimal.
	
	vector<double> fenotipo(N);
	for (int i=0; i<N; ++i){
		Cromosoma &c = ind.cromosoma;
		fenotipo[i] = decode(c.begin()+i*BT, c.begin()+i*BT+BT, BE, true);
	}
	
	Red.setear_pesos(fenotipo, N);
	double r = Red.probar("clouds.csv");
	return r;
}


/**
 * Calcula la cantidad total de pesos en la red.
 * @param arq Arquitectura.
 * @param entradas Cantidad de entradas, sin contar el sesgo.
 */
void calcular_constantes(vector<int> &arq, int entradas)
{
	int s = (entradas + 1) * arq[0];
	for (size_t i=1; i<arq.size(); ++i){
		s += (arq[i-1] + 1) * arq[i];
	}
	N = s;
	L = N * BT;
}


int main(){

	const static int maxiter = 100000;

	//Red neuronal:
	int aa[] = {10, 10, 1};
	vector<int> arq(aa, aa+3);
	Red.setear_arquitectura(arq);
	calcular_constantes(arq, 2); //clouds.csv 2 entradas

	GA genetico(25, L);
	genetico.setFuncionFitness(fitness_red);

	genetico.setMaximasIteraciones(maxiter);
	genetico.Elitismo(1);

	Individuo ii; ii.cromosoma = genetico.Ejecutar();

	//double r = -fitness_ackley(ii);
	double r = fitness_red(ii);

	cout<<"Solución: "<<r<<endl;
	//cin.get();
	return 0;
}
