/*
 * Project Name:  PCD8544 Nokia 5110 SPI LCD display Library RPI
 * File: main.cpp
 * Description: library test file, "Hello world", basic use case, Software SPI 
 * Author: Gavin Lyons.
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/NOKIA_5110_RPI
 */

// ************ libraries **************
#include <bcm2835.h> // for SPI, GPIO and delays. airspayce.com/mikem/bcm2835/index.html
#include <cmath>
#include <ctime>
#include <iostream> // for std::cout
#include "NOKIA_5110_RPI.hpp" // PCD8544 controller driver
#include <signal.h>

// **************** GPIO ***************
#define RST_LCD 25
#define DC_LCD 24
#define SCLK_LCD 11 // 22
#define SDIN_LCD 10 // 27
#define CS_LCD 8

#define inverse  false // set to true to invert display pixel color
#define contrast 0xBF // default is 0xBF set in LCDinit, Try 0xB1 <-> 0xBF if your display is too dark/dim
#define bias 0x13 // LCD bias mode 1:48: Try 0x12 or 0x13 or 0x14

#define NUMERO_CARACTERES_DISPLAY 69
#define NUMERO_COLUNAS_DISPLAY_LINHA 12
#define TAMANHO_STRING_CHAR	200

char bspd[TAMANHO_STRING_CHAR];

int contador = 0;

NOKIA_5110_RPI myLCD(RST_LCD, DC_LCD, CS_LCD, SDIN_LCD, SCLK_LCD);

void mtdConfigurarDisplayNokia5110(void);
void mtdFinalizarDisplayNokia5110(void);
void mtdFinalizacao(int NSinal);
int mtdObterComprimentoVetorChar(char *VetorChar);
char *mtdObterVetorCharTextoAlinhadoEstatico(char *Texto, int NumeroCaracteresLinha, char Alinhamento);
char *mtdObterVetorCharTextoAlinhadoDinamico(char *Texto, int NumeroCaracteresLinha, char Direcao, int Passo);
char *mtdObterVetorCharTexto(char *Texto, int NumeroCaracteresLinha, char Alinhamento, char Direcao, int Passo);
void mtdGerarDelay(float Intervalo);
void mtdImprimirSaidaLCDNokia5110(char *Texto, char Alinhamento, char Direcao, int Repeticoes, double Intervalo);
void mtdImprimirSaidaLCDNokia5110(char *Linha01, char *Linha02, char *Linha03, char *Linha04, char *Linha05, char Alinhamento, char Direcao, int Repeticoes, double Intervalo);
void mtdImprimirTempoLCDNokia5110(int Repeticoes, double Intervalo);

