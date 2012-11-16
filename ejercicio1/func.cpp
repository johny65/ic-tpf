#include <iostream>
#include <cmath>
#include <cassert>
#include <sstream>
#include <limits>
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


/**
 * @brief Función 1. Mínimo: -418.98 en x = 420.97
 */
double func1(double x)
{
    return -x * sin(sqrt(fabs(x)));
}


/**
 * @brief Función de fitness para la Función 1.
 */
double fitness1(Individuo &i)
{
    double x = decode(i.cromosoma, 10, true);
    return -func1(x);
}


/**
 * @brief Función 2. Mínimo: -9.4338 en x = 1.8270
 */
double func2(double x)
{
    return x + 5*sin(3*x) + 8*cos(5*x);
}


/**
 * @brief Función de fitness para la Función 2.
 */
double fitness2(Individuo &i)
{
    double x = decode(i.cromosoma, 6, false);
    return -func2(x);
}


/**
 * @brief Función 3. Mínimo: 
 */
double func3(double x, double y)
{
    double xx = x*x, yy = y*y, xy = xx + yy;
    double s = sin(50 * pow(xy, 0.1));
    return pow(xy, 0.25) * (s*s + 1);
}


/**
 * @brief Función de fitness para la Función 3.
 */
double fitness3(Individuo &i)
{
    //8 bits parte entera (7 -> 128, 8 para -128,128)
    //3 bits decimal
    //total l = 8+3+8+3 = 11+11 = 22
    Cromosoma &c = i.cromosoma;
    double x = decode(c.begin(), c.begin()+2, 3, true);
    double y = decode(c.begin()+2, c.end(), 3, true);
    //cout<<x<<" "<<y<<endl;
    //if (x < -100 || x > 100 || y < -100 || y > 100)
		//return -numeric_limits<double>::min();
    //else
		return -func3(x, y);
}
