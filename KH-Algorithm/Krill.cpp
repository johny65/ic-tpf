#include "Krill.h"
#include "func.h"

#include <iostream>
using namespace std;

Krill::Krill(Pos inicial, int dni,double delta_t) {
	this->X=inicial;
	this->dim=this->X.size();
	this->id=dni;
	this->wn=(rand()%100)/100.0;
	this->wf=(rand()%100)/100.0;
	this->dt=delta_t;
	
	//Inicializo la mejor posicion lograda como la posicion actual
	this->Beta_best=this->X;
	
	//Inicializo N,F y D como los vectores 0
	for(int i=0;i<this->dim;i++) { 
		this->N.push_back(0);
		this->F.push_back(0);
		this->D.push_back(0);
	}

	
}

Krill::~Krill() {
	
}

bool Krill::operator ==(Krill &B){
	if(this->id==B.get_id()) return true;
	else return false;
}

/**
 * Realiza la cruza con el krill que le viene (Fórmula 20).
 */
void Krill::cruzar(Krill &krillin){
	for (int i=0; i<this->dim; ++i){
		if (rand()/RAND_MAX < this->prob_cruza){
			this->X[i] = krillin.get_pos()[i];
		}
	}
}

/**
 * Realiza la mutación basada en DE (Fórmula 22).
 * 
 * Se eligen 2 individuos al azar y se calcula el vector de prueba u(t)
 * mediante un vector objetivo X_gbes. Este vector (individuo) objetivo se
 * puede seleccionar de varias maneras. Acá se usa la estrategia "DE/best/1/z"
 * (el objetivo es el mejor individuo de la población actual) (pág. 244 del
 * libro de Engelbrecht 2º Edición).
 */
void Krill::mutar(Krill &gbest, Krill &A, Krill &B){

	double mu = 0.5; /** < (o beta según Engelbrecht) Factor de escalado entre
                       * (0,inf). Debería ser un atributo del krill o de la
                       * manada toda, para todos el mismo. \todo: ver eso. */
	
	for (int i=0; i<this->dim; ++i){
		if (rand()/RAND_MAX < this->prob_mutar){
			this->X[i] = gbest.get_pos()[i] + mu * (A.get_pos()[i] -
				B.get_pos()[i]);
		}
	}
	
}

void Krill::set_prob(double &K){
	this->prob_cruza=0.2*K;
	this->prob_mutar=0.05/K;
	cout<<"Pc: "<<prob_cruza<<"\nPm: "<<prob_mutar<<endl; //<<<< SE HACEN INF
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
	///< to do: falta considera N_max, y Vf
	///<Genero el vector direccion aletorio gamma y lo normalizo
	for(int i=0;i<this->dim;i++) { 
		this->D[i]=((rand()%100)/100.0);
	}
	normalizar(this->D);
	this->D=prod_escalar(this->D,D_coef);
	
	Pos temp=prod_escalar(this->N,this->wn);

	this->N=sum(alpha_i,temp);

	
	//Pos Beta_i=sum(this->Beta_best,Beta_i_food);
	
	
	this->F=sum(sum(this->Beta_best,Beta_i_food),prod_escalar(this->F,this->wf));

	//Actualizo la posicion
	this->X=sum(this->X,prod_escalar(sum(this->N,sum(this->F,this->D)),this->dt));
	//mostrar(this->X);
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