int main(int argc, char** argv)
{
	char *Mensagem;
	char *Linha02;
	char *Linha03;
	char *Linha04;
	char *Linha05;
	char chrAlinhamento; 
	char chrDirecao; 
	int intRepeticoes = 0;
	double dblIntervalo = 0;

	if(bcm2835_init())
	{
		signal(SIGINT, mtdFinalizacao);

		std::cout << "Error 1201 : Problem with init bcm2835 library\r\n";
	
		mtdConfigurarDisplayNokia5110();
                                                                   
		switch(argc)
		{
			case 1:
				Mensagem = "Digite algum parametro ao chamar o aplicativo.";
				chrAlinhamento = 'd';
				chrDirecao ='a';
				intRepeticoes = -1;
				dblIntervalo = 1;

				mtdImprimirSaidaLCDNokia5110
				(
					Mensagem,
					chrAlinhamento,
					chrDirecao,
					intRepeticoes,
					dblIntervalo
				);

			break;
			case 2:
				switch(argv[1][1])
				{
					case 'r':
						if(argv[1][0] == '-')
						{		
							intRepeticoes = -1;
							dblIntervalo = .1;
							
							mtdImprimirTempoLCDNokia5110
							(
								intRepeticoes,
								dblIntervalo
							);
						}
					break;
					default:
						Mensagem = argv[1];
						chrAlinhamento = 'c';
						chrDirecao ='a';
						intRepeticoes = -1;
						dblIntervalo = 1;
						
						mtdImprimirSaidaLCDNokia5110
						(
							Mensagem,
							chrAlinhamento,
							chrDirecao,
							intRepeticoes,
							dblIntervalo
						);

					break;
				}

			break;
			case 3:
				switch(argv[1][1])
				{
					case 'r':
						if(argv[1][0] == '-')
						{		
							intRepeticoes = atoi(argv[2]);
							dblIntervalo = .1;
							
							mtdImprimirTempoLCDNokia5110
							(
								intRepeticoes,
								dblIntervalo
							);
						}
					break;
					default:
						Mensagem = argv[1];
						chrAlinhamento = argv[2][0];
						chrDirecao ='a';
						intRepeticoes = -1;
						dblIntervalo = 1;
						
						mtdImprimirSaidaLCDNokia5110
						(
							Mensagem,
							chrAlinhamento,
							chrDirecao,
							intRepeticoes,
							dblIntervalo
						);

					break;
				}
				
			break;
			case 4:
				switch(argv[1][1])
				{
					case 'r':
						if(argv[1][0] == '-')
						{		
							intRepeticoes = atoi(argv[2]);
							dblIntervalo = atof(argv[3]);
							
							mtdImprimirTempoLCDNokia5110
							(
								intRepeticoes,
								dblIntervalo
							);
						}
					break;
					default:
						Mensagem = argv[1];
						chrAlinhamento = argv[2][0];
						chrDirecao = argv[3][0];
						intRepeticoes = -1;
						dblIntervalo = 1;
						
						mtdImprimirSaidaLCDNokia5110
						(
							Mensagem,
							chrAlinhamento,
							chrDirecao,
							intRepeticoes,
							dblIntervalo
						);
					break;
				}
				
			break;
			case 5:
				Mensagem = argv[1];
				chrAlinhamento = argv[2][0];
				chrDirecao = argv[3][0];
				intRepeticoes = atoi(argv[4]);
				dblIntervalo = 1;
				
				mtdImprimirSaidaLCDNokia5110
				(
					Mensagem,
					chrAlinhamento,
					chrDirecao,
					intRepeticoes,
					dblIntervalo
				);

			break;
			case 6:
				Mensagem = argv[1];
				Linha02 = " ";
				Linha03 = " ";
				Linha04 = " ";
				Linha05 = " ";
				chrAlinhamento = argv[2][0];
				chrDirecao = argv[3][0];
				intRepeticoes = atoi(argv[4]);
				dblIntervalo = atof(argv[5]);
				
				mtdImprimirSaidaLCDNokia5110
				(
					Mensagem,
					Linha02,
					Linha03,
					Linha04,
					Linha05,
					chrAlinhamento,
					chrDirecao,
					intRepeticoes,
					dblIntervalo
				);

			break;
			case 7:
					switch(argv[1][1])
					{
						case 't':
							if(argv[1][0] == '-')
							{
								Mensagem = argv[2];
								chrAlinhamento = argv[3][0];
								chrDirecao = argv[4][0];
								intRepeticoes = atoi(argv[5]);
								dblIntervalo = atof(argv[6]);
								
								mtdImprimirSaidaLCDNokia5110
								(
									Mensagem,
									chrAlinhamento,
									chrDirecao,
									intRepeticoes,
									dblIntervalo
								);
							}
						
						break;

						default:
							Mensagem = argv[1];
							Linha02 = argv[2];
							Linha03 = " ";
							Linha04 = " ";
							Linha05 = " ";
							chrAlinhamento = argv[3][0];
							chrDirecao = argv[4][0];
							intRepeticoes = atoi(argv[5]);
							dblIntervalo = atof(argv[6]);
							
							mtdImprimirSaidaLCDNokia5110
							(
								Mensagem,
								Linha02,
								Linha03,
								Linha04,
								Linha05,
								chrAlinhamento,
								chrDirecao,
								intRepeticoes,
								dblIntervalo
							);

						break;
					}

			break;
			case 8:
				Mensagem = argv[1];
				Linha02 = argv[2];
				Linha03 = argv[3];
				Linha04 = " ";
				Linha05 = " ";
				chrAlinhamento = argv[4][0];
				chrDirecao = argv[5][0];
				intRepeticoes = atoi(argv[6]);
				dblIntervalo = atof(argv[7]);

				mtdImprimirSaidaLCDNokia5110
				(
					Mensagem,
					Linha02,
					Linha03,
					Linha04,
					Linha05,
					chrAlinhamento,
					chrDirecao,
					intRepeticoes,
					dblIntervalo
				);

			break;
			case 9:
				Mensagem = argv[1];
				Linha02 = argv[2];
				Linha03 = argv[3];
				Linha04 = argv[4];
				Linha05 = " ";
				chrAlinhamento = argv[5][0];
				chrDirecao = argv[6][0];
				intRepeticoes = atoi(argv[7]);
				dblIntervalo = atof(argv[8]);

				mtdImprimirSaidaLCDNokia5110
				(
					Mensagem,
					Linha02,
					Linha03,
					Linha04,
					Linha05,
					chrAlinhamento,
					chrDirecao,
					intRepeticoes,
					dblIntervalo
				);

			break;
			case 10:
				Mensagem = argv[1];
				Linha02 = argv[2];
				Linha03 = argv[3];
				Linha04 = argv[4];
				Linha05 = argv[5];
				chrAlinhamento = argv[6][0];
				chrDirecao = argv[7][0];
				intRepeticoes = atoi(argv[8]);
				dblIntervalo = atof(argv[9]);

				mtdImprimirSaidaLCDNokia5110
				(
					Mensagem,
					Linha02,
					Linha03,
					Linha04,
					Linha05,
					chrAlinhamento,
					chrDirecao,
					intRepeticoes,
					dblIntervalo
				);

			break;
		}

		mtdFinalizarDisplayNokia5110();
	}
	
	return 0;
}

