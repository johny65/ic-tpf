#ifndef HERD_H
#define HERD_H
#include <vector>
#include "Krill.h"
using namespace std;

class herd {
private:
	vector<Krill> M; ///<Manada de Krill
	Pos food; ///<Posicion estimada del alimento
	int max_it; ///<Maximo numero de iteraciones
	int dim; ///<dimension del problema a resolver
	int num_krill; ///<Numero de Krill en la manada
	double sensing_dist; ///< distancia para evalual los vecinos
	double fitness();
	
	bool graf; ///<Opcion para graficar
	
	///<Funciones
	void calc_pos_food();
	vector<int> vecinos(Krill &A);
	
public:
	herd(int cant_k, int dimension, int max, vector<pair<double,double> >);
	~herd();
	void set_fitness(); ///<Setea la funcion de fitness a utilizar "ver como hacer esto"
	void set_max_it(int);
	void set_sensing_d(double); ///<Setea la distancia para evaluar los vecinos
	void set_graf(bool); ///<True: si se desea graficar 
	
	void Optimizar(); ///<Rutina principal; resuelve el problema
	
};

#endif

