#ifndef _GNUPLOT_HPP_
#define _GNUPLOT_HPP_

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>

//#ifdef WITH_GNUPLOT

class GNUplot {
public:
	GNUplot() {
		gnuplotpipe = popen("gnuplot","w");
		if (!gnuplotpipe) {
			throw("Gnuplot not found !");
		}
		/*configura gnuplot para que no ponga siempre la ventana del gráfico
		 * arriba de todo en cada graficación, y los nombres de los ejes: */
		fprintf(gnuplotpipe,"%s\n", "set terminal wxt noraise; set xlabel \"Tiempo\";\
		 set ylabel \"eje Y\"; set zlabel \"eje Z\"");
	}
	
	~GNUplot() {
		fprintf(gnuplotpipe,"exit\n");
		pclose(gnuplotpipe);
	}
	
	void operator()(const std::string& command) {
		fprintf(gnuplotpipe,"%s\n",command.c_str());
		fflush(gnuplotpipe);
	}
	
protected:
	FILE *gnuplotpipe;
};

#endif // _GNUPLOT_H_

//#endif // WITH_GNUPLOT