void mtdConfigurarDisplayNokia5110(void)
{
	bcm2835_delay(250);
	std::cout << "Iniciar LCD.\r\n";
	myLCD.LCDBegin(inverse, contrast, bias);
	bcm2835_delay(250);
	myLCD.LCDdisplayClear();
}

void mtdFinalizarDisplayNokia5110(void)
{
	myLCD.LCDPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "Finalizar LCD.\r\n";
}

void mtdFinalizacao(int NSinal)
{
	mtdFinalizarDisplayNokia5110();

	exit(0);
}

int mtdObterComprimentoVetorChar(char *VetorCaractere)
{
	int Retorno = 0;

	while(*VetorCaractere++)
	{
		Retorno++;
	}

	return Retorno;
}

char *mtdObterVetorCharTextoAlinhadoEstatico(char *Texto, int NumeroCaracteresLinha, char Alinhamento) 
{
	char *Retorno;

	int intNumeroCaracteresTexto = 0;
	intNumeroCaracteresTexto = mtdObterComprimentoVetorChar(Texto);

	int intNumeroEspaco = 0;

	char bspe[TAMANHO_STRING_CHAR];

	for(int i = 0; i < TAMANHO_STRING_CHAR; i++)
	{
		bspe[i] = (i <= NumeroCaracteresLinha ? ' ' : '\0');
	}

	int intContador = -1;

	if(intNumeroCaracteresTexto < NumeroCaracteresLinha)
	{
		switch(Alinhamento)
		{
			case 101: // 'e'
				intNumeroEspaco = -1;

			break;
			case 99: // 'c'
				intNumeroEspaco = round((NumeroCaracteresLinha - mtdObterComprimentoVetorChar(Texto)) / 2);

			break;
			case 100: // 'd'
				intNumeroEspaco = round(NumeroCaracteresLinha - mtdObterComprimentoVetorChar(Texto));

			break;
			default:
				intNumeroEspaco = - 1;

			break;
		}

		while(intContador <= intNumeroEspaco)
		{
			bspe[intContador] = (intContador++ < intNumeroEspaco ? ' ' : '\0');
		}
	}

	snprintf(bspd, TAMANHO_STRING_CHAR, "%s%s", bspe, Texto);

	Retorno = bspd;

	return Retorno;
}

char *mtdObterVetorCharTextoAlinhadoDinamico(char *Texto, int NumeroCaracteresLinha, char Direcao, int Passo) 
{
	char *Retorno;

	int intNumeroCaracteresTexto = 0;
	intNumeroCaracteresTexto = mtdObterComprimentoVetorChar(Texto);

	int intContador = 0;
	int intIncremento = -1;
	int intPasso = (Passo % intNumeroCaracteresTexto);

	switch(Direcao)
	{
		case 97: // a
			intIncremento = 0;

			for(int i = 0; i < NumeroCaracteresLinha; i++)
			{
				intContador = (i + intPasso);

				if(intContador >= intNumeroCaracteresTexto)
				{
					intContador = intIncremento++;
				}

				bspd[i] = Texto[intContador];
			}

		break;
		case 114: // r
			intIncremento = intNumeroCaracteresTexto;

			for(int i = 0; i < NumeroCaracteresLinha; i++)
			{
				intContador = (i - intPasso);

				if(intContador < 0)
				{
					intContador = intIncremento + (i - intPasso);
				}

				bspd[i] = Texto[intContador];
			}    

		break;
		default:

		break;
	}

	Retorno = bspd;

	return Retorno;
}

char *mtdObterVetorCharTexto(char *Texto, int NumeroCaracteresLinha, char Alinhamento, char Direcao, int Passo) 
{
	char *Retorno;

	int intNumeroCaracteresTexto = 0;
	intNumeroCaracteresTexto = mtdObterComprimentoVetorChar(Texto);

	int intIncremento = -1;
	int intPasso = (Passo % intNumeroCaracteresTexto);

	if(intNumeroCaracteresTexto <= NumeroCaracteresLinha)
	{
		Retorno = mtdObterVetorCharTextoAlinhadoEstatico(Texto, NumeroCaracteresLinha, Alinhamento);
	}
	else
	{
		Retorno = mtdObterVetorCharTextoAlinhadoDinamico(Texto, NumeroCaracteresLinha, Direcao, Passo);
	}

	Retorno = bspd;

	return Retorno;
}

