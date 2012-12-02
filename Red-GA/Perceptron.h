#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include "GNUplot.h"

using namespace std;

class Perceptron;
typedef vector<Perceptron> Layer;

class Perceptron {
	/**
	@brief Clase Perceptron Simple
	*/
private:
	int nd; ///< Cantidad total de entradas del perceptrón (incluye sesgo)
	vector<double> pesos; ///< Vector de pesos
	vector<double> dw_anteriores; ///< Vector de incrementos pasados de pesos, para usarlos con el término de momento
	double delta; ///< Gradiente local
	bool hidden; ///< Indica si pertenece a una capa oculta
	double v; ///< Campo inducido local (o salida lineal del perceptrón, es decir, v es igual a la suma de los pesos por las entradas sin pasar por la función de activación)
	
	//vector<double> salidas; ///< Vector de salidas
	//vector<double> salidas_deseadas; ///< Vector con las salidas esperadas
	//double (*func)(double, double); ///< Función de activación
	//double tol; ///< Tolerancia del error para detener el entrenamiento
	//bool graficos; ///< Indica si se activan los gráficos o no
	//bool couts; ///< Indica si se deben mostrar salidas por consola
	//bool show_error; ///< Indica si se debe mostrar el gráfico de error
	//vector<double> error_ent; ///< Guarda el error por iteración para el entrenamiento

	//para validación cruzada:
	//vector<double> error; ///< Guarda el error de la prueba para cada partición
	//vector< vector<double> > weight; ///< Guarda los pesos con los que termina cada entrenamiento

	//GNUplot plotter; ///< Conexión con GNUplot
	//GNUplot error_graf; /// Para graficar error de entrenamiento
	//double tiempo_espera; ///< Tiempo entre frames para la animación
	//void graficar(const char *titulo);
	//void graficar();
	
public:
	Perceptron();
	Perceptron(bool);
	~Perceptron();
	double get_delta();
	bool get_hidden();
	double get_salida();
	double get_peso(int peso);
	void set_pesos(vector<double> x);
	
	//void fijar_tasa(double m);
	//void set_tolerancia(double t);
	//void set_tiempo_espera(double t);
	//void set_graficos(bool g);
	//void set_show_error(bool g);
	//void set_salidas(bool s);
	
	void inicializar_pesos(int);
	double clasificar(const vector<double> &D);
	void calcular_delta(double ej);
	void calcular_delta(Layer&, int);
	void actualizar_pesos(vector<double>&, double eta, double alfa = 0.0);
	void mostrar_pesos();
	vector<double>& get_vector_pesos();

	
};

#endif
