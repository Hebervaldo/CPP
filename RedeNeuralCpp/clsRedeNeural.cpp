#include "clsRedeNeural.h"

clsRedeNeural::clsRedeNeural()
{
	mtdIniciarVariaveis();
}

clsRedeNeural::~clsRedeNeural()
{
}

void clsRedeNeural::mtdIniciarVariaveis()
{
	modEpocaDisplay = 1;
	tempoInicial = 0;
	tempoIntermediario = 0;
	tempoFinal = 0;
	TipoSaida = 0;
	TipoErro = 0;
	TipoDeltaS = 0;
	i = 0;
	j = 0;
	k = 0;
	p = 0;
	np = 0;
	op = 0;
	epoca = 0;
	numPadroes = 0;
	numEntrada = 0;
	numEscondida = 0;
	numSaida = 0;
	numIteracoes = 100;
	minimoValorEntrada = 0;
	maximoValorEntrada = 0;
	minimoValorAlvo = 0;
	maximoValorAlvo = 0;	
	Erro = 0;
	eta = 0.05;
	alpha = 0;
	wmax = 1;
	erroLimite = 0.0001;
	primeiraExecucao = 1;
}

int clsRedeNeural::mtdObterComprimentoVetorInteger(int *Vetor)
{
	return (sizeof(Vetor)/sizeof(Vetor[0]));
}

int clsRedeNeural::mtdObterNumeroLinhasMatrizInteger(int **Matriz)
{
	return (sizeof(Matriz)/sizeof(Matriz[0]));
}

int clsRedeNeural::mtdObterNumeroColunasMatrizInteger(int **Matriz)
{
	return (sizeof(Matriz[0])/sizeof(Matriz[0][0]));
}

int clsRedeNeural::mtdObterComprimentoVetorDouble(double *Vetor)
{
	return (sizeof(Vetor)/sizeof(Vetor[0]));
}

int clsRedeNeural::mtdObterNumeroLinhasMatrizDouble(double **Matriz)
{
	return (sizeof(Matriz)/sizeof(Matriz[0]));
}

int clsRedeNeural::mtdObterNumeroColunasMatrizDouble(double **Matriz)
{
	return (sizeof(Matriz[0])/sizeof(Matriz[0][0]));
}

void clsRedeNeural::mtdCriarVetorDinamicoInteger(int **Vetor, int Comprimento)
{
	int *Vetor_ = new int[Comprimento];
	memset(Vetor_, 0, (Comprimento + 1));

	*Vetor = Vetor_;
}

void clsRedeNeural::mtdCriarMatrizDinamicaInteger(int ***Matriz, int Linha, int Coluna)
{
	int **Matriz_ = new int*[Linha];
	memset(Matriz_, 0, (Linha + 1));

	for (int i = 0; i < Linha; i++)
	{
		Matriz_[i] = new int[Coluna];
	}

	*Matriz = Matriz_;
}

void clsRedeNeural::mtdCriarVetorDinamicoDouble(double **Vetor, int Comprimento)
{
	double *Vetor_ = new double[Comprimento];
	memset(Vetor_, 0, (Comprimento + 1));

	*Vetor = Vetor_;
}

void clsRedeNeural::mtdCriarMatrizDinamicaDouble(double ***Matriz, int Linha, int Coluna)
{
	double **Matriz_ = new double*[Linha];
	memset(Matriz_, 0, (Linha + 1));

	for (int i = 0; i < Linha; i++)
	{
		Matriz_[i] = new double[Coluna];
	}

	*Matriz = Matriz_;
}

void clsRedeNeural::mtdObterVetorDinamicoInteger(int *Vetor, int Comprimento)
{
	if(Vetor)
	{
		for(int i = 0; i < Comprimento; i++)
		{
			cout << "Vetor[" << i << "]: " << Vetor[i] << "\n"; 
		}
	}
}

void clsRedeNeural::mtdObterMatrizDinamicaInteger(int **Matriz, int Linha, int Coluna)
{
	if(Matriz)
	{
		for (int i = 0; i < Linha; i++)
		{
			if (Matriz[i]) 
			{
				for (int j = 0; j < Coluna; j++)
				{
					cout << "Matriz[" << i << "][" << j << "]: " << Matriz[i][j] << "\n"; 
				}
			}
		}
	}
}

void clsRedeNeural::mtdObterVetorDinamicoDouble(double *Vetor, int Comprimento)
{
	if(Vetor)
	{
		for(int i = 0; i < Comprimento; i++)
		{
			cout << "Vetor[" << i << "]: " << Vetor[i] << "\n"; 
		}
	}
}

