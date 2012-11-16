#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <limits>
#include "genetic.h"
#include "utils.h"


using namespace std;


/**
 * @brief Constructor.
 * @param n Cantidad de individuos que va a tener la población.
 * @param l Longitud de cada cromosoma.
 */
GA::GA(int n, int l) : itmax(100), pc(0.9), pm(0.1), elite(0)
{
    srand(time(NULL) + getpid());
    inicializar_poblacion(n, l);
}


/**
 * @brief Establece la cantidad máxima de iteraciones.
 */
void GA::setMaximasIteraciones(int it)
{
    this->itmax = it;
}


/**
 * @brief Función principal que ejecuta el algoritmo genético.
 */
Cromosoma GA::Ejecutar()
{
    int it = 0;
    int r1, r2;
    while (it < this->itmax){
        
        Poblacion nueva = seleccionar(this->poblacion);

        for (int i=0; i<this->N; ++i){
            r1 = rand()%this->N; r2 = rand()%this->N;
            if (rand()/RAND_MAX <= this->pc){
                cruzar(nueva[r1].cromosoma,
                    nueva[r2].cromosoma);
            }
            if (rand()/RAND_MAX <= this->pm){
                mutar(nueva[r1].cromosoma);
            }
            if (rand()/RAND_MAX <= this->pm){    
                mutar(nueva[r2].cromosoma);
            }
        }

        if (this->elite != 0) { //elitismo, agarrar los mejores y pasarlos directamente
            sort(this->poblacion.begin(), this->poblacion.end());
            for (int j=0; j<this->elite; ++j){
                nueva[j] = this->poblacion[j];
            }
        }
        
        this->poblacion = nueva;
        it++;
    }
    
    evaluar_fitness_poblacion();
    sort(this->poblacion.begin(), this->poblacion.end());

    crear_dat_vector(f_mejor, "fmejor.dat");
    crear_dat_vector(f_peor, "fpeor.dat");
    crear_dat_vector(f_promedio, "fprom.dat");
    plotter("plot \"fmejor.dat\" with lines");
    plotter("replot \"fpeor.dat\" with lines");
    plotter("replot \"fprom.dat\" with lines");
    
    return this->poblacion.front().cromosoma;
}


/**
 * @brief Crea una población aleatoria de `n` individuos de longitud `l`. Cada
 * individuo está representado por un cromosoma (cadena de genes).
 */
void GA::inicializar_poblacion(int n, int l)
{
    this->N = n;
    int r, i, j;
    this->poblacion = Poblacion(n);
    Gen *s;
    for (i=0; i<n; ++i){
        s = new Gen[l+1];
        for (j=0; j<l; ++j){
            r = rand();
            s[j] = (r%2 ? '0' : '1');
        }
        s[l] = '\0';
        this->poblacion[i].cromosoma = s;
        delete[] s;
    }
}


/**
 * @brief Cruza dos cromosomas.
 */
void GA::cruzar(Cromosoma &a, Cromosoma &b)
{
    assert(a.size() == b.size());
    int l = a.size();
    int r = rand()%l; //locus aleatorio
    swap_ranges(a.begin()+r, a.end(), b.begin()+r);
}


/**
 * @brief Muta un cromosoma (intercambia un bit aleatorio).
 */
void GA::mutar(Cromosoma &a)
{
    int r = rand()%a.size();
    a[r] = (a[r] == '0' ? '1' : '0');
}


/**
 * @brief Función de selección (por ahora sólo competencia).
 */
Poblacion GA::seleccionar(Poblacion &vieja)
{
    const int N = 5;

    double maxfit = -numeric_limits<double>::max();
    int maxind = 0;

    evaluar_fitness_poblacion();
    Poblacion nueva(vieja.size());

    for (size_t i=0; i<nueva.size(); ++i){
        for (int j=0; j<N; ++j){
            int r = rand()%vieja.size();
            Individuo &seleccionado = vieja[r];
            if (seleccionado.fitness > maxfit){
                maxfit = seleccionado.fitness;
                maxind = r;
            }
        }
        nueva[i] = vieja[maxind];
    }

    return nueva;
}


/**
 * @brief Evalúa el fitness de cada individuo de la población.
 */
void GA::evaluar_fitness_poblacion()
{
    double fmin = numeric_limits<double>::max();
    double fmax = -numeric_limits<double>::max();
    double sum = 0.0;
    
    for (int i=0; i<this->N; ++i){
        this->poblacion[i].fitness = fitness_func(
            this->poblacion[i]);
        if (this->poblacion[i].fitness < fmin) fmin = this->poblacion[i].fitness;
        if (this->poblacion[i].fitness > fmax) fmax = this->poblacion[i].fitness;
        sum += this->poblacion[i].fitness;
    }

    this->f_mejor.push_back(fmax);
    this->f_peor.push_back(fmin);
    this->f_promedio.push_back(sum/this->N);
    
}


/**
 * @brief Establece la función de fitness a usar para evaluar la población.
 * @param f Función de fitness, debe aceptar como parámetro un Individuo&.
 */
void GA::setFuncionFitness(double (*f)(Individuo&))
{
    this->fitness_func = f;
}


/**
 * @brief Uso de elitismo en el algoritmo (el mejor o los n mejores se
 * mantienen tras generación).
 * 
 * @param n Cantidad de individuos que pasan directamente a la siguiente
 * generación. Si es 0 no hay elitismo.
 */
void GA::Elitismo(int n)
{
    this->elite = n;
}
