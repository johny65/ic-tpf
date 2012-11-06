#include<iostream>
#include <vector>
#include "herd.h"
using namespace std;

int main (int argc, char *argv[]) {
	pair<double,double> k;
	k.first=-512; k.second=512;
	vector<pair<double,double> > r;
	r.push_back(k); r.push_back(k);
	
	herd Manada(15,1,10,r,1.5);
	Manada.Optimizar();
	return 0;
}

