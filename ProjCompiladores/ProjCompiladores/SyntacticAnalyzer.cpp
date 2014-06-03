#include <cstring>
#include <fstream>
#include <string>
#include "SyntacticAnalyzer.h"
#include <iostream>
using namespace std;

/* Funcoes de Classe */
SyntacticAnalyzer::SyntacticAnalyzer(string filename){
	ifstream *file = new ifstream(filename.c_str());
	string leitura;

	/* Leitura de Cabeçalho */
	getline(*file, leitura);
	getline(*file, leitura);
	getline(*file, leitura);

	/* Leitura de Arquivo */
	while (!file->eof()){
		*file >> leitura;
		tokens->push_back(leitura);
		*file >> leitura;
		classes->push_back(leitura);
		*file >> leitura;
		linhas->push_back(leitura);
	}

	file->close();
}

SyntacticAnalyzer::~SyntacticAnalyzer(){
	delete tokens;
	delete classes;
	delete linhas;
}

/* Funcoes de Leitura */
string SyntacticAnalyzer::getToken(int index){
	return tokens->at(index);
}

string SyntacticAnalyzer::getClass(int index){
	return classes->at(index);
}

string SyntacticAnalyzer::getLinha(int index){
	return linhas->at(index);
}

/* Funcoes de Sintaxe */
int SyntacticAnalyzer::programa(int index){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;
	
	tokenLido = getToken(index);
	linhaLida = getLinha(index);
	index++;
	if(tokenLido.compare("program")){
		cout << "ERRO: " << linhaLida << "    O programa precisa iniciar com a palavra-chave program " << endl;
		return index;
	}
	
	tokenLido  = getToken(index);
	classeLida = getClass(index); 
	index++;
	if(classeLida.compare("Identificador")){
		cout << "ERRO: "<< linhaLida << "     Depois da palavra-chave program, deve haver um identificador" << endl;
		return index;
	}

	tokenLido = getToken(index);
	index++;
	if(tokenLido.compare(";")){
		cout << "ERRO: " << linhaLida << "    Faltando o ;" << endl;
		return index;
	}

	index = declaracoes_variaveis(index);
	index = declaracoes_de_subprogramas(index);
	index = comando_composto(index);
	return index;
	
}
int SyntacticAnalyzer::declaracoes_variaveis(int index){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;

	
	tokenLido = getToken(index);
	index++;
	if(!tokenLido.compare("var")){
		index = lista_declaracoes_variaveis(index);
		return index;
	}
	return index;
}
int SyntacticAnalyzer::lista_declaracoes_variaveis(int index){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;
	lista_de_identificadores();

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index); 
	index++;
	if(tokenLido.compare(":")){
		cout <<"ERRO: " << linhaLida << "    Necessario ':' após lista de declaracoes de variaveis" << endl;
		return index;
	}

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;

	if(classeLida.compare("Inteiro") && classeLida.compare("Real") && classeLida.compare("Booleano")){
		cout <<"ERRO: " << linhaLida << "   Necessario tipo após lista de variaveis" << endl;
		return index;
	}

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;
	if(tokenLido.compare(";")){
		cout <<"ERRO: " << linhaLida << "     Esperado ';' " << endl;
		return;
	}

	index = lista_declaracoes_variaveis_auxiliar(index);
	return index;


}
int SyntacticAnalyzer::lista_declaracoes_variaveis_auxiliar(int index){
	
}
int SyntacticAnalyzer::lista_de_identificadores(int index){ }
int SyntacticAnalyzer::lista_de_identificadores_auxiliar(int index){ }
int SyntacticAnalyzer::tipo(int index){ }
int SyntacticAnalyzer::declaracoes_de_subprogramas(int index){ }
int SyntacticAnalyzer::declaracoes_de_subprogramas_auxiliar(int index){ }
int SyntacticAnalyzer::declaracao_de_subprograma(int index){ }
int SyntacticAnalyzer::argumentos(int index){ }
int SyntacticAnalyzer::lista_de_parametros(int index){ }
int SyntacticAnalyzer::lista_de_parametros_auxiliar(int index){ }
int SyntacticAnalyzer::comando_composto(int index){ }
int SyntacticAnalyzer::comandos_opcionais(int index){ }
int SyntacticAnalyzer::lista_de_comandos(int index){ }
int SyntacticAnalyzer::lista_de_comandos_auxiliar(int index){ }
int SyntacticAnalyzer::comando(int index){ }
int SyntacticAnalyzer::parte_else(int index){ }
int SyntacticAnalyzer::variavel(int index){ }
int SyntacticAnalyzer::ativacao_de_procedimentos(int index){ }
int SyntacticAnalyzer::lista_de_expressoes(int index){ }
int SyntacticAnalyzer::lista_de_expressoes_auxiliar(int index){ }
int SyntacticAnalyzer::expressao(int index){ }
int SyntacticAnalyzer::expressao_simples(int index){ }
int SyntacticAnalyzer::expressao_simples_auxiliar(int index){ }
int SyntacticAnalyzer::termo(int index){ }
int SyntacticAnalyzer::termo_auxiliar(int index){ }

int SyntacticAnalyzer::fator(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (!classeLida.compare("Identificador")){
		/* Significa que inicia com Identificador */
		index++;
		tokenLido = getToken(index);
		classeLida = getClass(index);
		linhaLida = getLinha(index);

		if (!tokenLido.compare("(")){
			/* Significa que o parêntese foi aberto */
			index++;
			index = lista_de_expressoes(index);

			tokenLido = getToken(index);
			classeLida = getClass(index);
			linhaLida = getLinha(index);

			if (!tokenLido.compare(")")){
				/* Significa que fechou corretamente */
				index++;
				return index + 1;
			}
			else {
				/* Significa que o parêntese não foi fechado */
				cout << "ERRO: " << linhaLida << "Parêntese aberto e não fechado" << endl;
				exit(0);
			}

		}
		else {
			/* Significa que é um identificador isolado */
			index--;
			return index + 1;
		}
	}

	/* Ainda tem mais coisas */


}

int SyntacticAnalyzer::sinal(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("+") && tokenLido.compare("-")) {
		/* Significa que não é sinal */
		cout << "ERRO: " << linhaLida << "Esperado um sinal + -" << endl;
		exit(0);
	}

	return index + 1;
}

int SyntacticAnalyzer::op_relacional(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("=") && tokenLido.compare("<") && tokenLido.compare(">")
		&& tokenLido.compare("<=") && tokenLido.compare(">=") && tokenLido.compare("<>")) {
		/* Significa que não é relacional */
		cout << "ERRO: " << linhaLida << "Esperado um operador relacional = < > <= >= <>" << endl;
		exit(0);
	}

	return index + 1;
}

int SyntacticAnalyzer::op_aditivo(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("+") && tokenLido.compare("-") && tokenLido.compare("or")) {
		/* Significa que não é aditivo */
		cout << "ERRO: " << linhaLida << "Esperado um operador aditivo + - or" << endl;
		return index;
	}

	return index + 1;
}

int SyntacticAnalyzer::op_multiplicativo(int index){
	string tokenLido, classeLida, linhaLida;
	
	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("*") && tokenLido.compare("/") && tokenLido.compare("and")) {
		/* Significa que não é multiplicativo */
		cout << "ERRO: " << linhaLida << "Esperado um operador multiplicativo + - and" << endl;
		return index;
	}

	return index + 1;
}