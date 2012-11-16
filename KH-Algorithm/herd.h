#ifndef HERD_H
#define HERD_H
#include <vector>
#include <cstdlib>
#include "Krill.h"
#include "herd.h"
#include "func.h"

#include "GNUplot.h"
using namespace std;

class herd {
private:
	vector<Krill> M; ///<Manada de Krill
	Pos food; ///<Posicion estimada del alimento
	int dim; ///<dimension del problema a resolver
	int num_krill; ///<Numero de Krill en la manada
	int max_it;
	double C_best, C_food, D_diffusion; ///< Coeficientes
	
	double fitness(Pos X,int id);
	double K_best, K_worst; ///<Mejor fitness y peor fitness en cada iteracion
	int mejor, peor; ///<indices del mejor y el peor
	bool graf; ///<Opcion para graficar
	
	vector<double> func_obj; ///<vector que guarda el fitness de cada Krill

	GNUplot plotter;
	
	///<Funciones
	void calc_pos_food();
	vector<int> vecinos(Krill &A);
	void calc_best_peor(int &, int &,double &, double &); ///<devuelve el indice del mejor y peor individuo dentro de la Manada
	void calc_best_food(int &);
	void calc_Xs_Ks(int &i, int &j, Pos &X, double &K); ///<
	void calc_Xs_Ks_vector(int &i, Pos &j, Pos &X, double &K); ///< Solo para food
	double calcular_dist_sensing(int);
	void calcular_coef(int);
	Pos calc_alpha_l(int);
	Pos calc_alpha_t(int);
	double distancia(int i,int j);
	void calcular_fitness(); ///<calcula todos los fitness 
	int id;///< id de las funciones de fitness
	///<Para el control de graficos y datos
	bool grafica;
	
	
public:
	herd(int cant_k, int dimension, vector<pair<double,double> >, double delta_t, double, double, double);
	~herd();
	void set_fitness(); ///<Setea la funcion de fitness a utilizar "ver como hacer esto"
	void set_max_it(int);
//	void set_sensing_d(double); ///<Setea la distancia para evaluar los vecinos
	void set_graf(bool); ///<True: si se desea graficar 
	void Optimizar(int,int ); ///<Rutina principal; resuelve el problema
	void mostrar_posiciones();
	void mostrar_vector(Pos &v);
	void set_grafica(bool);
	void graficar(bool); ///<rutina de graficacion
};

#endif

