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
	
	double C_best, C_food, D_diffusion; ///< Coeficientes
	
	double fitness(Pos X);
	double K_best, K_worst; ///<Mejor fitness y peor fitness en cada iteracion
	int mejor, peor; ///<indices del mejor y el peor
	bool graf; ///<Opcion para graficar

	
	///<Funciones
	void calc_pos_food();
	vector<int> vecinos(Krill &A);
	void calc_best_peor(int &, int &,double &, double &); ///<devuelve el indice del mejor y peor individuo dentro de la Manada
	void calc_best_food(int &);
	void calc_Xs_Ks(Pos &i, Pos &j, Pos &X, double &K);
	double calcular_dist_sensing(int);
	void calcular_coef(int);
	Pos calc_alpha_l(int);
	Pos calc_alpha_t(int);
	double distancia(int i,int j);
	
	
public:
	herd(int cant_k, int dimension, int max, vector<pair<double,double> >, double delta_t);
	~herd();
	void set_fitness(); ///<Setea la funcion de fitness a utilizar "ver como hacer esto"
	void set_max_it(int);
//	void set_sensing_d(double); ///<Setea la distancia para evaluar los vecinos
	void set_graf(bool); ///<True: si se desea graficar 
	void Optimizar(); ///<Rutina principal; resuelve el problema
	void mostrar_posiciones();
	void mostrar_vector(Pos &v);
};

#endif

