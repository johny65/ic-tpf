#ifndef PARTICULA_H
#define PARTICULA_H
#include <vector>

using namespace std;

class Particula {
private:
	vector<double> Pos; ///<guarda la posicion de la Particula
	vector<double> Vel; ///<guarda la velocidad de la Particula
	vector<double> best_pers; ///<guarda la mejor posicion personal;
	vector<pair<double,double> > rango;
	double c1,c2; ///<aceleraciones para las dos componentes de velocidad
	vector<double> r1,r2;///<numeros aletorios para la act de la velocidad
	double fitness;
	
public:
	Particula(double ,double ,vector<pair<double,double> > ,int ); ///< Aqui se incializa la velocidad,se fijan c1 y c2, rango guarda los rangos de busqueda para cada variable x,y,z...etc
	~Particula();
	void actualizar_vel(vector<double> ); ///<best_local es la mejor posicion en la vecindad(lbest) o global (gbest)
	void actualizar_pos();
	void actualizar_best_pers();
	void set_r(vector<double> &, vector<double> &);
	vector<double> get_Pos();
	vector<double> get_best_pers();

};

#endif

