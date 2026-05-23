#include <iostream>

#include "clsMMQ.h"

using namespace std;

int main (int argc, char *argv[])
{
	clsMMQ objMMQ;
	
	// cout << "mtdVerificarMelhor_Parametro_Escala_MMQ: "  << objMMQ.mtdVerificarMelhor_Parametro_Escala_MMQ(-10, 10, .01, 0.0, 1.0, 0.0, 0.001, 1.0, 0.0001) << endl;
	cout << "mtdVerificarMelhor_Parametro_Escala_MMQ: "  << objMMQ.mtdVerificarMelhor_Parametro_Escala_MMQ_Otimizado(-10, 10, .000001, 0.0, 1.0, 0.0, 0.001, 1.0, 0.0000001) << endl;

	cout << "Press ENTER to continue..." << endl;
	cin.get();

	return 0;
}
