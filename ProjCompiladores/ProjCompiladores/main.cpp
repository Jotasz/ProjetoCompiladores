#include <fstream>
#include <vector>
#include <list>
#include "LexicalAnalyzer.h"
#include <iostream>

using namespace std;


int main(int n_arg, char** args){
	//Variáveis e Ponteiros
	ifstream *code = NULL;
	ofstream *lexc = NULL;
	//string l_reserv[] = {"program", "var", "integer","real","boolean",
	//	"procedure","begin","end","if", "then","else","while","do","not"};
	char input[256] = "TextLex.txt", output[256] = "TextLex.out";
	//strcmp(input, args[1]);
	//strcmp(output, args[1]);
	//strcat(input, ".txt");
	//strcat(output, ".out");

	//std::list<lexToken> list;

	//Abertura de Arquivos
	//ISSO AQUI TEM ERRO LAU, CONSERTA AÍ. VOU ASSUMIR QUE CODE e LEXC ESTÃO FUNCIONANDO
	//O meu intellisense tá dizendo aqui que o operador "+" não pode ser usado com esses operandos aí
	code = new ifstream(input);
	
	if (code == NULL){
		cout << "Arquivo invalido" << endl;
	}

	lexc = new ofstream(output);
	//Vou fazer a escrita em C, depois se você quiser mudar beleza.
	//FILE *input, *output;
	//input = fopen((char*)(f_name),"r");
	//output = fopen((char*)(e_lexc),"w");
	
	//Análise Léxica
	LexicalAnalyzer *lex = new LexicalAnalyzer();
	lex->analyze(code);
	lex->writeOutput(lexc);

	//Fechamento de Arquivos
	code->close();
	lexc->close();

	//Deletações
	delete lex;
	delete lexc;
	delete code;

	//Retorno
	return 0;
}