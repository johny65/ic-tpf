#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <limits>
#include "Swarm.h"
#include "utils.h"
#include "func.h"

using namespace std;



void generar(vector<double> &alet1, vector<double> &alet2){
	for(size_t i=0;i<alet1.size();i++) { 
		alet1[i]=rand()*1.0 / RAND_MAX;
		alet2[i]=rand()*1.0 / RAND_MAX;
	}
}

template <class T>
void mostrar(vector<T> x){
	for(size_t i=0;i<x.size();i++) { 
		cout<<x[i]<<", ";
	}
}

Swarm::Swarm(int cant_p,int cant_v,double c1,double c2,vector<pair<double,double> > r, int v0, int overlap) {
	/**
	@param cant_p: cantidad de particulas
	@param cant_v: cantidad de vecindades
	@param c1: aceleracion respecto a la mejor pos personal
	@param c2: aceleracion respecto a la mejor pos local (vencindad)
	@param rango: rango de inicializacion x-min, xmax del problema extendible a n-dimensiones
	@param v0: intero entre 0-100 para realizar una inicializacion aletoria de la velocidad ~U(0,v0)
	@param overlap: numero de particulas solapadas
	*/
	srand(time(NULL));
	int cantxv=cant_p/cant_v; //cantidad de particulas por vecindad
	this->rango=r;
	for(int i=0;i<cant_v;i++) { //Inicializo las particulas 
		set<int> temp; //guarda la vecindad
		for(int j=0;j<cantxv;j++) { 
			//aca podria cambiar c1 y c2 para hacerlo diferente para cada particula o cambiarlo arriba para que varie por cada vecindad 
			Particula P(c1,c2,rango,v0);
			this->Enjambre.push_back(P);
			temp.insert(temp.end(),i*cantxv+j);
		}
		this->Vecindad.push_back(temp);
	}
	
	//Para cada conjuntos C tomo un numero igual a overlap y se los agrego al conjunto siguiente
	for(int i=(this->Vecindad.size()-1);i>0;i--) { 
		set<int>::iterator q=this->Vecindad[i].begin();
		for(int j=0;j<overlap;j++) { 
			this->Vecindad.at(i-1).insert(*q);
			q++;
		}
	}
	
	//falta solapar 0 con el final lo hago aqui
	set<int>::iterator q=this->Vecindad[0].begin();
	for(int j=0;j<overlap;j++) { 
		this->Vecindad.at(cant_v-1).insert(*q);
		q++;
	}

	//Inicializo el mejor por vecidad
	for(size_t i=0;i<this->Vecindad.size();i++) { 
		this->bestxvec.push_back(*(this->Vecindad[i].begin()));
	}

}

void Swarm::mejores_pos_vecindad(int id){
	for(size_t i=0;i<this->Vecindad.size();i++) { 
		set<int>::iterator q=Vecindad[i].begin();
		int mejor=*q; 
		double m_fitness=fitness(id,this->Enjambre.at(mejor).get_Pos());
		q++;
		while(q!=Vecindad[i].end()){
			if(fitness(id,this->Enjambre.at(*q).get_Pos())<m_fitness){
				m_fitness=fitness(id,this->Enjambre.at(*q).get_Pos());
				mejor=*q;
			}
			q++;
		}
		this->bestxvec.push_back(mejor);
	}
}
Swarm::~Swarm() {
	
}

double Swarm::fitness(int id, vector<double> P){
	/**
	*@param id : identificacion de la funcion a optimizar
	*@param x y: valores en los cuales se evalua la funcion
	*@return z: el resultado de la evaluacion
	*/
	double z; ///<valor de retorno
	
	int x=P[0];
	
	
	switch(id){
	case 1: z=-x*sin(sqrt(abs(x)));
		break;
	case 2: z=x + 5*sin(3*x) + 8*cos(5*x);
		break;
	case 3: int y=P[1]; z= pow(pow(x,2)+pow(y,2),0.25)*(pow(sin(50*(pow(pow(x,2)+pow(y,2),0.1))),2)+1);
		break;
	}
	return z;
}