void clsRedeNeural::mtdObterMatrizDinamicaDouble(double **Matriz, int Linha, int Coluna)
{
	if(Matriz)
	{
		for (int i = 0; i < Linha; i++)
		{
			if (Matriz[i])
			{
				for (int j = 0; j < Coluna; j++)
				{
					cout << "Matriz[" << i << "][" << j << "]: " << Matriz[i][j] << "\n"; 
				}
			}
		}
	}
}

void clsRedeNeural::mtdPreencherVetorDinamicoInteger(int *Vetor, int Comprimento, int Conteudo)
{
	if(Vetor)
	{
		for(int i = 0; i < Comprimento; i++)
		{
			Vetor[i] = Conteudo;
		}
	}
}

void clsRedeNeural::mtdPreencherMatrizDinamicaInteger(int **Matriz, int Linha, int Coluna, int Conteudo)
{
	if(Matriz)
	{
		for (int i = 0; i < Linha; i++)
		{
			if (Matriz[i]) 
			{
				for (int j = 0; j < Coluna; j++)
				{
					Matriz[i][j] = Conteudo;
				}
			}
		}
	}
}

void clsRedeNeural::mtdPreencherVetorDinamicoDouble(double *Vetor, int Comprimento, double Conteudo)
{
	if(Vetor)
	{
		for(int i = 0; i < Comprimento; i++)
		{
			Vetor[i] = Conteudo;
		}
	}
}

void clsRedeNeural::mtdPreencherMatrizDinamicaDouble(double **Matriz, int Linha, int Coluna, double Conteudo)
{
	if(Matriz)
	{
		for (int i = 0; i < Linha; i++)
		{
			if (Matriz[i])
			{
				for (int j = 0; j < Coluna; j++)
				{
					Matriz[i][j] = Conteudo;
				}
			}
		}
	}
}

void clsRedeNeural::mtdDestruirVetorDinamicoInteger(int *Vetor)
{
	if(Vetor)
	{
		delete(Vetor);
	}
}

void clsRedeNeural::mtdDestruirMatrizDinamicaInteger(int **Matriz, int Linha)
{
	if(Matriz)
	{
		for (int i = 0; i < Linha; i++)
		{
			if (Matriz[i]) 
			{
				delete(Matriz[i]);
			}
		}
	}
}

void clsRedeNeural::mtdDestruirVetorDinamicoDouble(double *Vetor)
{
	if(Vetor)
	{
		delete(Vetor);
	}
}

void clsRedeNeural::mtdDestruirMatrizDinamicaDouble(double **Matriz, int Linha)
{
	if(Matriz)
	{
		for (int i = 0; i < Linha; i++)
		{
			if (Matriz[i]) 
			{
				delete(Matriz[i]);
			}
		}
	}
}

int clsRedeNeural::mtdGerarArquivoMatriz(char *Arquivo, double ***Matriz, int *coluna, int *linha, int *comprimento, int *minimoValor, int *maximoValor)
{
	int Retorno = 0;
	int intEOF = 0;
	char numero[1000];
	int i = 0;
	int j = 0;
	int enterRepetido = 1;
	int espacoRepetido = 1;
	int pontoRepetido = 0;
	int sinalRepetido = 0;
	int ultimaEntrada = 0;
	int maxcoluna = 0;
	int contador = 0;
	int numeroEspaco = 0;
	char chr = 0;
	double vetnum[100000];
	double **Matriz_;

	fstream MyFile;
	MyFile.open(Arquivo, ios::in);
	intEOF = (int)MyFile.is_open();

	(*coluna) = 0;
	(*linha) = 0;

	if(intEOF)
	{
		while (intEOF)
		{
			if (((chr == '-' | chr == '+' | chr == '.' | chr == ',') & (pontoRepetido == 0 | sinalRepetido == 0)) | (chr >= '0' & chr <= '9'))
			{
				if (chr == ',')
				{
					chr = '.';
				}
				numero[contador++] = chr;
				numero[contador] = 0;
				if ((numero != "-" & numero != "+") & (numero != "." & numero != ","))
				{
					vetnum[numeroEspaco] = atof(numero);
				}
				enterRepetido = 0;
				espacoRepetido = 0;
				if (chr == '-' | chr == '+')
				{
					sinalRepetido++;
				}
				if (chr == '.' | chr == ',')
				{
					pontoRepetido++;
				}
				ultimaEntrada = 1;
			}
			else
			{
				if (!(chr == '-' | chr == '+' | chr == '.' | chr == ','))
				{
					contador = 0;
	
					if (espacoRepetido == 0)
					{
						(*coluna)++;
						numeroEspaco++;
					}
					espacoRepetido++;
	
					if (chr == (char)10 | chr == (char)13)
					{
						if (enterRepetido == 0)
						{
							if (maxcoluna < (*coluna))
							{
								maxcoluna = (*coluna);
							}
							(*coluna) = 0;
							(*linha)++;
						}
						enterRepetido++;
					}
	
					pontoRepetido = 0;
					sinalRepetido = 0;
				}
				else
				{
					enterRepetido = 0;
					espacoRepetido = 0;
					pontoRepetido++;
					sinalRepetido++;
				}
				ultimaEntrada = 0;
			}
			
			MyFile >> std::noskipws >> chr;	
			intEOF = !MyFile.eof();
		}
	
		numeroEspaco++;
		(*linha)++;
		(*coluna) = maxcoluna;
		(*comprimento) = numeroEspaco;
	
		if (ultimaEntrada == 0)
		{
			(*linha)--;
		}

		(*minimoValor) = vetnum[0];
		(*maximoValor) = vetnum[0];
	
		for (i = 0; i < (*comprimento); i++)
		{
			if ((*minimoValor) >= vetnum[i])
			{
				(*minimoValor) = vetnum[i];
			}
			if ((*maximoValor) <= vetnum[i])
			{
				(*maximoValor) = vetnum[i];
			}
		}
	
		// mtdCriarMatrizDinamicaDouble(Matriz, (*linha + 1), (*coluna + 1));
		Matriz_ = new double*[(*linha + 1)];
		memset(Matriz_, 0, (*linha + 1));
		for(i = 0; i < (*linha + 1); i++)
		{
			Matriz_[i] = new double[(*coluna + 1)];
		}

		// mtdPreencherMatrizDinamicaDouble(Matriz, (*linha + 1), (*coluna + 1), ((vetnum[(int)(((i - 1) * (*coluna)) + (j - 1))]) - (*minimoValor)) / ((*maximoValor) - (*minimoValor)));
		for (i = 1; i < (*linha + 1); i++)
		{
			for (j = 1; j < (*coluna + 1); j++)
			{
				Matriz_[i][j] = ((vetnum[(int)(((i - 1) * (*coluna)) + (j - 1))]) - (*minimoValor)) / ((*maximoValor) - (*minimoValor));
			}
		}
		
		Retorno = 1;
		*Matriz = Matriz_;
	}
	
	return Retorno;
}

