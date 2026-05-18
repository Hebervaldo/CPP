#ifndef CLSARQUIVOTEXTO_H
#define CLSARQUIVOTEXTO_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

class clsArquivoTexto
{
	public:
		clsArquivoTexto();
		~clsArquivoTexto();
		char *mtdLerArquivoTexto(char *EnderecoArquivo);
		bool mtdEscreverArquivoTexto(char *EnderecoArquivo, char *Texto);
	private:
		char *mtdConverterStringParaVetorChar(string Texto);
};

#endif
