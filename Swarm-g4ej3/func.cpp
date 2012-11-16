#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <set>
#include "func.h"
#include "GNUplot.h"
#include "utils.h"

using namespace std;


double dist(Punto a, Punto b)
{
	assert(a.size() == b.size()); //puntos de la misma dimensión
	int D = a.size();
	
	double d = 0.0;
	for (int i=0; i<D; ++i){
		d += (a[i] - b[i])*(a[i] - b[i]);
	}

	return d; //no hace falta sacar raíz cuadrada
}


vector<Punto> k_means(vector<Punto> datos, int k)
{
	vector<Punto> centroides;
	vector< vector<Punto> > particiones(k);
	vector<int> ks(datos.size(), 0); //guarda a qué partición pertenece cada punto

	GNUplot plot;

	//agarro k centroides al azar (método Forgy, tomo k elementos del set de datos como
	//centroides iniciales)

	set<Punto> s;
	while ((int)s.size() != k){ //me garantizo de tomar k puntos distintos
		int p = rand()%datos.size();
		s.insert(datos.at(p));
	}
	for (set<Punto>::iterator it = s.begin(); it != s.end(); it++){
		centroides.push_back(*it);
	}
	

	bool hay_cambios = true;
	int D = datos[0].size(); //dimensión de los datos
	int it = 0;

	while (hay_cambios){ //mientras algún punto se mueva de partición

		//limpieza
		hay_cambios = false;
		for (int i=0; i<k; ++i){
			particiones[i].clear();
		}

		//asigno los puntos a los centroides más cercanos
		
		for (size_t i=0; i<datos.size(); ++i){ //recorro cada punto
			Punto &p = datos[i];
			double dmin = dist(p, centroides[ks[i]]); int c = ks[i]; //distancia a mi centroide
			for (int j=0; j<k; ++j){ //recorro cada centroide
				double d = dist(p, centroides[j]);
				if  (d < dmin){
					hay_cambios = true;
					dmin = d;
					c = j;
				}
			}
			particiones[c].push_back(p);
			ks[i] = c;
		}

		//calculo nuevos centroides
		
		for (int i=0; i<k; ++i){ //por cada centroide
			Punto aux(D, 0.0);
			for (size_t j=0; j<particiones[i].size(); ++j){ //recorro sus puntos cercanos
				aux = sum(aux, particiones[i][j]);
			}
			assert(particiones[i].size() != 0);
			for (int j=0; j<D; ++j){
				aux[j] /= particiones[i].size();
			}
			centroides[i] = aux;
		}

		it++;

		
	}
	
		crear_dat(centroides, "c.dat");
		plot("plot \"c.dat\"");

		for (int i=0; i<k; ++i){
			if (particiones[i].size() != 0){
				stringstream ss; ss<<"ar"<<i<<".dat";
				crear_dat(particiones[i], ss.str().c_str());
				stringstream s2; s2<<"replot \""<<ss.str()<<"\" lt "<<i;
				plot(s2.str().c_str());
			}
		}
		cin.get();
	

	return centroides;
}

vector<double> init_weight(int nd)
{
	double w;
	vector<double> pesos;
	for(int i=0; i<nd; ++i){ //hasta nd xq el sesgo tambien tiene peso aletorio
		w=(rand()*1.0/RAND_MAX) - 0.5;
		pesos.push_back(w);
	}
	return pesos;
}

vector<double> sum(const vector<double> &y, const vector<double> &x)
{
	assert(y.size() == x.size());
	vector<double> r;
	int n=y.size();
	for(int i=0;i<n;++i){
		r.push_back(y[i]+x[i]);
	}
	return r;
}

vector<double> dif(const vector<double> &y, const vector<double> &x)
{
	assert(y.size() == x.size());
	vector<double> r;
	int n=y.size();
	for(int i=0;i<n;++i){
		r.push_back(y[i]-x[i]);
	}
	return r;
}

vector<double> prod_escalar(const vector<double> &x, double nu)
{
	vector<double> y;
	int n=x.size();
	for(int i=0;i<n;++i){
		y.push_back(nu*x[i]);
	}
	return y;
}

double dot(const vector<double> &x, const vector<double> &y)
{
	assert(y.size() == x.size());
	double p=0;
	int n=x.size();
	for(int i=0; i<n; ++i){
		p+=x[i]*y[i];
	}
	return p;
}

double energia(const vector<double> &s){
	double e=0;
	for(size_t i=0;i<s.size();i++) { 
		e+=s[i]*s[i];
	}
	return e;
}

double signo(double valor)
{
	if(valor>=0) return 1;
	else return -1;	
}

double gaussiana(Punto &x, Punto &media, double sigma2)
{
	double res = exp(-dist(x, media) / (2*sigma2));
	return res;
}
double norma(vector<double> X){
	double N=0;
	for(int i=0;i<X.size();i++) { 
		N+=pow(X[i],2);
	}
	return sqrt(N);
}