void clsRedeNeural::mtdGerarVetorMatriz()
{
	mtdCriarVetorDinamicoInteger(&ranpad, numPadroes + 1);
	
	mtdCriarMatrizDinamicaDouble(&SomaEscondida, numPadroes + 1, numEscondida + 1);
	
	mtdCriarMatrizDinamicaDouble(&W12, numEntrada + 1, numEscondida + 1);
	
	mtdCriarMatrizDinamicaDouble(&Escondida, numPadroes + 1, numEscondida + 1);
	
	mtdCriarMatrizDinamicaDouble(&SomaSaida, numPadroes + 1, numSaida + 1);
	
	mtdCriarMatrizDinamicaDouble(&W23, numEscondida + 1, numSaida + 1);
	
	mtdCriarMatrizDinamicaDouble(&Saida, numPadroes + 1, numSaida + 1);
	
	mtdCriarVetorDinamicoDouble(&DeltaS, numSaida + 1);
	
	mtdCriarVetorDinamicoDouble(&somaDWS, numEscondida + 1);
	
	mtdCriarVetorDinamicoDouble(&DeltaE, numEscondida + 1);
	
	mtdCriarMatrizDinamicaDouble(&DeltaW12, numEntrada + 1, numEscondida + 1);
	
	mtdCriarMatrizDinamicaDouble(&DeltaW23, numEscondida + 1, numSaida + 1);
}

void clsRedeNeural::mtdDestruirVetorMatriz()
{
	// int ranpad[NUMEROPADROES+1];
	mtdDestruirVetorDinamicoInteger(ranpad);

	// double entrada[NUMEROPADROES+1][NUMEROENTRADAS+1];
	mtdDestruirMatrizDinamicaDouble(entrada, numPadroes + 1);

	// double target[NUMEROPADROES+1][NUMEROSAIDAS+1];
	mtdDestruirMatrizDinamicaDouble(target, numPadroes + 1);

	// double SomaEscondida[NUMEROPADROES+1][NUMEROESCONDIDA+1];
	mtdDestruirMatrizDinamicaDouble(SomaEscondida, numPadroes + 1);

	// double W12[NUMEROENTRADAS+1][NUMEROESCONDIDA+1];
	mtdDestruirMatrizDinamicaDouble(W12, numEntrada + 1);

	// double Escondida[NUMEROPADROES+1][NUMEROESCONDIDA+1];
	mtdDestruirMatrizDinamicaDouble(Escondida, numPadroes + 1);

	// double SomaSaida[NUMEROPADROES+1][NUMEROSAIDAS+1]; 
	mtdDestruirMatrizDinamicaDouble(SomaSaida, numPadroes + 1);

	// double W23[NUMEROESCONDIDA+1][NUMEROSAIDAS+1]; 
	mtdDestruirMatrizDinamicaDouble(W23, numEscondida + 1);

	// double SAIDA[NUMEROPADROES+1][NUMEROSAIDAS+1];
	mtdDestruirMatrizDinamicaDouble(Saida, numPadroes + 1);

	// double DeltaS[NUMEROSAIDAS+1];
	mtdDestruirVetorDinamicoDouble(DeltaS);

	// double somaDWS[NUMEROESCONDIDA+1];
	mtdDestruirVetorDinamicoDouble(somaDWS);

	// double DeltaE[NUMEROESCONDIDA+1];
	mtdDestruirVetorDinamicoDouble(DeltaE);

	// double DeltaW12[NUMEROENTRADAS+1][NUMEROESCONDIDA+1];
	mtdDestruirMatrizDinamicaDouble(DeltaW12, numEntrada + 1);

	// double DeltaW23[NUMEROESCONDIDA+1][NUMEROSAIDAS+1];
	mtdDestruirMatrizDinamicaDouble(DeltaW23, numEscondida + 1);
}

