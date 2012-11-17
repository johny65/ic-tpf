#include "Particula.h"
#include <cstdlib>
#include "func.h"
#include <vector>
#include <iostream>
using namespace std;
void mostrar(vector<double> x){
	for(size_t i=0;i<x.size();i++) { 
		cout<<x[i]<<", ";
	}
	cout<<endl;
}
Particula::Particula(double ac1,double ac2,vector<pair<double,double> > r,int v0){
	/**
	* @param ac1: aceleracion c1;
	* @param ac2: aceleracion c2;
	* @param rango: vector que guarda el rango para cada variable i.e. para x: (x.first, x.second). para y: (y.first, y.second), etc
	* @param v0: para generar el rango de inciacializacion de la velocidad v~U(0,vo) v0 se pasa como un numero entre 0 y 100 y despues se lo pasa al rango [0 1]
	*/
	//incializo c1 y c2
	this->c1=ac1;
	this->c2=ac2;
	this->rango=r;
	
//	//inicializo r1 y r2
//	r1=(0+rand()%100)/100.0;
//	r2=(0+rand()%100)/100.0;
	
	//Inicializo las posiciones aletoriamente
	int dim=rango.size(); ///<dimension del problema a resolver
	
	//inicializo las posiciones en el rango correspondiente
	
	for(int i=0;i<dim;i++) { 
		int sep=abs(rango[i].second-rango[i].first);
		double p=rango[i].first+rand()%(sep);
//		this->Pos.push_back(400+rand()%5);
		this->Pos.push_back(p);
	}
	
	//incializacion de la velocidad
	if(v0==0){//inicializo la velocidad igual a la posicion inicial
		for(int i=0;i<dim;i++) { 
			this->Vel.push_back(0);
		}
	}
	else{//incializo la velocidad con un numero aletorio entre 0 y v0
		for(int i=0;i<dim;i++) { 
			this->Vel.push_back((1+rand()%v0)/100.0);
		}
	}
	
	//Inicializo la mejor pos personal = a la posicion inicial
	this->best_pers=this->Pos;
	
	
}

Particula::~Particula() {
	
}

void Particula::set_r(vector<double> &a1, vector<double> &a2){
	this->r1=a1;
	this->r2=a2;
}


void Particula::actualizar_vel(vector<double> best_local){
//	this->r1=(rand()%100)/100.0;
//	this->r2=(rand()%100)/100.0;
	vector<double> dml=dif(this->best_pers,this->Pos);
	vector<double> dmg=dif(best_local,this->Pos);
	//double coef1=c1*r1, coef2=c2*r2;
//	cout<<"muestro la componente individual "<<endl; mostrar(dml);
//	cout<<"muestro la componente grupal "<<endl; mostrar(dmg);
	
	//this->Vel=sum(this->Vel,sum(prod_escalar(dml,coef1),prod_escalar(dmg,coef2)));
	for(size_t i=0;i<Vel.size();i++) { 
		Vel[i]=0.9*Vel[i]+c1*this->r1[i]*(this->best_pers[i]-this->Pos[i])+c2*this->r2[i]*(best_local[i]-this->Pos[i]);
	}
//	cout<<"Muestro como se actualiza la velocidad "<<endl;
//	mostrar(this->Vel);
	
} 

void Particula::actualizar_pos(){
	vector<double> P_viejo=this->Pos;
	for(size_t i=0;i<this->Pos.size();i++) { 
		Pos[i]+=Vel[i];
	}
	//Evaluo los rangos si se va de rango dejo el peso viejo
	for(int i=0;i<this->rango.size();i++) { 
		if((Pos[i]<this->rango[i].first)||(Pos[i]>this->rango[i].second)){
			this->Pos=P_viejo;
			break;
		}
	}
	
}
void Particula::actualizar_best_pers(){
	this->best_pers=this->Pos;
}

vector<double> Particula::get_Pos(){
	return this->Pos;
}

vector<double>Particula::get_best_pers(){
	return this->best_pers;
}



