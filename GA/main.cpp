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

int cant_eval_func = 0;

double ackley(vector<double> &val)
{
	cant_eval_func++;
	
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


double bat1(vector<double> &x)
{
	cant_eval_func++;
	//f(x) = 0.6224 x1 x3 x4 + 1.7781 x2 x3^2 + 3.1661 x1^2 x4 + 19.84 x1^2 x3
	return 0.6224*x[0]*x[2]*x[3] + 1.7781*x[1]*x[2]*x[2] +
		3.1661*x[0]*x[0]*x[3] + 19.84*x[0]*x[0]*x[2];
}

double fitness_bat1(Individuo &ind)
{
	//codificación:
	//4 valores reales, cada uno usa 8 bits para la parte entera
	//y 3 bits para la parte decimal.
	
	const static int N = 4; //dimensión
	const static int BT = 11; //bits totales por valor real
	const static int BE = 8; //bits para la parte entera
	
	vector<double> fenotipo(N);
	for (int i=0; i<N; ++i){
		Cromosoma &c = ind.cromosoma;
		fenotipo[i] = decode(c.begin()+i*BT, c.begin()+i*BT+BT, BE, false);        
	}

	//ver restricciones:
	double &x1 = fenotipo[0];
	double &x2 = fenotipo[1];
	double &x3 = fenotipo[2];
	double &x4 = fenotipo[3];

	double fitnessmalo = numeric_limits<double>::infinity();


	double f = -bat1(fenotipo);//, C = 500;
	
	//f -= C * ( pow(max(0.0, -x1 + 0.0193*x3), 2) + pow(max(0.0, -x2 + 0.00954*x3), 2)
		//+ pow(max(0.0, -M_PI*x3*x3*x4 - (4.0/3.0)*M_PI*pow(x3, 3) + 1296000), 2)
		//+ pow(max(0.0, x4 - 240), 2) );
//
	//f -= C * ( pow(max(0.0, 0.0625 - x1), 2) + pow(max(0.0, x1 - 6.1875), 2) +
		//pow(max(0.0, 0.0625 - x2), 2) + pow(max(0.0, x2 - 6.1875), 2) +
		//pow(max(0.0, 10 - x3), 2) + pow(max(0.0, x3 - 200), 2) + pow(max(0.0, 10 - x4), 2)
		//+ pow(max(0.0, x4 - 200), 2) );

	//return f;

	//return -bat1(fenotipo); //hay que minimizar
	
	if (x1 < 0.0625 || x1 > 6.1875 || x2 < 0.0625 || x2 > 6.1875)
		return fitnessmalo;
//
	if (x3 < 10 || x3 > 200 || x4 < 10 || x4 > 200)
		return fitnessmalo;

	if (-x1 + 0.0193*x3 > 0)
		return fitnessmalo;

	if (-x2 + 0.00954*x3 > 0)
		return fitnessmalo;

	if (-M_PI*x3*x3*x4 - (4.0/3.0)*M_PI*pow(x3, 3) + 1296000 > 0)
		return fitnessmalo;

	if (x4 - 240 > 0)
		return fitnessmalo;
	
	return f;
}

double bat2(vector<double> &x)
{
	cant_eval_func++;
	return (x[2] + 2) * x[1]*x[0]*x[0];
}

double fitness_bat2(Individuo &ind)
{
	//codificación:
	//3 valores reales, cada uno usa 4 bits para la parte entera
	//y 3 bits para la parte decimal.
	
	const static int N = 3; //dimensión
	const static int BT = 7; //bits totales por valor real
	const static int BE = 4; //bits para la parte entera
	
	vector<double> fenotipo(N);
	for (int i=0; i<N; ++i){
		Cromosoma &c = ind.cromosoma;
		fenotipo[i] = decode(c.begin()+i*BT, c.begin()+i*BT+BT, BE, false);        
	}

	//ver restricciones:
	double &x1 = fenotipo[0];
	double &x2 = fenotipo[1];
	double &x3 = fenotipo[2];

	if (x1 < 0.05 || x1 > 1 || x2 < 0.25 || x2 > 1.3 || x3 < 2 || x3 > 15)
		return numeric_limits<double>::infinity();

	if (1 - pow(x2, 3)*x3/(71785*pow(x1, 4)) > 0)
		return numeric_limits<double>::infinity();

	if ((4*pow(x2, 2) - x1*x2)/(12566*(x2*pow(x1, 3) - pow(x1, 4))) +
		1.0/(5108*pow(x1, 2)) - 1 > 0)
		return numeric_limits<double>::infinity();

	if (1 - 140.45*x1/(pow(x2, 2)*x3) > 0)
		return numeric_limits<double>::infinity();

	if ((x1 + x2)/1.5 - 1 > 0)
		return numeric_limits<double>::infinity();

	return bat2(fenotipo);
}


int main(){

	const static int maxiter = 1000;

	//Ackley:
	
	//longitud del cromosoma: 20*9 = 180
	//GA genetico(15, 180);
	//genetico.setFuncionFitness(fitness_ackley);
	//genetico.inicializar_poblacion(15, 180);
	//genetico.setToleranciaCorte(1e-3);


	//longitud del cromosoma: 4*11 = 44
	int n = 250, l = 44;
	GA genetico(n, l);
	genetico.setFuncionFitness(fitness_bat1);
	genetico.inicializar_poblacion(n, l);
	cant_eval_func = 0;


	//longitud del cromosoma: 3*7 = 21
	//int n = 100, l = 21;
	//GA genetico(n, l);
	//genetico.setFuncionFitness(fitness_bat2);
	//genetico.inicializar_poblacion(n, l);


	
	
	genetico.setMaximasIteraciones(maxiter);
	genetico.Elitismo(1);

	Individuo ii; ii.cromosoma = genetico.Ejecutar();

	//double r = -fitness_ackley(ii);
	double r = -fitness_bat1(ii);

	cout<<"Solución: "<<r<<endl;
	cout<<"Cantidad de evaluaciones de funciones: "<<cant_eval_func<<endl;
	//cin.get();
	return 0;
}