void clsRedeNeural::mtdObterEntradasTreinamento()
{
	int coluna = 0;
	int linha = 0;
	int comprimento = 0;
	// double entrada[NUMEROPADROES+1][NUMEROENTRADAS+1];
	mtdGerarArquivoMatriz("entradastreinamento.dat", &entrada, &coluna, &linha, &comprimento, &minimoValorEntrada, &maximoValorEntrada);
	numEntrada = coluna;
	numPadroes = linha;
}

void clsRedeNeural::mtdObterEntradasExecucao()
{
	int coluna = 0;
	int linha = 0;
	int comprimento = 0;
	// double entrada[NUMEROPADROES+1][NUMEROENTRADAS+1];
	mtdGerarArquivoMatriz("entradasteste.dat", &entrada, &coluna, &linha, &comprimento, &minimoValorEntrada, &maximoValorEntrada);
	numEntrada = coluna;
	numPadroes = linha;
}

void clsRedeNeural::mtdObterAlvosTreinamento()
{
	int coluna = 0;
	int linha = 0;
	int comprimento = 0;
	// double target[NUMEROPADROES+1][NUMEROSAIDAS+1];
	mtdGerarArquivoMatriz("target.dat", &target, &coluna, &linha, &comprimento, &minimoValorAlvo, &maximoValorAlvo);
	numSaida = coluna;
	numPadroes = linha;
	
	mtdEscreverNumeroColunasAlvos();
}

void clsRedeNeural::mtdZerarAlvosExecucao(int linha)
{
	mtdObterNumeroColunasAlvos();

	int coluna = numSaida;

	// double target[NUMEROPADROES+1][NUMEROSAIDAS+1];
	mtdCriarMatrizDinamicaDouble(&target, linha + 1, coluna + 1);

	mtdPreencherMatrizDinamicaDouble(target, linha + 1, coluna + 1, 0.0);
}

void clsRedeNeural::mtdExportarPesos()
{
	int  m, n;
	fstream MyFile;
	// cfPtr = fopen("pesos.dat", "w");
	MyFile.open("pesos.dat", ios::out);
	
	for (n = 0; n < (numEscondida + 1); n++)
	{
		for (m = 0; m < (numEntrada + 1); m++)
		{
			MyFile << W12[m][n] << "\t";
		}

		MyFile << "\n";
	}

	for (n = 0; n < (numSaida + 1); n++)
	{
		for (m = 0; m < (numEscondida + 1); m++)
		{
			MyFile << W23[m][n] << "\t";
		}

		MyFile << "\n";
	}

	MyFile.close();
}

void clsRedeNeural::mtdIniciarPesos()
{
	int m, n;

	fstream MyFile;
	// cfPtr = fopen("pesos.dat", "r");
	MyFile.open("pesos.dat", ios::in);

	for (n = 0; n < (numEscondida + 1); n++)
	{
		for (m = 0; m < (numEntrada + 1); m++)
		{
			MyFile >> W12[m][n];
		}
	}

	for (n = 0; n < (numSaida + 1); n++)
	{
		for (m = 0; m < (numEscondida + 1); m++)
		{
			MyFile >> W23[m][n];
		}
	}

	MyFile.close();
}

void clsRedeNeural::mtdDefinirModEpocaDisplay()
{
	if (numIteracoes >= 100)
	{
		modEpocaDisplay = (int)(numIteracoes / 100);
	}
	else
	{
		modEpocaDisplay = 1;
	}
}

void clsRedeNeural::mtdObterErroTreinamento()
{
	fstream MyFile;
	// cfPtr = fopen("errotreinamento.dat", "r");
	MyFile.open("errotreinamento.dat", ios::in);

	MyFile >> Erro;

	MyFile.close();
}

