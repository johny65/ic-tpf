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
	switch(id){
		case 1:{
			k.first=-512;
			k.second=512;
			r.push_back(k);
			break;
		}
		case 2:{
			k.first=0;
			k.second=20;
			r.push_back(k);
			break;
		}
		case 3:{
			k.first=-100;
			k.second=100;
			r.push_back(k); r.push_back(k);
			break;
		}
		case 4:{
			k.first=-5;
			k.second=5;
			r.push_back(k); r.push_back(k); r.push_back(k); r.push_back(k);
			break;
		}
		case 5: {
			k.first = -32; k.second = 32;
			for (int i=0; i<20; ++i){
				r.push_back(k);
			}
			break;
		}
		case 6: { //vessel
			//r.push_back(make_pair(0.0, 256.0));
			//r.push_back(make_pair(0.0, 256.0));
			//r.push_back(make_pair(0.0, 256.0));
			//r.push_back(make_pair(0.0, 256.0));
			r.push_back(make_pair(0.0625, 6.1875));
			r.push_back(make_pair(0.0625, 6.1875));
			r.push_back(make_pair(10, 200));
			r.push_back(make_pair(10, 200));
		}
	}
	int dimension=r.size();

	//calcular delta_t:
	double dt = 0.0;
	for (int i=0; i<dimension; ++i){
		dt += r[i].second - r[i].first;
	}
	dt *= Ct;
	//dt=1;
	//cout<<"dt: "<<dt<<endl; cin.get();
	//double dt = Ct;
	
	herd Manada(cant_k, dimension, r, dt, N, V, D, id);
	Manada.Optimizar(cant_it, id);
}

int main (int argc, char *argv[]) {
	
	//int cant_k, double dt, double N,double V,double D, int id, int cant_it
	Semilla(250, 0.5, 0.02,0.01,0.005, 6, 1000);
	
	return 0;
}

