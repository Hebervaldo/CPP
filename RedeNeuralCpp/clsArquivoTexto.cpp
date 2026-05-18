#include "clsArquivoTexto.h"

clsArquivoTexto::clsArquivoTexto()
{
}

clsArquivoTexto::~clsArquivoTexto()
{
}

char *clsArquivoTexto::mtdConverterStringParaVetorChar(string Texto)
{
	char *Retorno = new char[Texto.length() + 1];

	strcpy(Retorno, Texto.c_str());

	return Retorno;
}

char *clsArquivoTexto::mtdLerArquivoTexto(char *EnderecoArquivo)
{
	char *Retorno;
	string str;

	fstream MyFile;

	MyFile.open(EnderecoArquivo, ios::in);
			
	if(MyFile)
	{
		char ch;
		
		while(1)
		{
			MyFile >> ch;
							
			if(MyFile.eof())
			{
				break;
			}
			else
			{
				str += ch;
			}
		}
	}
	else
	{
		cout << "Erro!";
	}

	MyFile.close();
	
	Retorno = mtdConverterStringParaVetorChar(str);
	
	return Retorno;
}

bool clsArquivoTexto::mtdEscreverArquivoTexto(char *EnderecoArquivo, char *Texto)
{
	bool Retorno = false;
	
	fstream MyFile;

	MyFile.open(EnderecoArquivo, ios::out);

	if(MyFile)
	{
		MyFile << Texto;
		MyFile.close();
		
		Retorno = true;
	}
	else
	{
		Retorno = false;
	}

	return Retorno;
}
