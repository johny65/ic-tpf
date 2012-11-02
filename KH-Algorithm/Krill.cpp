#include "Krill.h"
#include "func.h"

using namespace std;

Krill::Krill(Pos inicial, int dni) {
	this->X=inicial;
	this->dim=this->X.size();
	this->id=dni;
	
}

Krill::~Krill() {
	
}

bool Krill::operator ==(Krill &B){
	if(this->id==B.get_id()) return true;
	else return false;
}

void Krill::cruzar(){
	
}
void Krill::mutar(){
	
}

Pos &Krill::get_pos(){
	return this->X;
}
int Krill::get_id(){
	return this->id;
}

double Krill::distancia(Krill &B){
	double d=0;
	Pos KB=B.get_pos(); ///< Posicion del Krill B
	for(int i=0;i<this->dim;i++) { 
		d+=pow(this->X[i]-KB[i],2);
	}
	return d;
}

void Krill::actualizar_pos(Pos &alpha_i,Pos &Beta_i_food, double &D_coef){
	
	///<Genero el vector direccion aletorio gamma y lo normalizo
	for(int i=0;i<this->dim;i++) { 
		this->D.push_back((rand()%100)/100.0);
	}
	normalizar(this->D);
	this->D=prod_escalar(this->D,D_coef);
	
	this->N=sum(alpha_i,prod_escalar(this->N,this->wn));
	
	Pos Beta_i=sum(this->Beta_best,Beta_i_food);
	this->F=sum(Beta_i,prod_escalar(this->F,this->wf));
	
	//Actualizo la posicion
	this->X=sum(this->X,prod_escalar(sum(this->N,sum(this->F,this->D)),this->dt));
	
}

void Krill::set_dist_sensing(double d){
	this->dist_sensing=d;
}

double Krill::get_dist_sensing(){
	return this->dist_sensing;
}

Pos& Krill::get_beta_best(){
	return this->Beta_best;
}

void Krill::set_beta_best(Pos &b){
	this->Beta_best=b;
}
