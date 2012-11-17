#include <vector>
#include <sstream>
#include <fstream>
#include "utils.h"

using namespace std;

/**
 * @brief Recibe un vector de datos y genera un archivo que puede ser usado
 * por GNUplot para graficar esos datos.
 * @param v Vector de datos a grabar.
 * @param name Es el nombre del archivo a generar.
 */
void crear_dat_vector(vector<double> &v, const char *name)
{
	std::ostringstream ss;
	ofstream out(name, ios::trunc);
	vector<double>::iterator q=v.begin();
	while(q!=v.end()){
		ss << (*q) << "\n";
		q++;
	}
	out<<ss.str();
	out.close();
}
