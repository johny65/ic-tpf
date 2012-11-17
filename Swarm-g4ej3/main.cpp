#include<iostream>
#include <vector>
#include "Swarm.h"
using namespace std;

void semilla(int cant_p, int cant_v, double c1, double c2, int solapa,int max_it, int id, bool vis){
	vector<pair<double,double> > rango;
	pair<double,double> a;
	
	switch(id){
		case 1: a.first=-512; a.second=512;
			rango.push_back(a);
			break;
		case 2: a.first=0; a.second=20;
			rango.push_back(a);
			break;
		case 3:
			a.first=-100; a.second=100;
			rango.push_back(a); rango.push_back(a);
			break;
	}
	
	Swarm S(cant_p,cant_v,c1,c2,rango, 0, solapa);
	S.Volar(max_it,id,vis);
}

int main (int argc, char *argv[]) {
	
	semilla(20,5,0.2,0.2,3,2000,3,0);
	return 0;
}

