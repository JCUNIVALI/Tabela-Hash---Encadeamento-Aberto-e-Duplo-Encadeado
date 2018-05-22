// tabela.cpp: Define o ponto de entrada para a aplicação de console.


#include <string>
#include <iostream>
#include "stdafx.h"
#include <fstream>
const int MAX = 1000;
const int TAMSTRING = 6;
#include <time.h>
#include "Dado.h"
#include "EnderecamentoAberto.h"
#include "HashEncadeado.h"

int main()
{	
	cout << "###############Enderecamento Aberto##########################" << endl;
	//EnderecamentoAberto();
	cout << "###############Enderecamento Encadeado#######################" << endl;
	HashEncadeado();
    return 0;
}

