#include<iostream>
#include <vector>
#include "herd.h"
using namespace std;

int main (int argc, char *argv[]) {
	pair<double,double> k;
	k.first=-512; k.second=512;
	vector<pair<double,double> > r;
	r.push_back(k); r.push_back(k);
	herd Manada(25,1,r,1.5,5,1,0.002);
	Manada.Optimizar(150);
	return 0;
}

