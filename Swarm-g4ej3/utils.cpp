#include <valarray>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include "utils.h"

using namespace std;

vector< vector<double> > leer_csv(const char *archivo, vector<double> &sd)
{
	vector< vector<double> > todo;
	sd.clear();
	
	vector<double> aux;
	ifstream in(archivo);
	string linea, temp;
	double val;
	while (getline(in, linea)){
		//aux.push_back(-1); //para las redes RBF no hay que poner el -1 en la entrada
		stringstream ss(linea);
		while(getline(ss, temp, ',')){
			stringstream ss2(temp);
			ss2>>val;
			aux.push_back(val);
		}
		//pasar la salida deseada al vector de salidas deseadas:
		sd.push_back(aux.back());
		aux.erase(aux.end()-1);
		
		todo.push_back(aux);
		aux.clear();
	}
	return todo;
}

vector< vector<double> > leer_csv(const char *archivo)
{
	vector< vector<double> > todo;
	
	vector<double> aux;
	ifstream in(archivo);
	string linea, temp;
	double val;
	while (getline(in, linea)){
		//aux.push_back(-1);
		stringstream ss(linea);
		while(getline(ss, temp, ',')){
			stringstream ss2(temp);
			ss2>>val;
			aux.push_back(val);
		}
		todo.push_back(aux);
		aux.clear();
	}
	return todo;
}

void crear_dat(vector<vector<double> > &v, const char *name)
{
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	vector<vector<double> >::iterator q=v.begin();
	while(q!=v.end()){
		int n=(*q).size();
		for(int i=0;i<n;++i){
			if(i!=n-1) ss << ((*q)[i]) << " ";
			else ss << ((*q)[i]) << endl;
		}
		q++;
	}
	out<<"# archivo temporal usado para graficar los puntos de entrada en gnuplot\n";
	out<<ss.str();
	out.close();
}

void crear_dat_vector(vector<double> &v, const char *name)
{
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	vector<double>::iterator q=v.begin();
	while(q!=v.end()){
		ss << (*q) << "\n";
		q++;
	}
	out<<"# archivo temporal usado para graficar error en gnuplot\n";
	out<<ss.str();
	out.close();
	
}

void guardar_csv(const char *file, vector< vector<double> > &datos)
{
	ofstream out(file, ios::trunc);
	for (size_t i=0; i<datos.size(); ++i){
		for (size_t j=0; j<datos[i].size()-1; ++j){
			out<<datos[i][j]<<", ";
		}
		out<<datos[i].back()<<endl;
	}
	out.close();
}

void pesos_a_archivo(vector< vector<double> > pesos){
	ofstream out("pesos.txt", ios::app);
	std::ostringstream aux;
	for (size_t i=0; i<pesos.size(); i++){
		for (size_t j=0; j< pesos[i].size(); j++){
				aux<<pesos[i][j]<<" ";
		}
		aux<<endl;
	}
	aux<<endl;
	out<<aux.str();
	out.close();
}

// Cargar los pesos de un Archivo a una red

vector< vector<double> > pesos_desde_archivo(const char * archivo){
	vector< vector<double> > pesos;
	vector<double> aux;
	ifstream in(archivo);
	string linea, temp;
	double val;
	while (getline(in, linea)){
		stringstream ss(linea);
		while(getline(ss, temp, ' ')){
			stringstream ss2(temp);
			ss2>>val;
			aux.push_back(val);
		}
		pesos.push_back(aux);
		aux.clear();
	}
	return pesos;
}



void crear_datos(vector<Particula> &S,vector<double> &fit, const char *name){
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	for(int i=0;i<S.size();i++) { //Para cada vecindad genero un archivo con namei donde i=1,2,3... 
		vector<double> P=S[i].get_Pos();
		for(int k=0;k<P.size();k++) { 
				ss<<P[k]<<" ";
			}
		ss<<fit[i]<<" \n";
	}

	
	
	out<<"# archivo temporal usado para graficar posicion de las particulas en gnuplot\n";
	out<<ss.str();
	out.close();
	
}



