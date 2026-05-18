#ifndef CLSREDENEURAL_H
#define CLSREDENEURAL_H

#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

#define rando() ((double)rand()/RAND_MAX)

class clsRedeNeural
{
	public:
		int tempoInicial;
		int tempoFinal;
		int numEscondida;
		int numIteracoes;

		clsRedeNeural();
		~clsRedeNeural();
		void mtdIniciarVariaveis();
		int mtdObterComprimentoVetorInteger(int *Vetor);
		int mtdObterNumeroLinhasMatrizInteger(int **Matriz);
		int mtdObterNumeroColunasMatrizInteger(int **Matriz);
		int mtdObterComprimentoVetorDouble(double *Vetor);
		int mtdObterNumeroLinhasMatrizDouble(double **Matriz);
		int mtdObterNumeroColunasMatrizDouble(double **Matriz);
		void mtdCriarVetorDinamicoInteger(int **Vetor, int Comprimento);
		void mtdCriarMatrizDinamicaInteger(int ***Matriz, int Linha, int Coluna);
		void mtdCriarVetorDinamicoDouble(double **Vetor, int Comprimento);
		void mtdCriarMatrizDinamicaDouble(double ***Matriz, int Linha, int Coluna);
		void mtdObterVetorDinamicoInteger(int *Vetor, int Comprimento);
		void mtdObterMatrizDinamicaInteger(int **Matriz, int Linha, int Coluna);
		void mtdObterVetorDinamicoDouble(double *Vetor, int Comprimento);
		void mtdObterMatrizDinamicaDouble(double **Matriz, int Linha, int Coluna);
		void mtdPreencherVetorDinamicoInteger(int *Vetor, int Comprimento, int Conteudo);
		void mtdPreencherMatrizDinamicaInteger(int **Matriz, int Linha, int Coluna, int Conteudo);
		void mtdPreencherVetorDinamicoDouble(double *Vetor, int Comprimento, double Conteudo);
		void mtdPreencherMatrizDinamicaDouble(double **Matriz, int Linha, int Coluna, double Conteudo);		void mtdDestruirVetorDinamicoInteger(int *Vetor);
		void mtdDestruirMatrizDinamicaInteger(int **Matriz, int Linha);
		void mtdDestruirVetorDinamicoDouble(double *Vetor);
		void mtdDestruirMatrizDinamicaDouble(double **Matriz, int Linha);
		int mtdGerarArquivoMatriz(char *Arquivo, double ***Matriz, int *coluna, int *linha, int *comprimento, int *minimoValor, int *maximoValor);
		void mtdGerarVetorMatriz();
		void mtdDestruirVetorMatriz();
		void mtdObterEntradasTreinamento();
		void mtdObterEntradasExecucao();
		void mtdObterAlvosTreinamento();
		void mtdZerarAlvosExecucao(int linha);
		void mtdExportarPesos();
		void mtdIniciarPesos();
		void mtdDefinirModEpocaDisplay();
		void mtdObterErroTreinamento();
		void mtdEscreverErroTreinamento();
		void mtdObterNumeroNeuronios();
		void mtdEscreverNumeroNeuronios();
		void mtdObterNumeroColunasAlvos();
		void mtdEscreverNumeroColunasAlvos();
		void mtdEscreverSaida(int TipoResultado);
		int mtdTreinarRedeNeural();
		int mtdExecutarRedeNeural();
		void mtdPausar();
		void mtdSair();
		void mtdTreinamentoRedeNeural(int Escondida, int Iteracoes, double ErroLimite);
		void mtdExecucaoRedeNeural(int Escondida, int Iteracoes);
		
		double erroLimite;
		int primeiraExecucao;		

	protected:
		
	private:
		int modEpocaDisplay;
		// int tempoInicial;
		int tempoIntermediario;
		// int tempoFinal;
		int TipoSaida;
		int TipoErro;
		int TipoDeltaS;
		int i;
		int j;
		int k;
		int p;
		int np;
		int op;
		int epoca;
		int numPadroes;
		int numEntrada;
		// int numEscondida;
		int numSaida;
		// int numIteracoes;
		int minimoValorEntrada;
		int maximoValorEntrada;
		int minimoValorAlvo;
		int maximoValorAlvo;

		// int ranpad[NUMEROPADROES+1];
		int *ranpad;
		// double entrada[NUMEROPADROES+1][NUMEROENTRADAS+1];
		double **entrada;
		// double target[NUMEROPADROES+1][NUMEROSAIDAS+1];
		double **target;
		// double SomaEscondida[NUMEROPADROES+1][NUMEROESCONDIDA+1];
		double **SomaEscondida;
		// double W12[NUMEROENTRADAS+1][NUMEROESCONDIDA+1];
		double **W12;
		// double Escondida[NUMEROPADROES+1][NUMEROESCONDIDA+1];
		double **Escondida;
		// double SomaSaida[NUMEROPADROES+1][NUMEROSAIDAS+1]; 
		double **SomaSaida;
		// double W23[NUMEROESCONDIDA+1][NUMEROSAIDAS+1]; 
		double **W23;
		// double SAIDA[NUMEROPADROES+1][NUMEROSAIDAS+1];
		double **Saida;
		// double DeltaS[NUMEROSAIDAS+1];
		double *DeltaS;
		// double somaDWS[NUMEROESCONDIDA+1];
		double *somaDWS;
		// double DeltaE[NUMEROESCONDIDA+1];
		double *DeltaE;
		// double DeltaW12[NUMEROENTRADAS+1][NUMEROESCONDIDA+1];
		double **DeltaW12;
		// double DeltaW23[NUMEROESCONDIDA+1][NUMEROSAIDAS+1];
		double **DeltaW23;
		
		double Erro;
		double eta;
		double alpha;
		double wmax;
		// double erroLimite;
		// int primeiraExecucao;		
};

#endif
