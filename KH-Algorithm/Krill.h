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
	double wn;///<inertia weight
	
	Pos F; ///<Foraging Motion
	double wf;///<inertia weight
	
	Pos D; ///<Physical diffusion
	
	
	Pos X; ///<Actual position
	
	
	
	
public:
	Krill(Pos inicial, int);
	~Krill();
	bool operator ==(Krill &B);
	void actualizar_pos(Pos &alpha_i,Pos &Beta_i, double &D_coef); ///< alpha y beta vectores directore. D_coef=D_max*(1-I/I_max)
	void cruzar();
	void mutar();
	double distancia(Krill &B);
	Pos get_pos();
	int get_id();
	
};

#endif

