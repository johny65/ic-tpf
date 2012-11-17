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

using namespace std;

double ackley(vector<double> &val)
{
    int n = val.size();
    double s1 = 0.0, s2 = 0.0;
    for (int i=0; i<n; ++i){
		s1 += val[i]*val[i];
		s2 += cos(2*M_PI*val[i]);
    }
	double r= -20*exp(-0.2*sqrt(s1/n))-exp(s2/n)+20+exp(1);
	return r;
}

double fitness_ackley(Individuo &ind)
{
    //codificación:
    //20 valores reales, cada uno usa 6 bits para la parte entera (de -32 a 32)
    //y 3 bits para la parte decimal.
    
    const static int N = 20; //dimensión
    const static int BT = 9; //bits totales por valor real
    const static int BE = 6; //bits para la parte entera
    
    vector<double> fenotipo(N);
    for (int i=0; i<N; ++i){
        Cromosoma &c = ind.cromosoma;
        fenotipo[i] = decode(c.begin()+i*BT, c.begin()+i*BT+BT, BE, true);
    }

    return -ackley(fenotipo);
}

double kowalik(vector<double> &val)
{
	double r = 0.0;
	double a[] = {0.1957, 0.1947, 0.1735, 0.16, 0.0844, 0.0627, 0.0456,
        0.0342, 0.0323, 0.0235, 0.0246};
	double b[] = {0.25, 0.5, 1, 2, 4, 6, 8, 10, 12, 14, 16};
	
	for(int i=0; i<11; ++i){
		double aux = a[i]-(val[0]*(1+val[1]*b[i]))/(1+val[2]*b[i]+val[3]*b[i]);
		r += (aux*aux);
	}
	return r;
}

double fitness_kowalik(Individuo &ind)
{
    //codificación:
    //4 valores reales, cada uno usa 4 bits para la parte entera (de -8 a 8)
    //y 3 bits para la parte decimal.
    //El rango de la función es de -5 a 5, se penalizan los inválidos
    
    const static int N = 4; //dimensión
    const static int BT = 7; //bits totales por valor real
    const static int BE = 4; //bits para la parte entera
    
    vector<double> fenotipo(N);
    for (int i=0; i<N; ++i){
        Cromosoma &c = ind.cromosoma;
        fenotipo[i] = decode(c.begin()+i*BT, c.begin()+i*BT+BT, BE, true);
        if (fabs(fenotipo[i]) >= 5) //restricción del rango
            return -1000; //numeric_limits<double>::max();
    }

    double r = -kowalik(fenotipo);
    return isinf(r) ? -1000 : r;
}


int main(){

    const static int maxiter = 1000;

    //Ackley:
    
    //longitud del cromosoma: 20*9 = 180
    GA genetico(15, 180);
    genetico.setFuncionFitness(fitness_ackley);
    genetico.setToleranciaCorte(1e-3);

    //Kowalik:
    
    //longitud del cromosoma: 4*7 = 28
    //GA genetico(10000, 28);
    //genetico.setFuncionFitness(fitness_kowalik);
    //genetico.setToleranciaCorte(1e-3);

    
    genetico.setMaximasIteraciones(maxiter);
    genetico.Elitismo(1);

    Individuo ii; ii.cromosoma = genetico.Ejecutar();

    double r = -fitness_ackley(ii);
    //double r = -fitness_kowalik(ii);

    cout<<"Solución: "<<r<<endl;
    cin.get();
    return 0;
}
