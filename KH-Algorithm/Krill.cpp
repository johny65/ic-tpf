#include "Krill.h"
#include <cmath>
using namespace std;

Krill::Krill(Pos inicial, int dni) {
	this->X=inicial;
	this->dim=this->X.size();
	this->id=dni;
}

Krill::~Krill() {
	
}

bool Krill::operator ==(Krill &B){
	if(this->id=B.get_id()) return true;
	else return false;
}
void Krill::update_pos(){
	
}
void Krill::cruzar(){
	
}
void Krill::mutar(){
	
}

Pos Krill::get_pos(){
	return this->X;
}
int Krill::get_id(){
	return this->id;
}

double Krill::distancia(Krill &B){
	double d=0;
	Pos KB=B.get_pos(); ///< Posicion del Krill B
	for(int i=0;i<this->dim;i++) { 
		d+=pow(this->X[i]-KB[i],2);
	}
	return d;
}