void Swarm::Volar(int max_it,int id, bool vis){
	/**
	@param max_it: maximo num de iteraciones
	@param id: identificador de la funcion de fitness
	*/
	int i=0;
	vector<double> pos_a, best_pp, best_vec; //pos_a: posicion actual; best_pp: mejor posicion personal lograda; best_vec: mejor de la vecindad
	//Cargo todos los fitness de las posiciones iniciales
	for(size_t i=0;i<this->Enjambre.size();i++) { 
		this->func_obj.push_back(fitness(id, this->Enjambre[i].get_Pos()));
		cout<<this->func_obj.at(i)<<endl;
	}
	

	double mejor_a; //mejor actual;
	
	vector<double> alet1;
	vector<double> alet2;
	//Inicializo con 0
	for(size_t i=0;i<this->Enjambre[i].get_Pos().size();i++) { 
		alet1.push_back(0);
		alet2.push_back(0);
	}
	
	while (i<max_it){
		
		for(size_t j=0;j<this->Vecindad.size();j++) {//Para cada vecindad 
			set<int>::iterator q=this->Vecindad[j].begin();
			while(q!=this->Vecindad[j].end()){
				
				int mejor_vecindad=this->bestxvec[j];
				best_vec=this->Enjambre[mejor_vecindad].get_Pos();
				
				//pos_a=this->Enjambre.at(*q).get_Pos(); //posicion actual de la particula
				best_pp=this->Enjambre.at(*q).get_best_pers(); //mejor posicion personal obtenida por la particula
				
				//Actualizo la mejor posicion personal de cada particula y calculo la mejor posicion en el vecindario
				if(func_obj.at(*q)<fitness(id,best_pp)){
					this->Enjambre.at(*q).actualizar_best_pers();//actualizo la posicion pesonal
				}
				
				if(this->func_obj.at(*q)<fitness(id,best_vec)){
					//actualizo la mejor posicion local (en el vecindario)
					this->bestxvec[j]=*q; //actualizo el indice del mejor de la vecindad
				}
				q++;
			}
		}
		mostrar_posiciones(id);
		cout<<"mejor por vecindad "; mostrar(this->bestxvec); cout<<endl;
		
		generar(alet1, alet2);
		
		 
		for(size_t j=0;j<this->Vecindad.size();j++) { 
			int ind_mejor_vecindad=this->bestxvec[j];
			set<int>::iterator q=this->Vecindad[j].begin();
			while(q!=this->Vecindad[j].end()) { 
				//Actulizo la velocidad
				this->Enjambre.at(*q).set_r(alet1,alet2);
				this->Enjambre.at(*q).actualizar_vel(this->Enjambre.at(ind_mejor_vecindad).get_Pos());
				//Actualizo la posicion
				this->Enjambre.at(*q).actualizar_pos();
				q++;
			}
		}
		
		//recalculo todos los fitness
		for(size_t k=0;k<this->Enjambre.size();k++) { 
			this->func_obj.at(k)=fitness(id, this->Enjambre[k].get_Pos());
		}
		if(vis){
			graficar(id);
		}
		
		mejor_a=*min_element(this->func_obj.begin(),this->func_obj.end());
		
		if(evaluar_rad_norm()<0.001) {mostrar_posiciones(id);cout<<"Corte en la iteracion "<<i<<endl; cout<<"El valor del radio es"<<evaluar_rad_norm()<<endl; break;}
		
		i+=1; //Siguiente iteracion
		
	}
		
		//cout<<endl<<"Finaliza por cantidad de iteraciones "<<endl<<endl;
		mostrar_posiciones(id);
		cout<<"El mejor de todos es "<<*min_element(this->func_obj.begin(),this->func_obj.end());
		
		graficar(id);
	
		
}



void Swarm::mostrar_posiciones(int id){
	for(size_t i=0;i<this->Vecindad.size();i++) { //recorro la vecindad
		set<int>::iterator q=this->Vecindad[i].begin();
		cout<<"Vecindad "<<i<<endl;
		while(q!=this->Vecindad[i].end()) {  //recorro las particulas de la vecindad i
			cout<<"Particula "<<*q<<" ";
			mostrar(this->Enjambre[*q].get_Pos());
			cout<<" fitness "<<this->func_obj.at(*q)<<endl;
			//cout<<endl<<"------------------"<<endl;
			q++;
		}
	}
}
void Swarm::graficar(int id){
	stringstream ss;
	if(id==1){
//		z=-x*sin(sqrt(abs(x)));
		ss<<"plot [-512:512]-x*sin(sqrt(abs(x))) \n";
		crear_datos(this->Enjambre,this->func_obj, "datos");
		ss<<"replot \"datos\" with points \n";

		
		}
	if(id==2){
//		z=x + 5*sin(3*x) + 8*cos(5*x);
		ss<<"set isosamples 500\n";
		ss<<"plot [0:20] x+5*sin(3*x)+8*cos(5*x) \n";
		crear_datos(this->Enjambre,this->func_obj, "datos");
		ss<<"replot \"datos\" with points \n";
	}
	if(id==3){
		ss<<"set isosamples 50,50\n"; //números más grandes hacen mejor la gráfica, pero más lento
		ss<<"set hidden3d\n";
		ss<<"splot [-100:100][-100:100] (x**2 + y**2)**0.25 * ( sin(50 * (x**2+y**2)**0.1)**2 + 1)\n";
		crear_datos(this->Enjambre,this->func_obj, "datos");
		ss<<"replot \"datos\" with points \n";
	}
	plotter(ss.str());
	cin.get();
	
}
double Swarm::evaluar_rad_norm(){
	double Rmax, DiameterS;
	
	int ind_p=0;
	double fit_alto=this->func_obj.at(0);
	for(int i=1;i<this->Enjambre.size();i++) { 
/*		cout<<"fitness de la particula "<<i<<" "<<this->func_obj[i]<<endl;*/
		if(this->func_obj[i]>fit_alto){
			fit_alto=this->func_obj[i];
			ind_p=i;
		}
	}
	//Busco el mejor global
	double mejor_f=this->func_obj.at(0); int ind_m=0;
	for(int j=1;j<this->Enjambre.size();j++) { 
		if(this->func_obj.at(j)<mejor_f){
			mejor_f=this->func_obj.at(j);
			ind_m=j;
		}
	}
	
	Rmax=norma(dif(this->Enjambre.at(ind_p).get_Pos(),this->Enjambre.at(ind_m).get_Pos()));
	DiameterS=this->rango.at(0).second-this->rango.at(0).first;
//	cout<<"DiameterS es "<<DiameterS<<endl;
	cout<<"La norma es "<<Rmax<<endl;
//	cout<<"El peor es la particula "<<ind_p<<endl;
//	cout<<"El mejor es la particula "<<ind_m<<endl;
	
	return Rmax/DiameterS;
	
}
