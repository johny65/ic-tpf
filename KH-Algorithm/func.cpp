#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <limits>
#include <set>
#include "func.h"


using namespace std;

extern int cant_func_val;

double fitness_vessel(Pos &X)
{
	cant_func_val++;
	
	double &x1 = X.at(0);
	double &x2 = X.at(1);
	double &x3 = X.at(2);
	double &x4 = X.at(3);

	double fitnessmalo = numeric_limits<double>::infinity();

	if (x1 < 0.0625 || x1 > 6.1875 || x2 < 0.0625 || x2 > 6.1875)
		return fitnessmalo;
		
	if (x3 < 10 || x3 > 200 || x4 < 10 || x4 > 200)
		return fitnessmalo;
		
	if (-x1 + 0.0193*x3 > 0)
		return fitnessmalo;

	if (-x2 + 0.00954*x3 > 0)
		return fitnessmalo;

	if (-M_PI*x3*x3*x4 - (4.0/3.0)*M_PI*pow(x3, 3) + 1296000 > 0)
		return fitnessmalo;

	if (x4 - 240 > 0)
		return fitnessmalo;

	double f = 0.6224*x1*x3*x4 + 1.7781*x2*x3*x3 +
		3.1661*x1*x1*x4 + 19.84*x1*x1*x3;

	return -f;
}


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
	if(X.size()==1) {return fabs(X.at(0));}
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