void clsRedeNeural::mtdEscreverErroTreinamento()
{
	fstream MyFile;
	// cfPtr = fopen("errotreinamento.dat", "w");
	MyFile.open("errotreinamento.dat", ios::out);

	MyFile << Erro;

	MyFile.close();
}

void clsRedeNeural::mtdObterNumeroNeuronios()
{
	fstream MyFile;
	// cfPtr = fopen("numeroneuronios.dat", "r");
	MyFile.open("numeroneuronios.dat", ios::in);

	MyFile >> numEscondida;

	MyFile.close();
}

void clsRedeNeural::mtdEscreverNumeroNeuronios()
{
	fstream MyFile;
	// cfPtr = fopen("numeroneuronios.dat", "w");
	MyFile.open("numeroneuronios.dat", ios::out);

	MyFile << numEscondida;

	MyFile.close();
}

void clsRedeNeural::mtdObterNumeroColunasAlvos()
{
	if (numSaida <= 0)
	{
		mtdObterAlvosTreinamento();
		
		mtdEscreverNumeroColunasAlvos();
	}
	else
	{
		fstream MyFile;
		// cfPtr = fopen("numerocolunasalvos.dat", "r");
		MyFile.open("numerocolunasalvos.dat", ios::in);
	
		MyFile >> numSaida;
	
		MyFile.close();
	}
}

void clsRedeNeural::mtdEscreverNumeroColunasAlvos()
{
	fstream MyFile;
	// cfPtr = fopen("numerocolunasalvos.dat", "w");
	MyFile.open("numerocolunasalvos.dat", ios::out);

	MyFile << numSaida;

	MyFile.close();
}

void clsRedeNeural::mtdEscreverSaida(int TipoResultado)
{
	fstream MyFile;

	if(TipoResultado == 0)
	{
		// cfPtr = fopen("resultadostreinamento.dat", "w");
		MyFile.open("resultadostreinamento.dat", ios::out);
	}
	else if(TipoResultado == 1)
	{
		// cfPtr = fopen("resultadosteste.dat", "w");
		MyFile.open("resultadosteste.dat", ios::out);
	}

	tempoIntermediario = time(NULL);
	// fprintf(cfPtr, "NETWORK DATA - Epoca %d - Neuronios %d - Iteracoes %d - Erro %lf - Tempo Execucao %.0lf [s].\n\nPat:\t", epoca, numEscondida, numIteracoes, Erro, difftime(tempoIntermediario, tempoInicial)); // Mostra as SAIDAs
	MyFile << "NETWORK DATA - Epoca " << epoca << " - Neuronios " << numEscondida <<  "- Iteracoes " << numIteracoes << " - Erro " << Erro << " - Tempo Execucao " << difftime(tempoIntermediario, tempoInicial) << " [s].\n\nPat:\t";

	for (i = 1; i < (numEntrada + 1); i++)
	{
		MyFile << "Entrada " << i << "\t";
	}

	for (k = 1; k < (numSaida + 1); k++)
	{
		MyFile << "Alvo " << k << "\tSaida " << k << "\t";
	}

	for (p = 1; p < (numPadroes + 1); p++)
	{
		MyFile << "\n" << p << "\t";

		for (i = 1; i < (numEntrada + 1); i++)
		{
			MyFile << entrada[p][i] * (maximoValorEntrada - minimoValorEntrada) + (minimoValorEntrada) << "\t";
		}

		for (k = 1; k < (numSaida + 1); k++)
		{
			MyFile << target[p][k] * (maximoValorEntrada - minimoValorEntrada) + (minimoValorEntrada) << "\t" << Saida[p][k] * (maximoValorAlvo - minimoValorAlvo) + (minimoValorAlvo) << "\t";
		}
	}

	tempoIntermediario = time(NULL);
	// fprintf(stdout, "NETWORK DATA - Epoca %d - Neuronios %d - Iteracoes %d - Erro %lf - Tempo Execucao %.0lf [s].\n\nPat:\t", epoca, numEscondida, numIteracoes, Erro, difftime(tempoIntermediario, tempoInicial)); // Mostra as SAIDAs
	cout << "NETWORK DATA - Epoca " << epoca << " - Neuronios " << numEscondida <<  "- Iteracoes " << numIteracoes << " - Erro " << Erro << " - Tempo Execucao " << difftime(tempoIntermediario, tempoInicial) << " [s].\n\nPat:\t";

	for (i = 1; i < (numEntrada + 1); i++)
	{
		cout << "Entrada " << i << "\t";
	}

	for (k = 1; k < (numSaida + 1); k++)
	{
		cout << "Alvo " << k << "\tSaida " << k << "\t";
	}

	for (p = 1; p < (numPadroes + 1); p++)
	{
		cout << "\n" << p << "\t";
		for (i = 1; i < (numEntrada + 1); i++)
		{
			cout << entrada[p][i] * (maximoValorEntrada - minimoValorEntrada) + (minimoValorEntrada) << "\t";
		}
		for (k = 1; k < (numSaida + 1); k++)
		{
			cout << target[p][k] * (maximoValorEntrada - minimoValorEntrada) + (minimoValorEntrada) << "\t" << Saida[p][k] * (maximoValorAlvo - minimoValorAlvo) + (minimoValorAlvo) << "\t";
		}
	}
	
	cout << "\n\n";

	MyFile.close();
	
	// mtdPausar();
}

