#ifndef utils_H
#define utils_H

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

/**
 * @file utils.h Maneja todas las rutinas de entrada/salida de archivos.
*/


/**
 * @brief Rutina para leer un archivo csv.
 *
 * Lee todas las entradas más la salida deseada. La entrada del sesgo la agrega
 * al principio. Las salidas deseadas las mete en un vector aparte.
 *
 * @param archivo Nombre del archivo que se va a leer.
 * @param sd Vector donde se guardarán las salidas deseadas.
 * @return Matriz de datos leídos, cada fila corresponde a un patrón de entrada.
*/
vector< vector<double> > leer_csv(const char *archivo, vector<double> &sd);

//no separa salidas deseada
vector< vector<double> > leer_csv(const char *archivo);


/**
 * @brief Recibe una matriz de datos y genera un archivo que puede ser usado
 * por GNUplot para graficar esos datos.
 * @param v Matriz de datos a grabar.
 * @param name Es el nombre del archivo a generar.
 */
void crear_dat(vector<vector<double> > &v, const char *name);


/**
 * @brief Recibe un vector de datos y genera un archivo que puede ser usado
 * por GNUplot para graficar esos datos.
 * @param v Vector de datos a grabar.
 * @param name Es el nombre del archivo a generar.
 */
void crear_dat_vector(vector<double> &v, const char *name);


/**
 * @brief Guarda un archivo .csv con los datos pasados.
 * @param file Nombre del archivo para guardar.
 * @param datos Matriz con los datos.
 */
void guardar_csv(const char *file, vector< vector<double> > &datos);


/**
* @brief Recibe un vector de datos y genera un archivo con todos los pesos por 
* por perceptrón.
* @param pesos Vector de pesos a grabar.
*/
void pesos_a_archivo(vector< vector<double> > pesos); 

void mostrar_sdcapa(vector<vector<double> > x);

/**
* @brief Recibe el nombre de un archivo y crea un vector con los pesos de una red.
* @param v Vector de datos a grabar.
* @param archivo Es el nombre del archivo del que se van a extraer los datos.
*/
vector< vector<double> > pesos_desde_archivo(const char * archivo);

#endif
