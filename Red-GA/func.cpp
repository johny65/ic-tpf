#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>
#include "func.h"

using namespace std;

/**
 * @brief Convierte una cadena binaria a un entero.
 * @param inicio Iterador que indica el inicio de la cadena.
 * @param fin Iterador que indica el fin de la cadena.
 * @param neg Si es true, el número de salida puede ser negativo (el primer
 * bit indica el signo).
 * @return Un entero.
 */
int bin2dec(iterador inicio, iterador fin, bool neg)
{
	//cout<<distance(inicio, fin)<<endl;
    int res = 0;
    int l = distance(inicio, fin) - (neg ? 2 : 1);
    while (l >= 0){
        if (*(fin - 1 - l) == '1')
            res += pow(2, l);
        l--;
    }
    if (neg && *inicio == '1'){
		res *= -1;
	}
	return res;
}


/**
 * @brief Decodifica un cromosoma.
 * 
 * El cromosoma representa un número real. Usa A bits para la parte entera
 * y el resto de bits para la parte decimal.
 *
 * @param inicio Iterador que indica el inicio del cromosoma.
 * @param fin Iterador que indica el fin del cromosoma.
 * @param A Cantidad de bits para la parte entera.
 * @param neg Si es true, es un entero con signo, sino un entero sin signo.
 */
double decode(iterador inicio, iterador fin, int A, bool neg)
{		
    stringstream ss;
    ss<<bin2dec(inicio, inicio+A, neg);
    ss<<".";
    ss<<bin2dec(inicio+A, fin, false);

    double res;
    ss>>res;
    return res;
}


/**
 * @brief Función wrapper para poder pasar un cromosoma completo.
 */
double decode(const Cromosoma &c, int A, bool neg)
{
	return decode(c.begin(), c.end(), A, neg);
}


vector<double> init_weight(int nd)
{
	double w;
	vector<double> pesos;
	for(int i=0; i<nd; ++i){ //hasta nd xq el sesgo tambien tiene peso aletorio
		w=(rand()*1.0/RAND_MAX) - 0.5;
		//w = (rand()%1000) / 1000.0 - 0.5;
		pesos.push_back(w);
	}
	return pesos;
}

vector<double> sum(const vector<double> &y, const vector<double> &x)
{
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
	//vector de pesos sin sesgo
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


/* Funciones de activación: */

/*
 * Tiene que aceptar parámetros (double, double) para que haya compatibilidad
 * con la sigmoide.
 */

double signo(double valor, double a)
{
	if(valor>=0) return 1;
	else return -1;	
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
