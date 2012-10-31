#ifndef KRILL_H
#define KRILL_H
#include <vector>
using namespace std;

typedef vector<double> Pos;

class Krill {
private:
	double dt; ///<diferencial te tiempo (muy importante)
	int dim; ///<dimension del problema
	int id; ///<identificador del Krill sirve solo para saber si dos krilles son diferentes o no
	
	Pos N; ///<Motion induced by other individuals 
	Pos alpha_l; ///<alpha local
	Pos alpha_t; ///<alpha target
	double w;///<inertia weight
	
	Pos F; ///<Foraging Motion
	double Beta_food; ///<
	double Beta_best; ///<
	double wf;///<inertia weight
	
	Pos D; ///<Physical diffusion
	
	
	Pos X; ///<Actual position
	
	
	
	
public:
	Krill(Pos inicial, int);
	~Krill();
	bool operator ==(Krill &B);
	void update_pos();
	void cruzar();
	void mutar();
	double distancia(Krill &B);
	Pos get_pos();
	int get_id();
	
};

#endif

