#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include "Perceptron.h"
#include "utils.h"
#include "func.h"
#include "wait.h"
#include "GNUplot.h"

using namespace std;

/**
 * @brief Constructor por defecto.
 *
 * Por defecto el perceptrón es establecido como perteneciente a una capa
 * oculta.
 */
Perceptron::Perceptron() : hidden(true)
{
	//srand(time(NULL));
}


/**
 * @brief Constructor con parámetro para establecer si es oculta o no.
 *
 * @param h true si el perceptrón está en una capa oculta, false en caso
 * contrario.
 */
Perceptron::Perceptron(bool h)
{
	this->hidden = h;
	//srand(time(NULL));
}


/**
 * @brief Destructor.
 */
Perceptron::~Perceptron() {}


/**
 * Inicializa los pesos del perceptrón en valores aleatorios.
 *
 * @param num_entradas Cantidad de pesos (cantidad de entradas que tiene el
 * perceptrón contando el sesgo)
 */
void Perceptron::inicializar_pesos(int num_entradas)
{
	this->pesos = init_weight(num_entradas);

	this->dw_anteriores = vector<double>(this->pesos.size(), 0.0);
	
}


/**
 * @brief Devuelve si el perceptrón se encuentra en una capa oculta.
 * @return true si está en una capa oculta, false si está en la capa de salida.
 */
bool Perceptron::get_hidden(){
	return hidden;
}


/**
 * @brief Calcula el gradiente local de una neurona que se encuentra en la
 * capa de salida.
 *
 * Fórmula: deltaj = ej * phi'(vj)
 *
 * (Pág. 175 Haykin: Neural Networks - A Comprehensive Foundation - 2º Ed.)
 *
 * @param ej Valor que corresponde al error en la salida de la neurona (es
 * decir:
 *     ej = dj - yj
 * donde:
 *     dj = salida deseada para la neurona
 *     yj = salida obtenida por la neurona).
 */
void Perceptron::calcular_delta(double ej)
{
	if (this->hidden) {
		cout<<"Error: calculando delta de capa de salida en una capa oculta.\n";
		exit(-1);
	}
	else {
		this->delta = ej*derivada_sigmoide(this->v);
	}
}

void Perceptron::set_pesos(vector<double> x){
	this->pesos=x;
}


/**
 * @brief Calcula el gradiente local de una neurona que se encuentra en una
 * capa oculta.
 *
 * Fórmula: deltaj = phi'(vj) * sum_k( deltak * wkj )
 * 
 * (Pág. 175 Haykin: Neural Networks - A Comprehensive Foundation - 2º Ed.)
 *
 * @param capa_posterior Referencia a la capa posterior (la de la derecha) de
 * la capa donde se encuentra el perceptrón. De esta forma recorre las neuronas
 * de esa capa pidiéndoles sus gradientes locales y sus pesos que las unen a
 * ella.
 * @param indice Índice de la neurona en su capa (posición).
 */
void Perceptron::calcular_delta(Layer &capa_posterior, int indice)
{
	if (!this->hidden){
		cout<<"Error: calculando delta de capa oculta en una capa de salida.\n";
		exit(-1);
	}
	else {
		double s = 0.0;
		for (size_t i=0; i<capa_posterior.size(); ++i){
			/* por cada neurona de la capa posterior, le pido su delta y el peso
			 * que la une a mí (este peso lo guarda ella, no yo) y con esto
			 * hago la sumatoria.
			 * Tener en cuenta que el peso que corresponde a la neurona k, está
			 * guardado en el índice k+1, ya que el índice 0 corresponde al peso
			 * del sesgo. Por eso el "indice + 1".
			 */
			s += capa_posterior[i].get_delta() * capa_posterior[i].get_peso(indice + 1);
		}
		this->delta = derivada_sigmoide(this->v)*s;
	}
}


/**
 * @brief Devuelve el gradiente local de la neurona.
 */
double Perceptron::get_delta()
{
	return this->delta;
}


/**
 * @brief Actualiza los pesos del perceptrón.
 *
 * Fórmula: Δwji(n) = eta * 𝛅j(n) * yi(n) + alfa * Δwji(n-1)
 *
 * (yi es de la capa anterior)
 * (Pág. 170 Haykin: Neural Networks - A Comprehensive Foundation - 2º Ed.)
 *
 * @param ys Vector con las salidas de las neuronas de la capa anterior
 * conectadas a mí (serían los yi).
 * @param eta Tasa de aprendizaje.
 * @param alfa Coeficiente de momento (0 <= |alfa| < 1).
 */
void Perceptron::actualizar_pesos(vector<double> &ys, double eta, double alfa)
{
	assert(ys.size() == this->pesos.size());

	double dw;
	for (size_t i=0; i<this->pesos.size(); ++i){
		dw = eta * this->delta * ys[i] + alfa * this->dw_anteriores[i];
		this->pesos[i] += dw;
		this->dw_anteriores[i] = dw;
	}
	
}




/**
 * @brief Establece el tiempo de espera entre frames para la animación, es
 * decir el tiempo que hay que esperar para dibujar otra vez.
 * @param t Tiempo de espera.
 */
/*void Perceptron::set_tiempo_espera(double t)
{
	this->tiempo_espera = t;
}
*/

/**
 * @brief Establece si se deben mostrar los gráficos o no.
 * @param g true si se muestran gráficos, false si no.
 *//*
void Perceptron::set_graficos(bool g)
{
	this->graficos = g;
}
*/

