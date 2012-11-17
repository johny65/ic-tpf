#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>

#define rand_01 ((double)rand() / (double)RAND_MAX)

const int numofdims = 1;
const int numofparticles = 100;
const int max_iter = 10;

using namespace std;

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

        double r = -X[i][0] * sin(sqrt(fabs(X[i][0])));
        
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
            for(int j = 0; j < numofdims; j++)
            {
                V[i][j] = min(max((w * V[i][j] + rand_01 * c1 * (pbests[i][j] - X[i][j])
                                   + rand_01 * c2 * (gbest[j] - X[i][j])), Vmin[j]), Vmax[j]);
                X[i][j] = min(max((X[i][j] + V[i][j]), Xmin[j]), Xmax[j]);
            }
        }

        fitnessfunc(X, fitnesses);
        minfit = *min_element(fitnesses, fitnesses + numofparticles);
        minfitidx = min_element(fitnesses, fitnesses + numofparticles) - fitnesses;
        if(minfit < *gbestfit)
        {
            *gbestfit = minfit;
            memcpy(gbest, X[minfitidx], sizeof(double) * numofdims);
        }

        if (fabs(*gbestfit) < 1e-3){
            cout<<"Cortó en la it: "<<t<<" - Sol: "<<*gbestfit<<endl;
            break;
        }

        worsts[t] = *max_element(fitnesses, fitnesses + numofparticles);
        bests[t] = *gbestfit;
        meanfits[t] = mean(fitnesses, numofparticles);
    }


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
        xmax[i] = 512;
        xmin[i] = -512;
    }
    for(int i = 0; i < numofparticles; i++)
        for(int j = 0; j < numofdims; j++)
        {
            initpop[i][j] = rand() % (100 + 100 + 1) - 100;
        }

    PSO(max_iter, 2, 2, xmin, xmax, initpop, worsts, meanfits, bests, &gbestfit, gbest);

    cout<<"fitness: "<<gbestfit<<endl;
    return 0;
}