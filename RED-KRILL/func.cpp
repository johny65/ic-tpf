#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <set>
#include "func.h"


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
	Pos r;
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

Pos prod_escalar(const Pos &x, double nu){
	Pos y;
	int n=x.size();
	for(int i=0;i<n;++i){
		y.push_back(nu*x[i]);
	}
	return y;
}

double dot(const vector<double> &x, const vector<double> &y)
{
	//cout<<x.size()<<" "<<y.size()<<endl;
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

void normalizar(Pos &X){
	double n=0;
	for(size_t i=0;i<X.size();i++) { 
		n+=X[i]*X[i];
	}
	n=(1/(sqrt(n)+0.0001));
	if(n!=0){
		X=prod_escalar(X,n);
		
	}
	
}


double modulo(Pos &X){
	double m=0;
	if(X.size()==1) {return abs(X.at(0));}
	for(size_t i=0;i<X.size();i++) { 
		m+=pow(X[i],2);
	}
	return sqrt(m);
}

void mostrar(Pos &Y){
	for(size_t i=0;i<Y.size();i++) { 
		cout<<Y[i]<<", ";
	}
	cout<<endl;
}



double sigmoide(double valor, double a)
{
	//double res = (1.0 - exp(-a*valor)) / (1.0 + exp(-a*valor));
	double res = (2.0/(1.0 + exp(-a*valor)))-1;
	return res;
}

double derivada_sigmoide(double x, double a)
{
	double res = 2.0 * a * exp(a*x) / pow((exp(a*x) + 1), 2.0);
	return res;
}
