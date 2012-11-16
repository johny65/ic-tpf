#include<iostream>
#include <vector>
#include "herd.h"
using namespace std;

int main (int argc, char *argv[]) {
	pair<double,double> k;
	k.first=0; k.second=2;
	vector<pair<double,double> > r;
	r.push_back(k); r.push_back(k);
	r.push_back(k); r.push_back(k);
	herd Manada(100,4,r,0.01,0.02,0.01,0.005);
	Manada.Optimizar(50,3);
	
	
	//Para funcion 1d
//	pair<double,double> k;
//	k.first=-512; k.second=512;
//	vector<pair<double,double> > r;
//	r.push_back(k); 
//	herd Manada(15,1,r,0.5,0.3,0.01,0.01);
//	Manada.Optimizar(150);
	
	
	
	
	return 0;
}

