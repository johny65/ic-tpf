#include <stdexcept>
#include "Network.h"
#include "func.h"

/**
 * @brief Constructor, fija los parámetros por defecto.
 */
Network::Network() :
	eta(0.01), alfa(0.0), max_epocas(1000000), tol(0.01), sig_a(1.0), couts(false)
{
	srand(time(NULL) + getpid());
}


/**
 * @brief Inicializa la arquitectura de la red con las capas y neuronas fijadas.
 *
 * @param perceptrones_por_capa Vector donde cada elemento indica la cantidad
 * de perceptrones que va a haber en esa capa (la cantidad de capas la establece
 * la longitud del vector).
 */
void Network::setear_arquitectura(vector<int> perceptrones_por_capa)
{
	
	//capas ocultas (la capa de entrada es considerada capa oculta)
	int t = perceptrones_por_capa.size() - 1;
	for (int i=0; i<t; ++i){
		Layer nueva(perceptrones_por_capa[i], true);
		this->capas.push_back(nueva);
	}

	//capa de salida (pongo a los perceptrones como hidden = false)
	Layer nueva(perceptrones_por_capa[t], false);
	this->capas.push_back(nueva);

	//ya aloco el espacio para los vectores de salida de las capas;
	
	this->salidas_capas = vector< vector<double>* >(cant_capas());
	for (int i=0; i<cant_capas()-1; ++i){
		//si la capa es oculta, su salida será la entrada para otra capa,
		//entonces hay que agregar el -1 del sesgo
		this->salidas_capas[i] = new vector<double>(this->capas[i].size() + 1, -1);
	}
	//a la capa de salida no
	this->salidas_capas.back() = new vector<double>(this->capas.back().size());
		
}

	
/**
 * @brief Devuelve la cantidad de capas de la red.
 */
int Network::cant_capas()
{
	return this->capas.size();
}


void Network::setear_pesos(double X[],int N){
	int ind1=0, ind2=3;
	
	for(int i=0;i<this->capas[0].size();i++) {//Para la primera capa 
		vector<double> p(X+ind1,X+ind2);
		this->capas[0][i].set_pesos(p);
		ind1=ind2;
		ind2+=3;
	}
	

	int c=0;
	//Para las otras capas (comenzando en la capa 1) 
	for(int i=1;i<this->capas.size();i++) {  
		c=(this->capas[i-1].size()+1);
		ind2=ind1+c;
	
		for(int j=0;j<this->capas[i].size();j++) { 
			vector<double> p(X+ind1,X+ind2);
			
			this->capas[i][j].set_pesos(p);
			ind1=ind2;
			ind2+=c;
		}
	}


}


/**
 * @brief Para inicializar todos los pesos de la red (los pesos de todas las
 * neuronas que tiene).
 */
void Network::inicializar_pesos()
{
	//recorro todos los perceptrones diciéndoles que inicializen sus pesos

	//para los que están en la capa de entrada, la cantidad de pesos que tienen
	//es igual al número de entradas)
	for (size_t j=0; j<this->capas[0].size(); ++j){
		this->capas[0][j].inicializar_pesos(this->datos[0].size());
	}

	//para los demás la cantidad de pesos es igual a la cantidad de perceptrones
	//en la capa anterior más el peso correspondiente al sesgo
	for (size_t i=1; i<this->capas.size(); ++i){
		for (size_t j=0; j<this->capas[i].size(); ++j){
			this->capas[i][j].inicializar_pesos(capas[i-1].size()+1);
		}
	}
	
}


/**
 * @brief Destructor.
 */
Network::~Network()
{
	for (size_t i=0; i<this->salidas_capas.size(); ++i){
		delete this->salidas_capas[i];
	}
}


