#include "herd.h"
#include <limits>

using namespace std;

herd::herd(int cant_k, int dimension, int max,vector<pair<double,double> > rango) {
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
double herd::calcular_dist_sensing(int k){
	double ds=0;
	return ds;
}
void herd::set_graf(bool a){
	this->graf=a;
} 

void herd::Optimizar(){
	/**
	Rutina principal
	*/
	int c=0; //cuenta el numero de iteraciones
	Pos alpha_local, alpha_target, alpha_total; //Para el movimiento inducido por otros individuos
	//Para el movimiento forrajero 
	Pos beta_food, beta_best; double fitness_beta_food, fitness_beta_best;
	int m, p;
	
	while(c<this->max_it){
		calcular_coef(c); //Calcula los coeficiente C_best, C_food y D_diffusion
		
		//1-calculo el mejor y el peor individuo y su fitness asociado
		calc_best_peor(this->mejor,this->peor,this->K_best,this->K_worst);
		//2-calculo la posicion de la comida
		this->food=calc_pos_food();
		
		for(int i=0;i<this->num_krill;i++) { 
			//-a) Calculo la distancia de sensado del i-esimo Krill y calculo alpha_local y alpha_target
			this->M[i].set_dist_sensing(calcular_dist_sensing(i));
			alpha_local=calc_alpha_l(i);
			alpha_target=calc_alpha_t(i);
			alpha_total=sum(alpha_local,alpha_target);
			
			//-b) Calculo las componentes para el foraging motion beta_i
			calc_Xs_Ks(this->M[i].get_pos(),this->food,beta_food,fitness_beta_food);
			fitness_beta_food=this->C_food*fitness_beta_food;
			beta_food=prod_escalar(beta_food,fitness_beta_food);
			//Actualizo beta_best
			calc_Xs_Ks(this->M[i].get_pos(),this->M[i].get_beta_best(),beta_best,fitness_beta_best);
			beta_best=prod_escalar(beta_best,fitness_beta_best);
			this->M[i].set_beta_best(beta_best);
			
			
			///<Actualizo la posicion del i-esimo Krill
			this->M[i].actualizar_pos(alpha_total,beta_food,this->D_diffusion);
		}
		
		c+=1; //siguiente iteracion
	}
	
	
}

void herd::calcular_coef(int iteracion){
	this->C_best=2*(((rand()%100)/100.0)+iteracion/this->max_it);
	this->C_food=2*(1-(iteracion/this->max_it));
	this->D_diffusion=0.01*(1-(iteracion/this->max_it));
	
}

Pos herd::calc_alpha_l(int i){
	/**@param i: indice del Krill del cual se calcula el alpha_local*/
	Pos alfa;
	double a;
	
	for(int j=0;j<this->num_krill;j++) { //lazo hasta el i-esimo krill
		if(distancia(i,j)<this->M[i].get_dist_sensing()){ //si el krill j es vecino de i
			calc_Xs_Ks(this->M[i].get_pos(),this->M[j].get_pos(), alfa, a);
			alfa=sum(alfa,prod_escalar(alfa,a));
		}
		if(j+1==i) j=i+1;
	}
	return alfa;
}

Pos herd::calc_alpha_t(int i){
	Pos alfa;
	double fitness;
	calc_Xs_Ks(this->M[i].get_pos(), this->M[mejor].get_pos(),alfa,fitness);
	alfa=prod_escalar(alfa,this->C_best);
	return alfa;
}



double herd::distancia(int i,int j){
	/**
	*@brief : calcula la distancia entre el krill i y el krill j
	*/
	Pos X;
	X=dif(this->M[j].get_pos(),this->M[i].get_pos());
	return modulo(X);
}



double herd::fitness(Pos X){
	//Funcion del paper Z=X*e^(x^2+y^2);
	double f;
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
		a=fitness(this->M[i].get_pos());
		s+=(1/a);
		food=sum(food,prod_escalar(this->M[i].get_pos(), (1/a)));
	}
	food=prod_escalar(food,s);
	return food;
}
void herd::calc_best_peor(int &mejor, int &peor, double &kmejor, double &kpeor){
	/**
	*@brief funcion que calcula los indices del mejor y peor individuo global
	*@param mejor: indice del mejor individuo
	*@param peor: indice del peor individuo
	*/
	kmejor=-1, kpeor=numeric_limits<double>::max();
	double temp;
	for(int i=0;i<this->dim;i++) { 
		temp=fitness(this->M[i].get_pos());
		if(kmejor<temp){ //Busco el mejor
			kmejor=temp;
			mejor=i;
		}
		if(temp<kpeor){ //busco el peor
			kpeor=temp;
			peor=i;
		}
		
	}
}
void herd::calc_Xs_Ks(Pos &i, Pos &j, Pos &X, double &K){
	/**
	*@brief Calcula las formulas (5) y (6) del paper las retorna en la variables X y K
	*@param i: posicion del i-esimo Krill
	*@param j: posicion del j-esimo Krill
	*@param X: resultado de la ecuacion (5)
	*@param K: resultado de la ecuacion (6);
	*/
	X=dif(j,i);
	normalizar(X);
	K=(fitness(i)-fitness(j))/(this->K_worst - this->K_best);
}
