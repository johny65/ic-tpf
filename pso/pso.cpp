#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <limits>
#include "../GA/utils.h"

#define rand_01 ((double)rand() / (double)RAND_MAX)

const int numofdims = 4;
const int numofparticles = 250;
const int max_iter = 10;

int cant_eval_func = 0;

using namespace std;

/*
double fitness_bat1(double x1, double x2, double x3, double x4)
{
    cant_eval_func++;
    
    //double f = 0.6224*x1*x3*x4 + 1.7781*x2*x3*x3 +
		//3.1661*x1*x1*x4 + 19.84*x1*x1*x3, C = 500;
        
	//f += C * ( pow(max(0.0, -x1 + 0.0193*x3), 2) + pow(max(0.0, -x2 + 0.00954*x3), 2)
		//+ pow(max(0.0, -M_PI*x3*x3*x4 - (4.0/3.0)*M_PI*pow(x3, 3) + 1296000), 2)
		//+ pow(max(0.0, x4 - 240), 2) );

	//f -= C * ( pow(max(0.0, 0.0625 - x1), 2) + pow(max(0.0, x1 - 6.1875), 2) +
		//pow(max(0.0, 0.0625 - x2), 2) + pow(max(0.0, x2 - 6.1875), 2) +
		//pow(max(0.0, 10 - x3), 2) + pow(max(0.0, x3 - 200), 2) + pow(max(0.0, 10 - x4), 2)
		//+ pow(max(0.0, x4 - 200), 2) );


    double fitnessmalo = numeric_limits<double>::infinity();

    if (x1 < 0.0625 || x1 > 6.1875 || x2 < 0.0625 || x2 > 6.1875)
		return fitnessmalo;
        
	if (x3 < 10 || x3 > 200 || x4 < 10 || x4 > 200)
		return fitnessmalo;
        
	if (-x1 + 0.0193*x3 > 0)
		return fitnessmalo;

	if (-x2 + 0.00954*x3 > 0)
		return fitnessmalo;

	if (-M_PI*x3*x3*x4 - (4.0/3.0)*M_PI*pow(x3, 3) + 1296000 > 0)
		return fitnessmalo;

	if (x4 - 240 > 0)
		return fitnessmalo;

	double f = 0.6224*x1*x3*x4 + 1.7781*x2*x3*x3 +
		3.1661*x1*x1*x4 + 19.84*x1*x1*x3, C = 500;
	return f;
}
*/



void fitnessfunc(double X[numofparticles][numofdims], double fitnesses[numofparticles])
{
    memset(fitnesses, 0, sizeof (double) * numofparticles);
    for(int i = 0; i < numofparticles; i++)
    {
        //double s1 = 0.0, s2 = 0.0;
        //for(int j = 0; j < numofdims; j++)
        //{
            //s1 += X[i][j]*X[i][j];
            //s2 += cos(2*M_PI*X[i][j]);
        //}
        //double r = -20*exp(-0.2*sqrt(s1/numofdims))-exp(s2/numofdims)+20+exp(1);

        //double r=0.0;
        //double a[]= {0.1957, 0.1947, 0.1735, 0.16, 0.0844, 0.0627, 0.0456, 0.0342, 0.0323, 0.0235, 0.0246};
        //double b[]= {0.25, 0.5, 1, 2, 4, 6, 8, 10, 12, 14, 16};
//
        //for(int j=0; j<11; j++){
            //double aux= a[j]-(X[i][0]*(1+X[i][1]*b[j]))/(1+X[i][2]*b[j]+X[i][3]*b[j]);
            //r+= (aux*aux);
        //}

//
        //double &x1 = X[i][0];
        //double &x2 = X[i][1];
        //double &x3 = X[i][2];
        //double &x4 = X[i][3];
//
        //double r = fitness_bat1(x1, x2, x3, x4);


        //double r = -X[i][0] * sin(sqrt(fabs(X[i][0])));

        double x = X[i][0];
        double r = x + 5*sin(3*x) + 8*cos(5*x);
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

    vector<double> fmejor;

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

        for(int i = 0; i < numofparticles; i++)
        {
            if(fitnesses[i] < pbestfits[i])
            {
                pbestfits[i] = fitnesses[i];
                memcpy(pbests[i], X[i], sizeof(double) * numofdims);
            }
        }
        for(int i = 0; i < numofparticles; i++)
        {

            double viejo[numofdims];
            for(int j = 0; j < numofdims; j++){
                viejo[j] = X[i][j];
            }
            
            for(int j = 0; j < numofdims; j++)
            {
                V[i][j] = min(max((w * V[i][j] + rand_01 * c1 * (pbests[i][j] - X[i][j])
                                   + rand_01 * c2 * (gbest[j] - X[i][j])), Vmin[j]), Vmax[j]);
                viejo[j] = min(max((viejo[j] + V[i][j]), Xmin[j]), Xmax[j]);
            }

            //if (!isinf(fitness_bat1(viejo[0], viejo[1], viejo[2], viejo[3]))){
                for(int j = 0; j < numofdims; j++){
                    X[i][j] = viejo[j];
                }
            //}
        }

        fitnessfunc(X, fitnesses);
        minfit = *min_element(fitnesses, fitnesses + numofparticles);
        minfitidx = min_element(fitnesses, fitnesses + numofparticles) - fitnesses;
        if(minfit < *gbestfit)
        {
            *gbestfit = minfit;
            memcpy(gbest, X[minfitidx], sizeof(double) * numofdims);
        }

        fmejor.push_back(*gbestfit); //guardo mejores fitness

        if (fabs(*gbestfit) < 1e-3){
            cout<<"Cortó en la it: "<<t<<" - Sol: "<<*gbestfit<<endl;
            break;
        }

        worsts[t] = *max_element(fitnesses, fitnesses + numofparticles);
        bests[t] = *gbestfit;
        meanfits[t] = mean(fitnesses, numofparticles);
    }

    fmejor.push_back(cant_eval_func);
    crear_dat_vector(fmejor, "fmejor.dat");

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
        xmax[i] = 256;
        xmin[i] = 0;
    }

    //xmax[0] = 6.1875; xmin[0] = 0.0625;
    //xmax[1] = 6.1875; xmin[1] = 0.0625;
    //xmax[2] = 200; xmin[2] = 10;
    //xmax[3] = 200; xmin[3] = 10;
    
    
    int i=0;
    while (i < numofparticles){
        for(int j = 0; j < numofdims; j++)
        {
            initpop[i][j] = rand() % (int)(xmax[j] - xmin[j] + 1);// - xmax[j];
            //cout<<initpop[i][j]<<" ";
        }
        i++;
        //if (!isinf(fitness_bat1(initpop[i][0], initpop[i][1], initpop[i][2],
            //initpop[i][3]))){
            //cout<<"uno válido!"<<endl;
            //i++;
        //}
    }

    cant_eval_func = 0;
    cout<<"listo"<<endl;cout.flush();
    PSO(max_iter, 2, 2, xmin, xmax, initpop, worsts, meanfits, bests, &gbestfit, gbest);

    cout<<"fitness: "<<gbestfit<<endl;
    //cout<<"evaluaciones: "<<cant_eval_func<<endl;
    return 0;
}