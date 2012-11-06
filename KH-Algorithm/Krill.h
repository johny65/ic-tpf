#ifndef KRILL_H
#define KRILL_H
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

typedef vector<double> Pos;

class Krill {
private:
	double dt; ///<diferencial te tiempo (muy importante)
	int dim; ///<dimension del problema
	int id; ///<identificador del Krill sirve solo para saber si dos krilles son diferentes o no
	
	Pos N; ///<Motion induced by other individuals 
	Pos F; ///<Foraging Motion
	Pos D; ///<Physical diffusion
	
	Pos Beta_best; ///<Guarda la mejor posicion historica
	Pos X; ///<Actual position
	
	double dist_sensing; ///<distancia de sensado de cada Krill.
	double wn; ///<inercia para el movimiento inducido por otros individuos
	double wf; ///<inercia para el movimiento forrajero

	
	double prob_cruza; ///< Probabilidad de cruza
	double prob_mutar; ///< Probabilidad de mutacion 
	
	
	
	
public:
	Krill(Pos inicial, int, double);
	~Krill();
	bool operator ==(Krill &B);
	void actualizar_pos(Pos &alpha_i,Pos &Beta_i_food, double &D_coef); ///< alpha y beta vectores directore. D_coef=D_max*(1-I/I_max)
	void cruzar();
	void mutar();
	double distancia(Krill &B);
	double get_dist_sensing();
	Pos &get_beta_best();
	Pos &get_pos();
	int get_id();
	void set_dist_sensing(double);
	void set_beta_best(Pos &);
	void set_prob(double &K);///<Setea las probabilidades de cruza y mutacion que tiene el Krill
	
};

#endif