int clsRedeNeural::mtdTreinarRedeNeural()
{
	int retorno = 0;

	fstream MyFile;

	mtdDefinirModEpocaDisplay();
	mtdObterEntradasTreinamento();
	mtdObterAlvosTreinamento();
	mtdGerarVetorMatriz();
	
	MyFile.open("erro_TreinamentoRedeNeural.dat", ios::out);

	for (j = 1; j < (numEscondida + 1); j++)
	{
		// Inicializa W12 e DeltaW12
		for (i = 0; i < (numEntrada + 1); i++)
		{
			DeltaW12[i][j] = 0.0;
			W12[i][j] = 2.0 * (rando() - 0.5) * wmax;
		}
	}

	for (k = 1; k < (numSaida + 1); k++)
	{
		// Inicializa W23 e DeltaW23
		for (j = 0; j < (numEscondida + 1); j++)
		{
			DeltaW23[j][k] = 0.0;
			W23[j][k] = 2.0 * (rando() - 0.5) * wmax;
		}
	}

	for (epoca = 1; numIteracoes > 0 ? epoca < (numIteracoes + 1) : 1; epoca++)
	{
		// Faz a iteracao da atualizacao dos pesos
		for (p = 1; p < (numPadroes + 1); p++)
		{
			// Randomiza a ordem dos individuos
			ranpad[p] = p;
		}

		for (p = 1; p < (numPadroes + 1); p++)
		{
			np = (p + rando() * (numPadroes - p + 0));
			op = ranpad[p];
			ranpad[p] = ranpad[np];
			ranpad[np] = op;
		}
		Erro = 0.0;

		for (np = 1; np < (numPadroes + 1); np++)
		{
			// Repete para todos os padroes de treinamento
			p = ranpad[np];

			for (j = 1; j < (numEscondida + 1); j++)
			{
				// Computa as ativacoes da unidade escondida
				SomaEscondida[p][j] = W12[0][j];
				for (i = 1; i < (numEntrada + 1); i++)
				{
					SomaEscondida[p][j] += entrada[p][i] * W12[i][j];
				}
				Escondida[p][j] = 1.0 / (1.0 + exp(-SomaEscondida[p][j]));
			}

			for (k = 1; k < (numSaida + 1); k++)
			{
				// Computa as unidades de ativacao da saida e erros
				SomaSaida[p][k] = W23[0][k];
				for (j = 1; j < (numEscondida + 1); j++)
				{
					SomaSaida[p][k] += Escondida[p][j] * W23[j][k];
				}

				switch (TipoSaida)
				{
				case 0:
					Saida[p][k] = 1.0 / (1.0 + exp(-SomaSaida[p][k])); // Sigmoidal SAIDAs

					break;
				case 1:
					Saida[p][k] = SomaSaida[p][k]; // Linear SAIDAs

					break;
				}

				switch (TipoErro)
				{
				case 0:
					Erro += 0.5 * (target[p][k] - Saida[p][k]) * (target[p][k] - Saida[p][k]); // SSE

					break;
				case 1:
					Erro -= (target[p][k] * log(Saida[p][k]) + (1.0 - target[p][k]) * log(1.0 - Saida[p][k])); // Erro de Entropia Cruzada

					break;
				}

				switch (TipoDeltaS)
				{
				case 0:
					DeltaS[k] = (target[p][k] - Saida[p][k]) * Saida[p][k] * (1.0 - Saida[p][k]); // Sigmoidal SAIDAs, SSE */

					break;
				case 1:
					DeltaS[k] = target[p][k] - Saida[p][k]; // Sigmoidal SAIDAs, Cross-Entropy Erro

					break;
				case 2:
					DeltaS[k] = target[p][k] - Saida[p][k]; // Linear SAIDAs, SSE

					break;
				}
			}

			for (j = 1; j < (numEscondida + 1); j++)
			{
				// Retropropagacao de erros para a camada escondida
				somaDWS[j] = 0.0;
				for (k = 1; k < (numSaida + 1); k++)
				{
					somaDWS[j] += W23[j][k] * DeltaS[k];
				}
				DeltaE[j] = somaDWS[j] * Escondida[p][j] * (1.0 - Escondida[p][j]);
			}

			for (j = 1; j < (numEscondida + 1); j++)
			{
				// Atualiza pesos w12
				DeltaW12[0][j] = eta * DeltaE[j] + alpha * DeltaW12[0][j];
				W12[0][j] += DeltaW12[0][j];
				for (i = 1; i < (numEntrada + 1); i++)
				{
					DeltaW12[i][j] = eta * entrada[p][i] * DeltaE[j] + alpha * DeltaW12[i][j];
					W12[i][j] += DeltaW12[i][j];
				}
			}

			for (k = 1; k < (numSaida + 1); k++)
			{
				// Atualiza pesos W23
				DeltaW23[0][k] = eta * DeltaS[k] + alpha * DeltaW23[0][k];
				W23[0][k] += DeltaW23[0][k];
				for (j = 1; j < (numEscondida + 1); j++)
				{
					DeltaW23[j][k] = eta * Escondida[p][j] * DeltaS[k] + alpha * DeltaW23[j][k];
					W23[j][k] += DeltaW23[j][k];
				}
			}
		}

		if (epoca % modEpocaDisplay == 0 || epoca == numIteracoes)
		{
			tempoIntermediario = time(NULL);
			// fprintf(cfPtr, "NETWORK DATA - Epoca %d - Neuronios %d - Iteracoes %d - Erro %lf - Tempo Execucao %.0lf [s].\n", epoca, numEscondida, numIteracoes, Erro, difftime(tempoIntermediario, tempoInicial)); // Mostra as SAIDAs
			MyFile << "NETWORK DATA - Epoca " << epoca << " - Neuronios " << numEscondida << " - Iteracoes " << numIteracoes << " - Erro " << Erro << " - Tempo Execucao " << difftime(tempoIntermediario, tempoInicial) << " [s].\n"; // Mostra as SAIDAs
			cout << "NETWORK DATA - Epoca " << epoca << " - Neuronios " << numEscondida << " - Iteracoes " << numIteracoes << " - Erro " << Erro << " - Tempo Execucao " << difftime(tempoIntermediario, tempoInicial) << " [s].\n"; // Mostra as SAIDAs
		}

		if (Erro < erroLimite)
		{
			break; // Para o aprendizado quando o erro convergir para o valor descrito
		}
	}

	MyFile.close();

	mtdExportarPesos();
	mtdEscreverErroTreinamento();
	mtdEscreverSaida(0);
	mtdDestruirVetorMatriz();
	retorno = 1;

	return retorno;
}

