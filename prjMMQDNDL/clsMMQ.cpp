#include "clsMMQ.h"

#define DBL_MAX 1.7976931348623158e+308 /* max value */

clsMMQ::clsMMQ()
{
}

clsMMQ::~clsMMQ()
{
}

double clsMMQ::mtdFDPDN(double media, double desvio_padrao, double variavel_aleatoria)
{
	double Retorno = 0;
	
	Retorno = exp((-pow(((variavel_aleatoria - media) / desvio_padrao), 2) / 2)) / (sqrt(2 * pi) * abs(desvio_padrao));
	
	return Retorno;
}

double clsMMQ::mtdFDPDL(double parametro_localizacao, double parametro_escala, double variavel_aleatoria)
{
	double Retorno = 0;
	
	Retorno = pow(cosh((variavel_aleatoria - parametro_localizacao) / (2 * parametro_escala)), -2) / (4 * parametro_escala);
	
	return Retorno;
}

double clsMMQ::mtdDFDPDN_DFDPDL(double media, double desvio_padrao, double variavel_aleatoria_FDPDN, double parametro_localizacao, double parametro_escala, double variavel_aleatoria_FDPDL)
{
	double Retorno = 0;
	
	Retorno = mtdFDPDN(media, desvio_padrao, variavel_aleatoria_FDPDN) - mtdFDPDL(parametro_localizacao, parametro_escala, variavel_aleatoria_FDPDL);
	
	return Retorno;
}

double clsMMQ::mtdQFDPDN_DFDPDL(double media, double desvio_padrao, double variavel_aleatoria_FDPDN, double parametro_localizacao, double parametro_escala, double variavel_aleatoria_FDPDL)
{
	double Retorno = 0;
	
	Retorno = pow(mtdDFDPDN_DFDPDL(media, desvio_padrao, variavel_aleatoria_FDPDN, parametro_localizacao, parametro_escala, variavel_aleatoria_FDPDL), 2);

	return Retorno;
}

double clsMMQ::mtdObterSoma_Parametro_Escala_MMQ(double media, double desvio_padrao, double limite_inferior_variavel_aleatoria_FDPDL, double limite_superior_variavel_aleatoria_FDPDL, double incremento_variavel_aleatoria_FDPDL, double parametro_localizacao, double parametro_escala)
{
	double Retorno = 0;
	double SomaQFDPDN = 0;
	
	for (double j = limite_inferior_variavel_aleatoria_FDPDL; j <= limite_superior_variavel_aleatoria_FDPDL; j += incremento_variavel_aleatoria_FDPDL)
	{
		SomaQFDPDN += clsMMQ::mtdQFDPDN_DFDPDL(media, desvio_padrao, j, parametro_localizacao, parametro_escala, j);
	}
	
	Retorno = SomaQFDPDN;

	return Retorno;
}

double clsMMQ::mtdVerificarMelhor_Parametro_Escala_MMQ(double limite_inferior_variavel_aleatoria_FDPDL, double limite_superior_variavel_aleatoria_FDPDL, double incremento_variavel_aleatoria_FDPDL, double media, double desvio_padrao, double parametro_localizacao, double parametro_escala_minimo, double parametro_escala_maximo, double incremento_parametro_escala)
{
	double Retorno = 0;
	double Melhor_Parametro_Escala_MMQ = 0;
	double SomaQFDPDN = 0;
	double MenorSomaQFDPDN = DBL_MAX;
	
	for (double j = parametro_escala_minimo; j <= parametro_escala_maximo; j += incremento_parametro_escala)
	{
		SomaQFDPDN = clsMMQ::mtdObterSoma_Parametro_Escala_MMQ(media, desvio_padrao, limite_inferior_variavel_aleatoria_FDPDL, limite_superior_variavel_aleatoria_FDPDL, incremento_variavel_aleatoria_FDPDL, parametro_localizacao, j);

		if (SomaQFDPDN < MenorSomaQFDPDN)		
		{
			MenorSomaQFDPDN = SomaQFDPDN;
			Melhor_Parametro_Escala_MMQ = j;
		}
	}
	
	Retorno = Melhor_Parametro_Escala_MMQ;

	return Retorno;
}

double clsMMQ::mtdVerificarMelhor_Parametro_Escala_MMQ_Otimizado(double limite_inferior_variavel_aleatoria_FDPDL, double limite_superior_variavel_aleatoria_FDPDL, double incremento_variavel_aleatoria_FDPDL, double media, double desvio_padrao, double parametro_localizacao, double parametro_escala_minimo, double parametro_escala_maximo, double erro_maximo)
{
	double Retorno = 0;
	
	bool proxima_Melhor_Soma_Posterior = false;
	double Melhor_Parametro_Escala_MMQ = parametro_escala_minimo;
	double SomaQFDPDN = 0;
	double MenorSomaQFDPDN_Anterior = DBL_MAX;
	double MenorSomaQFDPDN = DBL_MAX;
	double MenorSomaQFDPDN_Posterior = DBL_MAX;
	double parametro_escala_minimo_ = parametro_escala_minimo;
	double parametro_escala_maximo_ = parametro_escala_maximo;
	double incremento_parametro_escala = (parametro_escala_maximo - parametro_escala_minimo) * 0.1;
	double incremento_parametro_escala_ = incremento_parametro_escala;
	double erro = DBL_MAX;
	double k = 0.1;

	while(erro >= erro_maximo)
	{
		for (double j = parametro_escala_minimo_; j <= parametro_escala_maximo_; j += incremento_parametro_escala_)
		{
			SomaQFDPDN = clsMMQ::mtdObterSoma_Parametro_Escala_MMQ(media, desvio_padrao, limite_inferior_variavel_aleatoria_FDPDL, limite_superior_variavel_aleatoria_FDPDL, incremento_variavel_aleatoria_FDPDL, parametro_localizacao, j);
	
			// cout << "Soma MMQ: " << SomaQFDPDN << "\t - Parametro: " << j << endl;

			if (SomaQFDPDN < MenorSomaQFDPDN)
			{
				MenorSomaQFDPDN_Anterior = MenorSomaQFDPDN;
				MenorSomaQFDPDN = SomaQFDPDN;
				Melhor_Parametro_Escala_MMQ = j;
				proxima_Melhor_Soma_Posterior = true;
			}
			else
			{
				if(proxima_Melhor_Soma_Posterior)
				{
					MenorSomaQFDPDN_Posterior = SomaQFDPDN;
				}

				proxima_Melhor_Soma_Posterior = false;
			}
		}

		if(MenorSomaQFDPDN_Anterior < MenorSomaQFDPDN_Posterior)
		{
			parametro_escala_minimo_ = Melhor_Parametro_Escala_MMQ - incremento_parametro_escala_;
			parametro_escala_maximo_ = Melhor_Parametro_Escala_MMQ;
			erro = abs(SomaQFDPDN - MenorSomaQFDPDN_Anterior);
		}
		else
		{
			parametro_escala_minimo_ = Melhor_Parametro_Escala_MMQ;
			parametro_escala_maximo_ = Melhor_Parametro_Escala_MMQ + incremento_parametro_escala_;
			erro = abs(MenorSomaQFDPDN_Posterior - SomaQFDPDN);	
		}

		k *= 0.1;
		incremento_parametro_escala_ = Melhor_Parametro_Escala_MMQ * k;
	}
	
	Retorno = Melhor_Parametro_Escala_MMQ;

	return Retorno;
}