/**
 * @brief Establece si se debe graficar el error por cada iteración.
 *//*
void Perceptron::set_show_error(bool g)
{
	this->show_error = g;
}
*/

/**
 * @brief Establece si se deben mostrar salidas por pantalla o no.
 * @param s true: salidas activadas, false: salidas desactivadas.
 *//*
void Perceptron::set_salidas(bool s)
{
	this->couts = s;
}
*/

/**
 * @brief Rutina con la cual el Perceptron aprende a partir de datos.
 * @param name Nombre del archivo .csv a leer, el mismo contiene los datos de
 * entrenamiento.
 * @return -1 si no pudo leer el archivo, 0 si tuvo éxito.
 *//*
int Perceptron::entrenar(const char *name)
{
	
	vector< vector<double> > datos=leer_csv(name, this->salidas_deseadas);
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo"<<endl;return -1;}
	vector<double> entradas;
	
	vector< vector<double> >::iterator q=datos.begin();
	this->nd=(*q).size(); //cantidad total de entradas (sesgo incluido)
	
	//archivo para gnuplot
	crear_dat(datos, "plot.dat");
	
	//inicializo el vector de pesos aletoriamente con valores entre [-0.5 0.5]
	this->pesos = init_weight(nd);
	cout<<endl<<"Pesos nuevos"<<endl; mostrar_pesos(); cout<<endl;
	
	double err = 0.0;
	int iteraciones = 0;
	while (iteraciones < this->max_iter){
		salidas.clear();
		int i = 0;
		q=datos.begin();
		
		while(q!=datos.end()){
			
			entradas = *q;
			this->salidas.push_back(clasificar(entradas));
			
			if(this->salidas_deseadas[i] != salidas.back()){ //salida deseada != salida obtenida?
				pesos=recalcular_pesos(this->pesos, this->eta,
					this->salidas.back(), this->salidas_deseadas[i], entradas);				
			}
		
			if (this->couts)
				mostrar_pesos();
			
			if (this->graficos)
				graficar();
			
			q++; i++;
		}
		
		//calcular error por iteración:
		err = calc_error(this->salidas_deseadas, this->salidas);
		this->error_ent.push_back(err);

		iteraciones++;
				
		if (this->couts){
			cout<<"Error: "<<err<<endl;
			cout<<"Iteración "<<iteraciones<<endl;
		}
		
		if (err <= this->tol)
			break;
	}
	
	
	if (this->show_error){
		crear_dat_vector(this->error_ent, "error.dat");
		error_graf("plot \"error.dat\" with lines");
	}
	
	this->weight.push_back(pesos); //guardo los pesos 
	
	cout<<"Se terminó de entrenar el perceptrón.\n"<<"iteraciones "<<iteraciones<<" error "<<err<<endl;
	graficar(); //resultado final siempre se muestra
	
	//Muestro el resultado del entrenamiento
	if (this->couts){
		q=datos.begin();
		int g=0;
		while(q!=datos.end()){
			for (int i=0;i<(int)(*q).size();i++){
				cout<<setw(8)<<setprecision(3)<<(*q)[i];
			}
			cout<<"    |"<<setw(5)<<setprecision(3)<<salidas_deseadas[g];
			cout<<"    |"<<setw(5)<<setprecision(3)<<salidas[g]<<endl;
			g++;
			q++;
		}
	}
	
	error_ent.clear(); //borro errores
	salidas.clear(); //borro los datos de las salidas el Perceptron ya esta entrenado
	return 0;
}
*/

/**
 * @brief Rutina que a partir de los datos de prueba genera las salidas y grafica(idea falta implementar)
 * @param datos matriz de datos de prueba en este vector no existe salida esperada a diferencia de la rutina entrenar
 *//*
void Perceptron::probar(const char *name)
{
	vector< vector<double> > datos = leer_csv(name, this->salidas_deseadas);
	if(pesos.empty()) {cout<<"Primero debe entrenar el Perceptron"<<endl; return;}
	vector< vector<double> >::iterator q=datos.begin();

	double error_e = 0.0;
	int i=0;
	
	while(q!=datos.end()){
		this->salidas.push_back(clasificar(*q));
		error_e += calc_error_x_epoca(this->salidas_deseadas[i],this->salidas.back());
		q++; i++;
	}

	this->error.push_back(error_e); //guardo el error

	cout<<"Error de la prueba: "<<error_e<<endl;

}
*/

/**
 * @brief Función para mostrar por consola los pesos del perceptrón.
 */
void Perceptron::mostrar_pesos(){
	vector<double>::iterator q=this->pesos.begin();
	while(q!=pesos.end()){
		cout<<(*q)<<" , ";
		q++;
	}
	cout<<endl;
}


/**
 * @brief Devuelve la salida que calcula el perceptrón para una entrada dada
 * con los pesos actuales.
 * 
 * @param D Vector con un patrón de entrada.
 * @return El valor de salida calculado.
 */
double Perceptron::clasificar(const vector<double> &D){
	this->v = dot(D, this->pesos);
	return sigmoide(this->v, 1.0);
}


/**
 * @brief Devuelve el valor de un peso particular (tener en cuenta que
 * `get_peso(0)` corresponde al sesgo).
 * @param peso Índice del peso.
 */
double Perceptron::get_peso(int peso)
{
	return this->pesos[peso];
}



/**
 * @brief Función que devuelve el vector de Pesos del Perceptrón.
 */
vector<double>& Perceptron::get_vector_pesos()
{
	return this->pesos;
}
