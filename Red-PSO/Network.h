#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Perceptron.h"
#include "utils.h"

using namespace std;


/**
	@class Network Clase principal de la red neuronal.
*/
class Network {
private:

	double eta; ///< Tasa de aprendizaje
	double alfa; ///< Coeficiente para el término de momento
	int max_epocas; ///< Cantidad máxima de épocas
	double tol; ///< Tolerancia del error para detener el entrenamiento

	double sig_a; ///< Constante a para la sigmoidea

	
	vector<Layer> capas; /** R (capas) es el vector de capas, es decir la longitud del vector R determina la cantidad de capas en la red, siendo R[R.size()-1] la capa de salida*/
	vector< vector<double> > salidas_deseadas; ///< Vector con las salidas esperadas (en forma de vectores)
	
	vector< vector<double> > datos;
	
	vector< vector<double>* > salidas_capas; ///<es necesario guardar cada una de las salidas de las capas para hacer el paso hacia atras
	

	bool graficos; ///< Indica si se activan los gráficos o no
	bool couts; ///< Indica si se deben mostrar salidas por consola
	GNUplot plotter; ///< Conexión con GNUplot
	GNUplot error_graf; /// Para graficar error de entrenamiento


	vector< vector<double> > mapear(vector<double>&);
	void inicializar_pesos();
	void graficar_puntos(const char *archivo, const char *titulo);
	bool is_hidden(Layer x);
	
	///<Funciones privadas

	void entrenar_con_pso(const char *name);
	
public:

	void setear_arquitectura(vector<int> perceptrones_por_capa);
	Network();
	~Network();
	
	int cant_capas();
	void set_max_epocas(int m);
	void set_tolerancia(double t);
	void set_tasa(double n);
	void set_momento(double a);
	void set_a_sigmoide(double a);
	void entrenar(const char *name);
	void val_cross(const char *archivo, int k);
	
	double probar(const char *name);
	vector<double> clasificar(vector<double> &Datos);
	void mostrar_pesos();
	void guardar_pesos();
	int prueba() { return 2; }
	void dibujar_red();
	void setear_pesos(double X[],int N);
	
};

#endif