void mtdTextoAcrescentarCaractere(char *Texto, char Caractere, int NumeroCaracteresLinha, char *Retorno)
{
	int intNumeroCaracteresTexto = 0;
	intNumeroCaracteresTexto = mtdObterComprimentoVetorChar(Texto);

	if(intNumeroCaracteresTexto > NumeroCaracteresLinha)
	{
		snprintf(Retorno, TAMANHO_STRING_CHAR, "%s%c", Texto, Caractere);
	}
	else
	{
		snprintf(Retorno, TAMANHO_STRING_CHAR, "%s", Texto);
	}
}

void mtdGerarDelay(float Intervalo)
{
	if(Intervalo > -1)
	{
		delay(Intervalo * 1000);
	}
	else
	{
		int c = getchar();
	}	
}

void mtdImprimirSaidaLCDNokia5110(char *Texto, char Alinhamento, char Direcao, int Repeticoes, double Intervalo)
{
	char bspl[1][TAMANHO_STRING_CHAR];
	char *Saida;

	int intContador = 0;

	switch(Direcao)
	{
		case 97: // a
			mtdTextoAcrescentarCaractere(Texto, '<', NUMERO_CARACTERES_DISPLAY, bspl[0]);

		break;
		case 114: // r
			mtdTextoAcrescentarCaractere(Texto, '>', NUMERO_CARACTERES_DISPLAY, bspl[0]);

		break;
	}

	myLCD.SetFontNum(LCDFontType_Default);
	myLCD.setTextSize(1);

	while(Repeticoes > -1 ? intContador++ < Repeticoes : 1)
	{
		myLCD.setCursor(5, 5);
		Saida = mtdObterVetorCharTexto(bspl[0], NUMERO_CARACTERES_DISPLAY, Alinhamento, Direcao, contador);
		myLCD.print(Saida);
		std::cout << Saida << std::endl;
		contador++;
		myLCD.LCDdisplayUpdate();
		bcm2835_delay(Intervalo * 1000);
	}
}

void mtdImprimirSaidaLCDNokia5110(char *Linha01, char *Linha02, char *Linha03, char *Linha04, char *Linha05, char Alinhamento, char Direcao, int Repeticoes, double Intervalo)
{
	char bspl[5][TAMANHO_STRING_CHAR];
	char *Saida[5];

	int intContador = 0;

	switch(Direcao)
	{
		case 97: // a
			mtdTextoAcrescentarCaractere(Linha01, '<', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[0]);
			mtdTextoAcrescentarCaractere(Linha02, '<', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[1]);
			mtdTextoAcrescentarCaractere(Linha03, '<', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[2]);
			mtdTextoAcrescentarCaractere(Linha04, '<', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[3]);
			mtdTextoAcrescentarCaractere(Linha05, '<', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[4]);

		break;
		case 114: // r
			mtdTextoAcrescentarCaractere(Linha01, '>', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[0]);
			mtdTextoAcrescentarCaractere(Linha02, '>', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[1]);
			mtdTextoAcrescentarCaractere(Linha03, '>', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[2]);
			mtdTextoAcrescentarCaractere(Linha04, '>', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[3]);
			mtdTextoAcrescentarCaractere(Linha05, '>', NUMERO_COLUNAS_DISPLAY_LINHA, bspl[4]);

		break;
	}

	myLCD.SetFontNum(LCDFontType_Default);
	myLCD.setTextSize(1);

	while(Repeticoes > -1 ? intContador++ < Repeticoes : 1)
	{
		myLCD.setCursor(5, 5);

		for (int i = 0; i < 5; i++)
		{
			Saida[i] = mtdObterVetorCharTexto(bspl[i], NUMERO_COLUNAS_DISPLAY_LINHA, Alinhamento, Direcao, contador);
			myLCD.println(Saida[i]);
			std::cout << "LINHA 05: " << Saida[i] << std::endl;
		}

		contador++;
		myLCD.LCDdisplayUpdate();
		bcm2835_delay(Intervalo * 1000);
	}
}

void mtdImprimirTempoLCDNokia5110(int Repeticoes, double Intervalo)
{
	char bspl[2][TAMANHO_STRING_CHAR];

	int intContador = 0;

	while(Repeticoes > -1 ? intContador++ < Repeticoes : 1)
	{
		std::time_t now = std::time(0);
		
		std::tm *dt = std::localtime(&now);

		snprintf(bspl[0], TAMANHO_STRING_CHAR, "%02d/%02d/%0004d", dt->tm_mday, dt->tm_mon + 1, 1900 + dt->tm_year);
		snprintf(bspl[1], TAMANHO_STRING_CHAR, "%02d:%02d:%02d", dt->tm_hour, dt->tm_min, dt->tm_sec);

		mtdImprimirSaidaLCDNokia5110(" ", bspl[0], " ", bspl[1], " ", 'c', 'a', 1, Intervalo);
	}
}
