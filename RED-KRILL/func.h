#ifndef FUNC_H
#define FUNC_H

/**
	@file func.h Maneja todas las funciones matemáticas.
*/

#include <vector>
#include <cmath>
#include <ctime>

#include "Krill.h"
using namespace std;
typedef vector<double> Punto;


/**
 * @brief Calcula la distancia euclídea entre 2 puntos de cualquier dimensión
 * (sin calcular la raíz cuadrada).
 */
double dist(Punto a, Punto b);




/**
 * @brief Rutina que inicializa el vector de pesos aletoriamente (valores
 * entre [-0.5, 0.5]).
 * @param nd Es la longitud del vector a retornar (cantidad total de entradas
 * teniendo en cuenta el -1).
 * @return Vector de pesos inicializados al azar.
 */
vector<double> init_weight(int nd);


/**
 * @brief Rutina que suma vectores componente a componente.
 */
vector<double> sum(const vector<double> &y, const vector<double> &x);


/**
 * @brief Rutina que resta vectores componente a componente.
 */
vector<double> dif(const vector<double> &y, const vector<double> &x);


/**
 * @brief Producto de un vector por un escalar (aunque el nombre no lo sugiera).
 */
Pos prod_escalar(const Pos &x, double nu);


/**
 * @brief Producto punto entre 2 vectores.
 */
double dot(const vector<double> &x, const vector<double> &y);


/**
 * @brief Calcula la energía de un vector (suma de los cuadrados).
 * @param s Vector.
 */
double energia(const vector<double> &s);


/**
 * @brief Función signo.
 */
double signo(double valor);


/**
 * @brief Función de base radial gaussiana.
 * @param x Punto a evaluar.
 * @param media Media para la gaussiana (mu).
 * @param sigma2 Varianza para la gaussiana (sigma cuadrado).
 */
double gaussiana(Punto &x, Punto &media, double sigma2);


/**
*@brief : normaliza un vector y lo devuelve en el mismo
*/
void normalizar(Pos &X);

/**
*@brief : calcula el vector normalizado y lo devuelve. X queda intacto
*/
/*Pos normalizar(Pos &X);*/

double modulo(Pos &X);
void mostrar(Pos &Y);




double sigmoide(double valor, double a = 1.0);
double derivada_sigmoide(double valor, double a = 1.0);

#endif