int clsRedeNeural::mtdExecutarRedeNeural()
{
	int retorno = 0;

	fstream MyFile;

	mtdDefinirModEpocaDisplay();
	mtdObterEntradasExecucao();
	mtdZerarAlvosExecucao(numPadroes);
	mtdGerarVetorMatriz();
	mtdIniciarPesos();

	MyFile.open("erro_ExecucaoRedeNeural.dat", ios::out);

	for (epoca = 1; numIteracoes > 0 ? epoca < (numIteracoes + 1) : 1; epoca++)
	{
		// Faz a iteracao da atualizacao dos pesos
		for (p = 1; p < (numPadroes + 1); p++)
		{
			// Randomiza a ordem dos individuos
			ranpad[p] = p;
		}
		for (p = 1; p < (numPadroes + 1); p++)
		{
			np = (p + rando() * (numPadroes - p + 0));
			op = ranpad[p];
			ranpad[p] = ranpad[np];
			ranpad[np] = op;
		}
		Erro = 0.0;
		for (np = 1; np < (numPadroes + 1); np++)
		{
			// Repete para todos os padroes de treinamento
			p = ranpad[np];
			for (j = 1; j < (numEscondida + 1); j++)
			{
				// Computa as ativacoes da unidade escondida
				SomaEscondida[p][j] = W12[0][j];
				for (i = 1; i < (numEntrada + 1); i++)
				{
					SomaEscondida[p][j] += entrada[p][i] * W12[i][j];
				}
				Escondida[p][j] = 1.0 / (1.0 + exp(-SomaEscondida[p][j]));
			}
			for (k = 1; k < (numSaida + 1); k++)
			{
				// Computa as unidades de ativacao da saida e erros
				SomaSaida[p][k] = W23[0][k];
				for (j = 1; j < (numEscondida + 1); j++)
				{
					SomaSaida[p][k] += Escondida[p][j] * W23[j][k];
				}

				switch (TipoSaida)
				{
				case 0:
					Saida[p][k] = 1.0 / (1.0 + exp(-SomaSaida[p][k])); // Sigmoidal SAIDAs

					break;
				case 1:
					Saida[p][k] = SomaSaida[p][k]; // Linear SAIDAs

					break;
				}

				switch (TipoErro)
				{
				case 0:
					Erro += 0.5 * (target[p][k] - Saida[p][k]) * (target[p][k] - Saida[p][k]); // SSE

					break;
				case 1:
					Erro -= (target[p][k] * log(Saida[p][k]) + (1.0 - target[p][k]) * log(1.0 - Saida[p][k])); // Erro de Entropia Cruzada

					break;
				}

				switch (TipoDeltaS)
				{
				case 0:
					DeltaS[k] = (target[p][k] - Saida[p][k]) * Saida[p][k] * (1.0 - Saida[p][k]); // Sigmoidal SAIDAs, SSE */

					break;
				case 1:
					DeltaS[k] = target[p][k] - Saida[p][k]; // Sigmoidal SAIDAs, Cross-Entropy Erro

					break;
				case 2:
					DeltaS[k] = target[p][k] - Saida[p][k]; // Linear SAIDAs, SSE

					break;
				}
			}
			for (j = 1; j < (numEscondida + 1); j++)
			{
				// Retropropagacao de erros para a camada escondida
				somaDWS[j] = 0.0;
				for (k = 1; k < (numSaida + 1); k++)
				{
					somaDWS[j] += W23[j][k] * DeltaS[k];
				}
				DeltaE[j] = somaDWS[j] * Escondida[p][j] * (1.0 - Escondida[p][j]);
			}
			for (j = 1; j < (numEscondida + 1); j++)
			{
				// Atualiza pesos w12
				DeltaW12[0][j] = eta * DeltaE[j] + alpha * DeltaW12[0][j];
				W12[0][j] += DeltaW12[0][j];
				for (i = 1; i < (numEntrada + 1); i++)
				{
					DeltaW12[i][j] = eta * entrada[p][i] * DeltaE[j] + alpha * DeltaW12[i][j];
					W12[i][j] += DeltaW12[i][j];
				}
			}
			for (k = 1; k < (numSaida + 1); k++)
			{
				// Atualiza pesos W23
				DeltaW23[0][k] = eta * DeltaS[k] + alpha * DeltaW23[0][k];
				W23[0][k] += DeltaW23[0][k];
				for (j = 1; j < (numEscondida + 1); j++)
				{
					DeltaW23[j][k] = eta * Escondida[p][j] * DeltaS[k] + alpha * DeltaW23[j][k];
					W23[j][k] += DeltaW23[j][k];
				}
			}
		}
		
		if (epoca % modEpocaDisplay == 0 || epoca == numIteracoes)
		{
			tempoIntermediario = time(NULL);
			MyFile << "NETWORK DATA - Epoca " << epoca << " - Neuronios " << numEscondida << " - Iteracoes " << numIteracoes << " - Erro " << Erro << " - Tempo Execucao " << difftime(tempoIntermediario, tempoInicial) << " [s].\n"; // Mostra as SAIDAs
			cout << "NETWORK DATA - Epoca " << epoca << " - Neuronios " << numEscondida << " - Iteracoes " << numIteracoes << " - Erro " << Erro << " - Tempo Execucao " << difftime(tempoIntermediario, tempoInicial) << " [s].\n"; // Mostra as SAIDAs
		}
	}
	
	MyFile.close();

	mtdObterErroTreinamento();
	mtdEscreverSaida(1);
	mtdDestruirVetorMatriz();
	retorno = 1;

	return retorno;
}

