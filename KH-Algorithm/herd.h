#ifndef HERD_H
#define HERD_H
#include <vector>
#include <cstdlib>
#include "Krill.h"
#include "herd.h"
#include "func.h"




using namespace std;

class herd {
private:
	vector<Krill> M; ///<Manada de Krill
	Pos food; ///<Posicion estimada del alimento
	int max_it; ///<Maximo numero de iteraciones
	int dim; ///<dimension del problema a resolver
	int num_krill; ///<Numero de Krill en la manada
	
	///< Variables necesarias para el calculo del movimiento inducido por otros individuos.
	double K_best; ///< Mejor fitness 
	double K_worst; ///< Peor fitness
	
	
	double sensing_dist; ///< distancia para evalual los vecinos
	double fitness(Krill &A);
	
	bool graf; ///<Opcion para graficar
	
	///<Funciones
	Pos calc_pos_food();
	vector<int> vecinos(Krill &A);
	int calc_best(); ///<devuelve el indice del mejor individuo dentro de M
	
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

