#include <valarray>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include "GNUplot.h"

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
		aux.push_back(-1);
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
		aux.push_back(-1);
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
		for(int i=1;i<n;++i){
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
	out<<ss.str();
	out.close();
	
}

void guardar_csv(const char *file, vector< vector<double> > &datos)
{
	ofstream out(file, ios::trunc);
	for (size_t i=0; i<datos.size(); ++i){
		for (size_t j=1; j<datos[i].size()-1; ++j){
			out<<datos[i][j]<<", ";
		}
		out<<datos[i].back()<<endl;
	}
	out.close();
}

void mostrar_sdcapa(vector<vector<double> > x){
	vector<vector<double> >::iterator q=x.begin();
	
	while(q!=x.end()){
		for(size_t i=0;i<(*q).size();i++) { 
			cout<<(*q)[i]<<" ";
		}
		cout<<endl;
		q++;
	}
}

void pesos_a_archivo(vector< vector<double> > pesos){
	ofstream out("pesos.txt", ios::app);
	std::ostringstream aux;
	for (int i=0; i<pesos.size(); i++){
		for (int j=0; j< pesos[i].size(); j++){
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