/**
 * @brief Mapea las salidas deseadas escalares a salidas vectoriales.
 *
 * Por ejemplo, si la salida deseada puede ser una de 3 clases (0, 1 ó 2), la
 * red debería tener 3 neuronas de salida donde se activará una sola de ellas
 * indicando la clase elegida en la clasificación. Por lo tanto las salidas
 * deseadas de la red quedan mapeadas de la siguiente forma:
 *
 * 0 => +1 -1 -1
 * 1 => -1 +1 -1
 * 2 => -1 -1 +1
 *
 * @param x vector de salidas deseadas escalares.
 */
vector< vector<double> > Network::mapear(vector<double> &x)
{
	///\todo ver eso del epsilon
	
	int c = this->capas.back().size(); //si la función es de la clase no hace falta pasar esto como parámetro

	vector< vector<double> > sal_m;
	if(c==1){
		//si hay una sola neurona en la última capa, las salidas no tienen mapeo
		//(-1 ó +1), solamente se pone cada valor en un vector aparte
		for (size_t i=0; i<x.size(); ++i) {
			sal_m.push_back(vector<double>(1, x[i] == 0 ? -1 : x[i])); //al 0 lo pone como -1
		}
	}
	else {
		//sino, se hace el mapeo doble->vector, donde queda en +1 el elemento
		//correspondiente al valor
		vector<double> n(c, -1.0);
		for (size_t i=0; i<x.size(); ++i) {
			sal_m.push_back(n);
			try {
				sal_m[i].at(x[i]) = 1.0; //pongo el at para que tire error si tenemos menos neuronas que las que necesita el mapeo
			} catch (out_of_range ex) {
				cout<<"Error: no se pueden mapear las salidas con la cantidad \
de neuronas establecidas para la capa de salida ("<<ex.what()<<")\n";
				exit(-1);
			}
		}
	}

	//descomentar para ver cómo quedó el mapeo:
	/*
	for (int i=0; i<sal_m.size(); ++i){
		cout<<"salida: "<<x[i]<<" mapeo: ";
		for (int j=0; j<sal_m[i].size(); ++j){
			cout<<sal_m[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	
	return sal_m;
	
}


/**
 * @brief Devuelve si una capa es oculta o no.
 * @param x Capa a evaluar.
 */
bool Network::is_hidden(Layer x){
	return x[0].get_hidden();
}


/**
 * @brief Entrena la red neuronal.
 * @param name Nombre del archivo que contiene los datos.
 */


	








double Network::probar (const char * name) {
	vector<vector<double> > vec_dif;
	
	//Abro el archivo de datos;
	vector<double> salidas_escalares;
	this->datos.clear();
	this->datos = leer_csv(name, salidas_escalares);
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo de prueba."<<endl; return -1;}
	
	//mapeo las salidas deseadas a las neuronas de salida
	this->salidas_deseadas = mapear(salidas_escalares);
	
	int aciertos=0;//para contar la cantidad de aciertos
	
	vector<vector<double> > result_c; //resultado de la clasificacion de los datos vector<vector<>> xq tengo un vector de salida por cada dato (por el mapear)

	vector<int> salidas_mias_lindas;
	
	for(size_t i=0;i<this->datos.size();i++) {  
		//cout<<"dimension de datos "<<datos[i][0]<<"   "<<datos[i][1]<<"   "<<datos[i][2]<<endl;
		result_c.push_back(clasificar(this->datos[i])); //guardo el resultado de la clasificacion de cada dato
		vec_dif.push_back(dif(this->salidas_deseadas[i],result_c.back()));
		if(this->salidas_deseadas.back().size()==1){//si pasa por aca quiere decir que las salidas son solo 1 o -1 (no hay mapeo a vector)
			//if(abs(vec_dif[i][0])<0.07){
			if (signo(result_c[i][0]) == this->salidas_deseadas[i][0]){
				aciertos++;
			}
			this->datos[i].push_back(signo(result_c[i][0]));
		}
		else{//tengo que ver que neurona se activo busco el maximo valor
			vector<double>::iterator m = max_element(result_c[i].begin(), result_c[i].end());
			int ind = distance(result_c[i].begin(), m);
			if (this->salidas_deseadas[i][ind] == 1)
				aciertos++;
			this->datos[i].push_back(ind); //agrego mi salida para ya dibujar
		}
	}
	
	cout<<"Número de aciertos: "<<aciertos<<"/"<<this->datos.size()<<endl;
	double porc = aciertos*100.0/this->datos.size();
	cout<<"% de aciertos: "<<porc<<"%"<<endl;
	
	//generar un archivo .txt para graficar los puntos con la clasificacion obtenida
	if (this->couts){
		guardar_csv("resultados.csv", this->datos);
		graficar_puntos("resultados.csv", "resultados");
	}
	
	return -porc; //Retorno - el porcentaje de aciertos porque busco el minimo con pso
}

void Network::graficar_puntos(const char *archivo, const char *titulo)
{
	vector< vector<double> > datos;
	vector<double> salidas;
	vector<double> clases;
	
	std::ostringstream sp;
	datos=leer_csv(archivo, salidas);
	if(datos.empty()) {cout<<"Error: no se pudo leer el archivo"<<endl;return;}
	int j=0;
	vector< vector<double> >::iterator q=datos.begin();
	
	//archivo para gnuplot		
	while(q!=datos.end()){
		std::ostringstream ss;
		char nombre[15];
		sprintf(nombre, "clase %d.dat",  (int)salidas[j]);
		ofstream out(nombre, ios::app);
		int n=(*q).size();
		for(int i=1;i<n;++i){
			if(i!=n-1) ss << ((*q)[i]) << " ";
			else ss << ((*q)[i]) << endl;
		}
		out<<ss.str();
		out.close();
		//Cargamos la clase en el vector de clases
		if (find(clases.begin(), clases.end(), salidas[j])==clases.end()){
			clases.push_back(salidas[j]);
		}
		q++;
		j++;
	}
	
	//Para que GNUPLOT Grafique todas las clases
	sp<<"plot ";
	for (size_t k=0; k<clases.size()-1;k++){
		sp<<"\"clase "<<clases[k]<<".dat\" lt "<<k+1<<", ";
	}
	//Este hay q separarlo porque no tiene que incluir la ',' al final
	sp<<" \"clase "<<clases[clases.size()-1]<<".dat\" lt "<<clases.size()<<" ; set title \""<<titulo<<"\"";
	plotter(sp.str());
	//wait(this->tiempo_espera);

	//Borramos los archivos creados para dibujar
	for( int j=0;j<100000000;j++){
		
	}
	for (size_t k=0; k<clases.size();k++){
		char  nomb[15];
		sprintf(nomb, "clase %d.dat",(int)clases[k]);
		remove(nomb);
	}
	
}


/**
 * @brief Define el número máximo de épocas (iteraciones) para entrenar la
 * red.
 * @param m Cantidad máxima de épocas (presentación completa de todos los patrones
 * de entrada).
 */
void Network::set_max_epocas(int m)
{
	this->max_epocas = m;
}


/**
 * @brief Fija la tasa de aprendizaje de la red.
 * @param n Tasa de aprendizaje nueva.
 */
void Network::set_tasa(double n)
{
	this->eta = n;
}


/**
 * @brief Fija la constante para el término de momento.
 * @param a Constante de momento. 0 <= |a| < 1.
 */
void Network::set_momento(double a)
{
	this->alfa = a;
}


/**
 * @brief Setea el parámetro a de la función sigmoide.
 * @param a Constante.
 */
void Network::set_a_sigmoide(double a)
{
	///\todo ver cómo usar esto
	this->sig_a = a;
}


/**
 * @brief Define la tolerancia del error.
 *
 * A medida que va entrenando la red, se calcula una medida del error
 * entre su salida y las salidas deseadas. Cuando este error sea menor que esta
 * tolerancia, el entrenamiento se detiene.
 *
 * @param t Nueva tolerancia.
 */
void Network::set_tolerancia(double t)
{
	this->tol = t;
}


vector<double> Network::clasificar(vector<double> &Datos)
{
	//Datos.insert(Datos.begin(), -1);
	int ic;
	vector<double> *entradas = &(Datos);
	//Calcula la salida para los Datos (esto una vez que ya esta entrenado)
	for (size_t k=0; k<this->capas.size(); ++k){
		Layer &capa = this->capas[k]; //parado en la capa k
		if (is_hidden(capa))
			ic = 1; //empezar a llenar salida_capa desde el índice 1 (el 0 es el -1 del sesgo)
		else
			ic = 0; //empezar a llenar salida_capa desde el índice 0
		//meter las entradas por los perceptrones de la capa
		vector<double> *salida_capa = this->salidas_capas[k];
		for (size_t j = ic; j<capa.size()+ic; ++j){ //for por cada neurona de la capa k
		//	cout<<"dimension de las entradas"<<(*entradas).size()<<endl;
			salida_capa->at(j) = capa[j-ic].clasificar(*entradas);
		}
		
		
		entradas=salida_capa;
		
	}
	return *entradas;
}

void Network::mostrar_pesos(){
	vector<Layer>::iterator q=this->capas.begin();
	int i=0;
	while(q!=capas.end()){
		cout<<"Capa "<<i<<endl<<" --------------------------------"<<endl;
		vector<Perceptron>::iterator u=(*q).begin();
		while(u!=(*q).end()) { 
			(*u).mostrar_pesos();
			u++;
		}
		q++;
		i++;
		cout<<endl;
	}
}


/**
 * @brief Función para dibujar la estructura de la red neuronal.
 *
 * Hace un grafiquito mostrando cómo es la estructura de la red según se
 * configuró. Requiere tener `graphviz` instalado (el programa `dot`) e
 * `ImageMagick` para mostrar la imagen (el programa `display`).
 */
void Network::dibujar_red()
{
	ofstream f("red.gv");
	f<<"digraph {\nrankdir=LR\n";
	for (size_t i=0; i<this->datos[0].size()-1; ++i){
		f<<"x"<<i<<" [shape=point, label=\"\"]\n";
	}
	for (size_t i=0; i<this->capas.size(); ++i){
		for (size_t j=0; j<this->capas[i].size(); ++j){
			f<<"c"<<i<<"p"<<j<<" [shape=circle, label=\"\"]\n";
		}
	}
	//cout<<"ultima cap: "<<this->capas.back().size()<<endl;
	//cout<<"ultima cap: "<<this->capas[this->capas.size()-1].size()<<endl;
	for (size_t i=0; i<this->capas.back().size(); ++i){
		f<<"s"<<i<<" [style=invisible, shape=point, label=\"\"]\n";
	}
	
	for (size_t i=0; i<this->datos[0].size()-1; ++i){
		for (size_t j=0; j<this->capas[0].size(); ++j){
			f<<"x"<<i<<" -> "<<"c0p"<<j<<endl;
		}
	}
	
	for (size_t i=0; i<this->capas.size()-1; ++i){
		for (size_t j=0; j<this->capas[i].size(); ++j){
			for (size_t k=0; k<this->capas[i+1].size(); ++k){
				f<<"c"<<i<<"p"<<j<<" -> "<<"c"<<i+1<<"p"<<k<<endl;
			}
		}
	}

	for (size_t i=0; i<this->capas.back().size(); ++i){
		f<<"c"<<this->capas.size()-1<<"p"<<i<<" -> s"<<i<<endl;
	}
	
	f<<"\n}";
	f.close();
	system("dot -Tpng -ored.png red.gv");
	system("display red.png");
}


/**
 * @brief Función para guardar los pesos de la red en un Archivo.
 */
void Network::guardar_pesos(){
	for (size_t i=0; i<this->capas.size(); ++i){
		vector< vector<double> > pesos_capa;
		for (size_t j=0; j<capas[i].size(); ++j){
			pesos_capa.push_back(capas[i][j].get_vector_pesos());
		}
		pesos_a_archivo(pesos_capa);
	}
}
