#ifndef SWARM_H
#define SWARM_H

#include <vector>
#include "Particula.h"
#include "GNUplot.h"
#include <set>
using namespace std;

class Swarm {
private:
	vector<Particula>  Enjambre; ///<vector de conjunto de particulas para modelar las vecindades.
	vector<int> bestxvec; ///<vector que guarda el mejor por cada vecindario
	vector<double> func_obj; ///<vector que guarda todos los fitness 
	vector<set<int> > Vecindad;
	vector<pair<double,double> > rango;
	void mejores_de_vecindad(int id);
	void graficar(int id);
	GNUplot plotter;
	void mejores_pos_vecindad(int);
	double evaluar_rad_norm();
public:
	Swarm(int ,int ,double ,double ,vector<pair<double,double> > , int , int);
	~Swarm();
	double fitness(int, vector<double>);
	void Volar(int,int,bool); ///<rutina principal del programa
	void mostrar_posiciones(int);
	void mostrar_mejor_vecindad(int );
};

#endif

