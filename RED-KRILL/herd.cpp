#include <limits>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include "utils.h"
#include "wait.h"
#include "herd.h"

using namespace std;

herd::herd(int cant_k, int dimension, vector<pair<double,double> > rango,double delta_t,double N,double V,double D): w(0.9), grafica(true) {
	//Inicializo la semilla
	srand(time(NULL));
	
	this->rango = rango;
	this->dim=dimension;
	this->num_krill=cant_k;
	
	//inicializo la posicion de la comida como el vector 0;
	for(int i=0;i<this->dim;i++) { 
		this->food.push_back(0);
	}
	
	//Inicializo la manada
	for(int i=0;i<this->num_krill;i++) { 
		
		Pos Ki; //Posicion para el Krill ith
		//genero la posicion aletoriamente en el rango del problema
		for(int j=0;j<this->dim;j++) { 
			int a=(int) rango[j].second-rango[j].first;
			Ki.push_back((rango[j].first+rand()%a)); //genero un numero aletorio entre las coordenadas limite del problema
		}
		Krill K(rango, Ki, i, delta_t, N, V, D);
		this->M.push_back(K);
		this->func_obj.push_back(0); ///<inicializo el vector que guardara los fitness;
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
	for(int i=0;i<this->num_krill;i++) { 
		if(i==k) continue;
		ds+=distancia(i,k);
	}
	
	return (ds/(5*this->num_krill));
}
void herd::set_graf(bool a){
	this->graf=a;
} 

void herd::Optimizar(int m, int id){
	/**
	Rutina principal
	*/

	/* guarda los mejores fitness: */
	vector<double> v_fitness_mejor;
	/* -----------------------------*/
	
	//Seteo la arquitectura de red
	vector<int> arq;
	arq.push_back(10); arq.push_back(10); arq.push_back(1);//arq.push_back(1);
	Red.setear_arquitectura(arq);
	
	this->max_it=m;
	this->id = id;
	int c=0; //cuenta el numero de iteraciones
	Pos alpha_local, alpha_target, alpha_total; //Para el movimiento inducido por otros individuos
	//Para el movimiento forrajero 
	Pos beta_food, beta_best; 
	double fitness_beta_food, fitness_beta_best;
	double K_CM; // K_CM: contante K de cruza y mutacion
	
	while(c<this->max_it){
		
		cout<<"Iteracion "<<c<<endl<<"---------------------------------"<<endl;
		//Calculo todos los fitness
		for(int i=0;i<this->num_krill;i++) { 
			this->func_obj[i]=fitness(this->M[i].get_pos(), id);
			//cout<<func_obj[i]<<endl;
		}
		v_fitness_mejor.push_back(*max_element(this->func_obj.begin(), this->func_obj.end()));
		cout<<v_fitness_mejor.back()<<endl;
		if (condicion_corte(v_fitness_mejor.back())){
			cout<<"Cortó en la iteración "<<c<<" - Solución: "<<
				v_fitness_mejor.back()<<endl;
			break;
		}
		
		//Calculo las distancia de sensado de cada krill;
		for(int i=0;i<this->num_krill;i++) {  
			this->M[i].set_dist_sensing(calcular_dist_sensing(i));
		}
		
		calcular_coef(c); //Calcula los coeficiente C_best, C_food y D_diffusion para la iteracion actual;
		calc_pos_food(); //Calculo la posicion de la comida
		
		//calculo el mejor y el peor individuo y su fitness asociado
		calc_best_peor(this->mejor,this->peor,this->K_best,this->K_worst); 
		
		
		//cout<<"Posicion de la comida ";	mostrar_vector(this->food);
		//mostrar_posiciones(); //muestro las posiciones de los Krill
//		cout<<"muestro el vector de fitness "<<endl; mostrar_vector(this->func_obj); 
		
		//cout<<"el mejor esta en la posicion "<<this->mejor<<" su fitness es "<<this->K_best<<endl;
		//cout<<"el peor esta en la posicion "<<this->peor<<" su fitness es "<<this->K_worst<<endl<<endl;
		
		if(this->grafica){
			graficar(true);
		}
		
		for(int i=0;i<this->num_krill;i++) { 
			
			//cout<<"Para el Krill "<<i<<endl<<"---------------------------------"<<endl<<endl;
			//-a) Calculo la distancia de sensado del i-esimo Krill y calculo alpha_local y alpha_target
			alpha_local=calc_alpha_l(i); //calculo el alfa local (4)
			alpha_target=calc_alpha_t(i); //calculo el alfa target (8)
			alpha_total=sum(alpha_local,alpha_target); //calculo alfa total (3)
		//	cout<<"alpha_target es "; mostrar_vector(alpha_target); cout<<"alpha_local es "; mostrar_vector(alpha_local);

			
			//-b) Calculo las componentes para el foraging motion beta_i
			calc_Xs_Ks_vector(i,this->food,beta_food,fitness_beta_food);
			fitness_beta_food=this->C_food*fitness_beta_food;
			beta_food=prod_escalar(beta_food,fitness_beta_food); //Calculo beta_food (13)
			
//			//Actualizo beta_best (15)
			calc_Xs_Ks_vector(i,this->M[i].get_beta_best(),beta_best,fitness_beta_best);
			beta_best=prod_escalar(beta_best,fitness_beta_best); //calculo beta_best (15)
			this->M[i].set_beta_best(beta_best);

			//-c) calculo probabilidades de cruza y mutacion
			K_CM=(func_obj[i]-this->K_best)/(this->K_worst-this->K_best); //K de la ecuacion (21) y (23)
			if(K_CM<0.0001) K_CM=0;
			this->M[i].set_prob(K_CM, this->w);
			
			//-d) cruzo y muto
			/*
			 * Para la cruza se selecciona un individuo aleatoriamente (fórmula 20;
			 * a diferencia de DE, donde la cruza es con el vector de prueba u_i(t),
			 * acá es con otro individuo de la población X_r distinto)
			 */
			int r = i;
			while (r == i)
				r = rand()%this->num_krill;
//			this->M[i].cruzar(this->M[r]);

			/*
			 * Para la mutación calcula el vector de prueba u_i(t) usando el
			 * mejor krill de la población, y 2 krills distintos elegidos al azar.
			 */
			r = i;
			while (r == i)
				r = rand()%this->num_krill;
			int r2 = r;
			while (r2 == r || r2 == i)
				r2 = rand()%this->num_krill;
//			this->M[i].mutar(this->M[this->mejor], this->M[r], this->M[r2]);

			
			//cout<<"vector alpha_total "; mostrar_vector(alpha_total);
			//cout<<"vector beta_food ";mostrar_vector(beta_food);
			///<to do: implementar cruzar y mutar
			//e)-Actualizo la posicion del i-esimo Krill
			this->M[i].actualizar_pos(alpha_total,beta_food,this->D_diffusion);
			//cout<<endl;
		}
		
		
		c+=1; //siguiente iteracion
	}

	for(int i=0;i<this->num_krill;i++) { 
		this->func_obj[i]=fitness(this->M[i].get_pos(), id);
	}	
	//mostrar_posiciones();
	calc_best_peor(this->mejor,this->peor,this->K_best,this->K_worst);
	cout<<"el mejor esta en la posicion "<<this->mejor<<" su fitness es "<<this->K_best<<endl; 

	crear_dat_vector(v_fitness_mejor, "kh_nuevo.dat");
	
}

void herd::calcular_coef(int iteracion){
	double iter=iteracion*1.0/this->max_it;

	//los w (omega, inercia) disminuyen linealmente de 0.9 a 0.1:
	this->w = 0.8 * (this->max_it - iteracion)/this->max_it + 0.1;

	//los w (omega, inercia) disminuyen de forma no lineal, w(0) = 0.9
	//this->w = (this->w - 0.4)*(this->max_it - iteracion) / (this->max_it + 0.4);
	
	this->C_best=2*(((rand()%100)/100.0)+iter);
	this->C_food=2*(1-iter);
	this->D_diffusion=0.01*(1-iter);
}


/**
 * Corta el algoritmo según si se aproxima a la solución (depende de cada
 * función).
 */
bool herd::condicion_corte(double val)
{
	switch (this->id) {
		case 1: {
		}
		case 2: {
		}
		case 3: {
		}
		case 4: {
			return false;
		}
		case 5: { //Ackley: mínimo 0.0
			return (fabs(val) < 1e-3);
		}
	}
	return false;
}


Pos herd::calc_alpha_l(int i){
	/**@param i: indice del Krill del cual se calcula el alpha_local*/
	Pos alfa;
	//Inicializo alfa como el vector 0 por si no existe ningun vecinos
	for(int j=0;j<this->dim;j++) { alfa.push_back(0); }
	double a;
	
	for(int j=0;j<this->num_krill;j++) { //lazo hasta el i-esimo krill
		
		//cout<<"la distancia de "<<i<<" a "<<j<<" es "<<distancia(i,j)<<endl;
		if(i==j) continue;
		else if(distancia(i,j)<this->M[i].get_dist_sensing()){ //si el krill j es vecino de i
				//cout<<"la distancia de "<<i<<" a "<<j<<" es menor que el radio de sensado"<<endl;
				calc_Xs_Ks(i,j,alfa,a);
				
				alfa=sum(alfa,prod_escalar(alfa,a));
		}
	}
	//mostrar_vector(alfa);
	return alfa;
}

Pos herd::calc_alpha_t(int i){
	Pos alfa;
	double f;//Guardo el fitnness
//	cout<<"vector ";mostrar_vector(this->M.at(mejor).get_pos());
	
	calc_Xs_Ks(i, this->mejor,alfa,f);
//	cout<<"vector alfa";mostrar_vector(alfa);
	f=this->C_best*f;
//	cout<<"valor fitness "<<f<<endl;
	alfa=prod_escalar(alfa,f);
	return alfa;
}



double herd::distancia(int i,int j){
	/**
	*@brief : calcula la distancia entre el krill i y el krill j
	*/
	Pos X;
/*	cout<<"indice "<<i<<" "<<j<<endl;*/
	X=dif(this->M.at(j).get_pos(),this->M.at(i).get_pos());
	//cout<<"diferencia de "<<i<<" con "<<j<<" ";mostrar_vector(X);
	/*cout<<modulo(X)<<endl;*/
	return modulo(X);
}



double herd::fitness(Pos X,int id){
	Red.setear_pesos(X);
	
	double r = Red.probar("clouds.csv");
	
	return -r;
}

void herd::calc_pos_food(){
	/**
	@brief Funcion que estima la posicion de la comida
	*/
	//Pongo en 0 this->food
	for(int i=0;i<this->dim;i++) { this->food[i]=0;}
	//Pos food;
	double s=0,k=0;//suma de todos los fitness
	double a; //fitness actual;
	for(int i=0;i<this->num_krill;i++) { 
		//sumar todos los fitness
		a=this->func_obj.at(i);
		//cout<<"a es "<<a<<endl;
		if(a!=0) k=(1/a); else k=0;
		s+=k; 
		this->food=sum(this->food,prod_escalar(this->M[i].get_pos(), k));
	}
	//cout<<" s es "<<s<<endl<<"vector antes de dividir por s ";
	//mostrar_vector(this->food);
	s=1/s;
	this->food=prod_escalar(this->food,s);
}
void herd::calc_best_peor(int &mejor, int &peor, double &kmejor, double &kpeor){
	/**
	*@brief funcion que calcula los indices del mejor y peor individuo global
	*@param mejor: indice del mejor individuo
	*@param peor: indice del peor individuo
	*/
	kmejor=func_obj[0]; kpeor=func_obj[0]; mejor=0; peor=0;
	double temp;
	for(int i=1;i<this->num_krill;i++) { 
		temp=func_obj[i];
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
void herd::calc_Xs_Ks(int &i, int &j, Pos &X, double &K){
	/**
	*@brief Calcula las formulas (5) y (6) del paper las retorna en la variables X y K
	*@param i: posicion del i-esimo Krill
	*@param j: posicion del j-esimo Krill
	*@param X: resultado de la ecuacion (5)
	*@param K: resultado de la ecuacion (6);
	*/
	X=dif(this->M[j].get_pos(),this->M[i].get_pos()); 
//	mostrar_vector(X);
	normalizar(X); 
//	mostrar_vector(X);
	//cout<<"diferencia de fitness "<<fitness(i)-fitness(j)<<endl;
	
	K=(func_obj.at(i)-func_obj.at(j))/(this->K_worst - this->K_best);
	if(isnan(K)) K=0.0;
//	cout<<K<<endl;
}
void herd::calc_Xs_Ks_vector(int &i, Pos &j, Pos &X, double &K){
	/**
	*@brief Calcula las formulas (5) y (6) del paper las retorna en la variables X y K
	*@param i: indice del i-esimo Krill
	*@param j: posicion del j-esimo Krill
	*@param X: resultado de la ecuacion (5)
	*@param K: resultado de la ecuacion (6);
	*/
	//cout<<"entre al calculo "<<endl;
	X=dif(j,this->M[i].get_pos()); 
	//mostrar_vector(X);
	normalizar(X); 
//	mostrar_vector(X);
	//cout<<"diferencia de fitness "<<fitness(i)-fitness(j)<<endl;
	
	K=(func_obj.at(i)-fitness(j, this->id))/(this->K_worst - this->K_best);
	if(isnan(K)) K=0.0;
	
	//cout<<K<<endl;
	
//	cout<<"termine el calculo"<<endl;
}
void herd::mostrar_posiciones(){
	Pos *temp;
	for(int i=0;i<this->num_krill;i++) { 
		temp=&(this->M[i].get_pos());
		cout<<"Krill "<<i<<" Posicion "<<setw(5);
		for(size_t j=0;j<temp->size();j++) { 
			cout<<setw(5)<<temp->at(j)<<", "<<setw(5);
		}
		cout<<"fitness "<<this->func_obj.at(i)<<endl;//<<"  "<<fitness(this->M[i].get_pos(), this->id)<<endl;
	}
	cout<<endl<<endl<<endl;
}
void herd::mostrar_vector(Pos &v){
	for(size_t i=0;i<v.size();i++) { 
		cout<<v[i]<<", ";
	}
	cout<<endl;
}

void herd::set_grafica(bool a){
	this->grafica=a;
}
void herd::graficar(bool graf_krill){
	stringstream ss;
	if(this->dim==1){
	
		ss<<"plot [-512:512]-x*sin(sqrt(abs(x))) \n";
		//ss<<", \"plot.dat\" lt 3; set title \""<<titulo<<"\"";
	
		//wait(0.05);
		if(graf_krill){
			//creo el csv con las posciones de todos los Krill
			crear_dat_krill(this->M,this->func_obj,"Posicion");
			crear_dat_pos_com(this->food, fitness(this->food, this->id),"Posicion_comida");
			ss<<"replot \"Posicion\" with points \n";
			ss<<"replot \"Posicion_comida\" with points \n";
	
		}
	}
	if(this->dim==2){

		ss<<"set isosamples 50,50\n"; //números más grandes hacen mejor la gráfica, pero más lento
		ss<<"set hidden3d\n";
		ss<<"splot [-100:100][-100:100] (x**2 + y**2)**0.25 * ( sin(50 * (x**2+y**2)**0.1)**2 + 1)\n";
		//ss<<"splot [-2:2][-2:2] x*exp(-x*x-y*y) \n";
		//ss<<", \"plot.dat\" lt 3; set title \""<<titulo<<"\"";
		
		//wait(0.05);
		if(graf_krill){
			//creo el csv con las posciones de todos los Krill
			crear_dat_krill(this->M,this->func_obj,"Posicion");
			crear_dat_pos_com(this->food, fitness(this->food, this->id),"Posicion_comida");
			ss<<"replot \"Posicion\" with points \n";
			ss<<"replot \"Posicion_comida\" with points \n";
			
		}
	}
	plotter(ss.str());
	//cin.get();
}

vector< pair<double, double> > &herd::get_rangos()
{
	return this->rango;
}
