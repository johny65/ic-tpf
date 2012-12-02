#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>

#define rand_01 ((double)rand() / (double)RAND_MAX)
#include "Network.h"

const int numofdims = 30+110+11;
const int numofparticles = 25;
const int max_iter = 10;
Network Red;
using namespace std;

void fitnessfunc(double X[numofparticles][numofdims], double fitnesses[numofparticles])
{
	
    memset(fitnesses, 0, sizeof (double) * numofparticles);
    for(int i = 0; i < numofparticles; i++)
    {
        Red.setear_pesos(X[i],numofdims);
		
        double r = Red.probar("clouds.csv");
        
        fitnesses[i] = r;
    }
}

double mean(double inputval[], int vallength)
{
    int addvalue = 0;
    for(int i = 0; i < vallength; i++)
    {
        addvalue += inputval[i];
    }
    return (double)(addvalue / vallength);
}

void PSO(int numofiterations, double c1, double c2,
              double Xmin[numofdims], double Xmax[numofdims], double initialpop[numofparticles][numofdims],
              double worsts[], double meanfits[], double bests[], double *gbestfit, double gbest[numofdims])
{
	/**@param numofiterations: numero de iteraciones
	 @param c1 c2: constantes de movimiento
	@param Xmin Xmax: rangos limites para cada dimension
	@param initialpo[numero de particula][numero de dimension (vector posicion)]
	@param worsts[]: devuelvo los peores
	@param meanfits[]: devuelvo la media de fitnessfunc
	@param bests[]: devuelvo los mejores 
	@param gbestfit: Puntero a la Solucion
	@param gbest: Posicion de la ganadora
	*/
	
	vector<int> arq;
	arq.push_back(10);
	arq.push_back(10);
	arq.push_back(1);
	Red.setear_arquitectura(arq);
    
	vector<double> fmejor;
	
	double V[numofparticles][numofdims] = {0};
    double X[numofparticles][numofdims];
    double Vmax[numofdims];
    double Vmin[numofdims];
    double pbests[numofparticles][numofdims];
    double pbestfits[numofparticles];
    double fitnesses[numofparticles];
    double w;
    double minfit;
    int   minfitidx;

    memcpy(X, initialpop, sizeof(double) * numofparticles * numofdims);
    
	
	fitnessfunc(X, fitnesses);
    
	minfit = *min_element(fitnesses, fitnesses + numofparticles);
    minfitidx = min_element(fitnesses, fitnesses + numofparticles) - fitnesses;
    *gbestfit = minfit;
    memcpy(gbest, X[minfitidx], sizeof(double) * numofdims);

    for(int i = 0; i < numofdims; i++)
    {
        Vmax[i] = 0.2 * (Xmax[i] - Xmin[i]);
        Vmin[i] = -Vmax[i];
    }

    for(int t = 0; t < max_iter; t++)
    {
        w = 0.9 - 0.7 * (t*1.0 / numofiterations);
		cout<<"Iteracion "<<t<<endl;

		
		
        for(int i = 0; i < numofparticles; i++) //Busca el mejor fitness de cada particula para guardarlo como mejor posicion personal
        {
            if(fitnesses[i] < pbestfits[i])
            {
                pbestfits[i] = fitnesses[i];
                memcpy(pbests[i], X[i], sizeof(double) * numofdims);
            }
        }
        for(int i = 0; i < numofparticles; i++) //Actualiza posiciones
        {
            for(int j = 0; j < numofdims; j++)
            {
                V[i][j] = min(max((w * V[i][j] + rand_01 * c1 * (pbests[i][j] - X[i][j])
                                   + rand_01 * c2 * (gbest[j] - X[i][j])), Vmin[j]), Vmax[j]);
                X[i][j] = min(max((X[i][j] + V[i][j]), Xmin[j]), Xmax[j]);
            }
        }

        fitnessfunc(X, fitnesses);
        minfit = *min_element(fitnesses, fitnesses + numofparticles);
        minfitidx = min_element(fitnesses, fitnesses + numofparticles) - fitnesses;//Mejor global
      
		if(minfit < *gbestfit)
        {
            *gbestfit = minfit;
            memcpy(gbest, X[minfitidx], sizeof(double) * numofdims);
        }
		
		fmejor.push_back(-*gbestfit); //guardo mejores fitness

        if (fabs(*gbestfit) < 1e-3){
            cout<<"Cortó en la it: "<<t<<" - Sol: "<<*gbestfit<<endl;
            break;
        }

        worsts[t] = *max_element(fitnesses, fitnesses + numofparticles);
        bests[t] = *gbestfit;
        meanfits[t] = mean(fitnesses, numofparticles);
    }

	crear_dat_vector(fmejor, "fmejor");
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));

    double xmin[numofdims], xmax[numofdims];
    double initpop[numofparticles][numofdims];
    double worsts[max_iter], bests[max_iter];
    double meanfits[max_iter];
    double gbestfit;
    double gbest[numofdims];
    for(int i = 0; i < numofdims; i++)
    {
        xmax[i] =1;
        xmin[i] = -1;
    }
    for(int i = 0; i < numofparticles; i++)
        for(int j = 0; j < numofdims; j++)
        {
            initpop[i][j] = rand() % (int)(xmax[j]-xmin[j]+1) - xmax[j];
        }

    PSO(max_iter, 2, 2, xmin, xmax, initpop, worsts, meanfits, bests, &gbestfit, gbest);

    cout<<"fitness: "<<gbestfit<<endl;
    return 0;
}
