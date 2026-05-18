#include "clsRedeNeural.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void mtdPadrao();

clsRedeNeural objRedeNeural;

void mtdPadrao()
{
	int opcao = 0;

	do
	{
		system("cls || clear");
		cout << "Menu Rede Neural - Escolha uma opcao\n";
		cout << "0. Treinar a Rede Neural\n";
		cout << "1. Executar a Rede Neural\n";
		cout << "2. Sair.\n";

		cin >> opcao;
		system("cls || clear");

		switch (opcao)
		{
			case 0:
				cout << "Digite o numero de neuronios da Rede Neural:\n";
				cin >> objRedeNeural.numEscondida;
				cout << "Digite o numero de iteracoes da Rede Neural:\n";
				cin >> objRedeNeural.numIteracoes;
				cout << "Digite o erro limite: \n";
				cin >> objRedeNeural.erroLimite;
				// printf("Escolha o tipo de Saida: \n");
				// scanf("%d", &TipoSaida);
				// printf("Escolha o tipo de Erro: \n");
				// scanf("%lf", &TipoErro);
				// printf("Escolha o tipo de DeltaS: \n");
				// scanf("%lf", &TipoDeltaS);
	
				objRedeNeural.tempoInicial = time(NULL);
				if (objRedeNeural.mtdTreinarRedeNeural() == 1)
				{
					cout << "Rede treinada com sucesso.\n";
				}
				else
				{
					cout << "Ocorreram erros.\n";
				}
				objRedeNeural.tempoFinal = time(NULL);
				cout << "Tempo decorrido para o treinamento da Rede Neural: " << difftime(objRedeNeural.tempoFinal, objRedeNeural.tempoInicial) << " [s].\n";
				
				objRedeNeural.mtdEscreverNumeroNeuronios();
	
				objRedeNeural.primeiraExecucao = 0;
	
				break;
			case 1:
				objRedeNeural.mtdObterNumeroNeuronios();
				if (objRedeNeural.numEscondida <= 0 && objRedeNeural.primeiraExecucao == 1)
				{
					cout << "Digite o numero de neuronios da Rede Neural:\n";
					cin >> objRedeNeural.numEscondida;
					objRedeNeural.mtdEscreverNumeroNeuronios();
				}
				objRedeNeural.numIteracoes = 1;
				// printf("Escolha o tipo de Saida: \n");
				// scanf("%d", &TipoSaida);
				// printf("Escolha o tipo de Erro: \n");
				// scanf("%lf", &TipoErro);
				// printf("Escolha o tipo de DeltaS: \n");
				// scanf("%lf", &TipoDeltaS);
	
				objRedeNeural.tempoInicial = time(NULL);
				if (objRedeNeural.mtdExecutarRedeNeural() == 1)
				{
					cout << "Rede executada com sucesso.\n";
				}
				else
				{
					cout << "Ocorreram erros.\n";
				}
				objRedeNeural.tempoFinal = time(NULL);
				cout << "Tempo decorrido para a execucao da Rede Neural: " << difftime(objRedeNeural.tempoFinal, objRedeNeural.tempoInicial) << " [s].\n";
				
				objRedeNeural.primeiraExecucao = 0;
	
				break;
			case 2:
				objRedeNeural.mtdSair();
	
				break;
			default:
				cout << "Digite uma opcao valida.\n";
	
				break;
		}

		objRedeNeural.mtdPausar();
	} 
	while (opcao != 2);
}

int main(int argc, char** argv)
{
	switch (argc)
	{
		case 2:
			if (atoi(argv[1]) <= 0)
			{
				objRedeNeural.mtdObterNumeroNeuronios();
			}
			else
			{
				objRedeNeural.numEscondida = atoi(argv[1]);
			}
			objRedeNeural.mtdExecucaoRedeNeural(objRedeNeural.numEscondida, 1);
			objRedeNeural.mtdEscreverNumeroNeuronios();
	
			break;
		case 4:
			objRedeNeural.mtdTreinamentoRedeNeural(atoi(argv[1]), atoi(argv[2]), atof(argv[3]));
			objRedeNeural.mtdEscreverNumeroNeuronios();

			break;
		default:
			mtdPadrao();
	
			break;
	}

	return 0;
}
