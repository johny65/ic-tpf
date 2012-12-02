#include <iostream>
#include <vector>
#include "herd.h"

using namespace std;

void Semilla(int cant_k,double Ct ,double N,double V,double D, int id, int cant_it){
	/**
	*@param cant_k: cantidad de individuos;
	*@param rango: rango de busqueda de la solucion (rango.size() = dimension del problema)
	*@param Ct: constante para calcular el delta_t
	*@param N: parametro para el movimiento inducido por otros individuos (N_max)
	*@param V: parametro para el movimiento forrajero 
	*@param D: parametro para difusion aletoria.
	*@param id: id de la funcion a evaluar.
	*@param cant_it: cantidad maxima de iteraciones.
	*/	

	pair<double,double> k;
	vector<pair<double,double> > r;
		k.first = -100; k.second = 100;
			for (int i=0; i<13; ++i){
				r.push_back(k);
			}

	int dimension=r.size();

	//calcular delta_t:
	double dt = 0.0;
	for (int i=0; i<dimension; ++i){
		dt += r[i].second - r[i].first;
	}
	dt *= Ct;
	//cout<<"dt: "<<dt<<endl; cin.get();
	//double dt = Ct;
	//dt=1;
	herd Manada(cant_k, dimension, r, dt, N, V, D);
	Manada.Optimizar(cant_it, id);
}

int main (int argc, char *argv[]) {
	
	//int cant_k, double dt, double N,double V,double D, int id, int cant_it
	Semilla(25, 0.5, 0.02,0.01,0.005,5, 10);
	
	
	
	return 0;
}

