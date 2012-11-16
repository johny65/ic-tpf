#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>
#include "genetic.h"
#include "func.h"

using namespace std;

int main(){

    int maxiter = 1000;

    //GA genetico(10, 13); //f1
    GA genetico(10, 9); //f2
    
    cout<<"Inited\n";
    genetico.setFuncionFitness(fitness2);
    cout<<"Fitness listo\n";
    genetico.setMaximasIteraciones(maxiter);
    //genetico.Elitismo(1);
    cout<<"Ejecutando...";cout.flush();
    //double r = func2(decode(genetico.Ejecutar(), 6, false));

    Individuo ii; ii.cromosoma = genetico.Ejecutar();
    double r = -fitness2(ii);
    //double r = -fitness2(genetico.Ejecutar());
    cout<<"Solución: "<<r<<endl;
    cin.get();
    return 0;
}
