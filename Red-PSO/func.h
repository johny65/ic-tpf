#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

/**
	@file func.h Maneja todas las funciones matemáticas utilizadas por la clase Perceptron.
*/


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
vector<double> prod_escalar(const vector<double> &x, double nu);


/**
 * @brief Producto punto entre 2 vectores.
 */
double dot(const vector<double> &x, const vector<double> &y);


/**
 * @brief Función para recalcular los pesos del perceptrón.
 * @param pv Pesos anteriores (viejos).
 * @param tasa
 * @param s Salida generada.
 * @param se Salida esperada.
 * @param datos Entradas.
 */
vector<double> recalcular_pesos(const vector<double>&, double, double, double, const vector<double>&);


/**
 * @brief Calcula la energía de un vector (suma de los cuadrados).
 * @param s Vector.
 */
double energia(const vector<double> &s);


double signo(double valor, double a = 1.0);
double sigmoide(double valor, double a = 1.0);
double derivada_sigmoide(double valor, double a = 1.0);

#endif
