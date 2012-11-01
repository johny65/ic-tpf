#include "herd.h"

using namespace std;

herd::herd(int cant_k, int dimension, int max,vector<pair<double,double> > rango) : sensing_dist(10){
	this->dim=dimension;
	this->max_it=max;
	this->num_krill=cant_k;
	//Inicializo la manada
	for(int i=0;i<this->num_krill;i++) { 
		
		Pos Ki; //Posicion para el Krill ith
		//genero la posicion aletoriamente en el rango del problema
		for(int j=0;j<this->dim;j++) { 
			Ki.push_back(rango[j].first+rand()%((int) rango[j].second)); //genero un numero aletorio entre las coordenadas limite del problema
		}
		Krill K(Ki,i);
		this->M.push_back(K);
	}
}

herd::~herd() {
	
}

void herd::set_fitness(){
	
}

void herd::set_max_it(int m){
	this->max_it=m;
}
void herd::set_sensing_d(double d){
	this->sensing_dist=d;
} 
void herd::set_graf(bool a){
	this->graf=a;
} 

void herd::Optimizar(){
	
}
vector<int> herd::vecinos(Krill &A){
	/**
	@brief funcion que a partir de un Krill devuelve los vecinos del mismo
	@param A Krill del cual se quieren obtener la lista de vecinos
	@return lista de indices de los vecinos del Krill A
	*/
	vector<int> indices;
	double a;
	for(int i=0;i<this->num_krill;i++) { 
		a=A.distancia(this->M[i])/(5*this->num_krill);
		if(a<pow(this->sensing_dist,2)){
			indices.push_back(i);
		}
	}
	return indices;
}


double herd::fitness(Krill &A){
	//Funcion del paper Z=X*e^(x^2+y^2);
	double f;
	Pos X=A.get_pos();
	f=X.at(0)*exp(pow(X.at(0),2)+pow(X.at(1),2));
	return f;
}

Pos herd::calc_pos_food(){
	/**
	@brief Funcion que estima la posicion de la comida
	*/
	Pos food;
	double s=0;//suma de todos los fitness
	double a; //fitness actual;
	for(int i=0;i<this->num_krill;i++) { 
		//sumar todos los fitness
		a=fitness(this->M[i]);
		s+=a;
		food=sum(food,prod_escalar(this->M[i].get_pos(), (1/a)));
	}
	food=prod_escalar(food,(1/s));
	return food;
}
