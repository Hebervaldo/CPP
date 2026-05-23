#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class clsMMQ
{
	public:
		clsMMQ();
        ~clsMMQ();
        double mtdFDPDN(double media, double desvio_padrao, double variavel_aleatoria);
		double mtdFDPDL(double parametro_localizacao, double parametro_escala, double variavel_aleatoria);
		double mtdDFDPDN_DFDPDL(double media, double desvio_padrao, double variavel_aleatoria_FDPDN, double parametro_localizacao, double parametro_escala, double variavel_aleatoria_FDPDL);
		double mtdQFDPDN_DFDPDL(double media, double desvio_padrao, double variavel_aleatoria_FDPDN, double parametro_localizacao, double parametro_escala, double variavel_aleatoria_FDPDL);
		double mtdObterSoma_Parametro_Escala_MMQ(double media, double desvio_padrao, double limite_inferior_variavel_aleatoria_FDPDL, double limite_superior_variavel_aleatoria_FDPDL, double incremento_variavel_aleatoria_FDPDL, double parametro_localizacao, double parametro_escala);
		double mtdVerificarMelhor_Parametro_Escala_MMQ(double limite_inferior_variavel_aleatoria_FDPDL, double limite_superior_variavel_aleatoria_FDPDL, double incremento_variavel_aleatoria_FDPDL, double media, double desvio_padrao, double parametro_localizacao, double parametro_escala_minimo, double parametro_escala_maximo, double incremento_parametro_escala);
		double mtdVerificarMelhor_Parametro_Escala_MMQ_Otimizado(double limite_inferior_variavel_aleatoria_FDPDL, double limite_superior_variavel_aleatoria_FDPDL, double incremento_variavel_aleatoria_FDPDL, double media, double desvio_padrao, double parametro_localizacao, double parametro_escala_minimo, double parametro_escala_maximo, double erro_maximo);
	private:
		const double pi = 3.141592653589793238463;
};