void clsRedeNeural::mtdPausar()
{
	#if defined(__linux__) // Ou #if __linux__
	    // codigo para linux
		int c = getchar();
		c = getchar();
	#elif _WIN32
    	// codigo para windows
		system("pause");
	#else
	    // codigo para linux
		// int c = getchar();
		// c = getchar();
	#endif
}

void clsRedeNeural::mtdSair()
{
	// system("exit");
	exit(1);
}

void clsRedeNeural::mtdTreinamentoRedeNeural(int Escondida, int Iteracoes, double ErroLimite)
{
	tempoInicial = time(NULL);
	numEscondida = Escondida;
	numIteracoes = Iteracoes;
	erroLimite = ErroLimite;

	if (mtdTreinarRedeNeural() == 1)
	{
		cout << "Rede treinada com sucesso.\n";
	}
	else
	{
		cout << "Ocorreram erros.\n";
	}
	tempoFinal = time(NULL);
	cout << "Tempo decorrido para o treinamento da Rede Neural: " << difftime(tempoFinal, tempoInicial) << " [s].\n";

	// mtdPausar();
}

void clsRedeNeural::mtdExecucaoRedeNeural(int Escondida, int Iteracoes)
{
	tempoInicial = time(NULL);
	numEscondida = Escondida;
	numIteracoes = Iteracoes;

	if (mtdExecutarRedeNeural() == 1)
	{
		printf("Rede executada com sucesso.\n");
	}
	else
	{
		printf("Ocorreram erros.\n");
	}
	tempoFinal = time(NULL);
	cout << "Tempo decorrido para a execucao da Rede Neural: " << difftime(tempoFinal, tempoInicial) << " [s].\n";

	// mtdPausar();
}
