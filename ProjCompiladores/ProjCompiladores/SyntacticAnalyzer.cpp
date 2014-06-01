#include <cstring>
#include <fstream>
#include <string>
#include "SyntacticAnalyzer.h"
#include <iostream>
using namespace std;

/* Funcoes de Classe */
SyntacticAnalyzer::SyntacticAnalyzer(string filename){
	file = new ifstream(filename);
}
SyntacticAnalyzer::~SyntacticAnalyzer(){
	file->close();
}

/* Funcoes de Leitura */
string SyntacticAnalyzer::getToken(string line){
	unsigned int size = line.length();
	char *reading = new char[size + 1],
		*token;
	strcpy(reading, line.c_str());
	token = strtok(reading, " ");
	string tok(token);
	return tok;
}

string SyntacticAnalyzer::getClass(string line){
	unsigned int size = line.length();
	char *reading = new char[size + 1],
		*token;
	strcpy(reading, line.c_str());
	token = strtok(reading, " ");
	token = strtok(NULL, " ");
	string tok(token);
	return tok;
}

string SyntacticAnalyzer::getLinha(string line){
	unsigned int size = line.length();
	char *reading = new char[size + 1],
		*token;
	strcpy(reading, line.c_str());
	token = strtok(reading, " ");
	token = strtok(NULL, " ");
	token = strtok(NULL, " ");
	string tok(token);
	return tok;
}

string SyntacticAnalyzer::readLine(){
	string line;
	getline(*file, line);
	return line;
}

/* Funcoes de Sintaxe */
void SyntacticAnalyzer::programa(){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;
	
	linhaBuffer = readLine();
	tokenLido = getToken(linhaBuffer);
	linhaLida = getLinha(linhaBuffer);
	if(tokenLido.compare("program")){
		cout << "ERRO: " << linhaLida << "O programa precisa iniciar com a palavra-chave program " << endl;
		return;
	}
	
	linhaBuffer = readLine();
	tokenLido  = getToken(linhaBuffer);
	classeLida = getClass(linhaBuffer); 

	if(classeLida.compare("Identificador")){
		cout << "ERRO: "<< linhaLida << "Depois da palavra-chave program, deve haver um identificador" << endl;
		return;
	}

	linhaBuffer = readLine();
	tokenLido = getToken(linhaBuffer);

	if(tokenLido.compare(";")){
		cout << "ERRO: " << linhaLida << "Faltando o ;" << endl;
		return;
	}

	declaracoes_variaveis();
	declaracoes_de_subprogramas();
	comando_composto();
	
}
void SyntacticAnalyzer::declaracoes_variaveis(){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;

	linhaBuffer = readLine();
	tokenLido = getToken(linhaBuffer);

	if(tokenLido.compare("var") == 0){
		lista_declaracoes_variaveis();
		return;
	}
}
void SyntacticAnalyzer::lista_declaracoes_variaveis(){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;
	lista_de_identificadores();

	linhaBuffer = readLine();

}
void SyntacticAnalyzer::lista_declaracoes_variaveis_auxiliar(){ }
void SyntacticAnalyzer::lista_de_identificadores(){ }
void SyntacticAnalyzer::lista_de_identificadores_auxiliar(){ }
void SyntacticAnalyzer::tipo(){ }
void SyntacticAnalyzer::declaracoes_de_subprogramas(){ }
void SyntacticAnalyzer::declaracoes_de_subprogramas_auxiliar(){ }
void SyntacticAnalyzer::declaracao_de_subprograma(){ }
void SyntacticAnalyzer::argumentos(){ }
void SyntacticAnalyzer::lista_de_parametros(){ }
void SyntacticAnalyzer::lista_de_parametros_auxiliar(){ }
void SyntacticAnalyzer::comando_composto(){ }
void SyntacticAnalyzer::comandos_opcionais(){ }
void SyntacticAnalyzer::lista_de_comandos(){ }
void SyntacticAnalyzer::lista_de_comandos_auxiliar(){ }
void SyntacticAnalyzer::comando(){ }
void SyntacticAnalyzer::parte_else(){ }
void SyntacticAnalyzer::variavel(){ }
void SyntacticAnalyzer::ativacao_de_procedimentos(){ }
void SyntacticAnalyzer::lista_de_expressoes(){ }
void SyntacticAnalyzer::lista_de_expressoes_auxiliar(){ }
void SyntacticAnalyzer::expressao(){ }
void SyntacticAnalyzer::expressao_simples(){ }
void SyntacticAnalyzer::expressao_simples_auxiliar(){ }
void SyntacticAnalyzer::termo(){ }
void SyntacticAnalyzer::termo_auxiliar(){ }
void SyntacticAnalyzer::fator(){ }
void SyntacticAnalyzer::sinal(){ }
void SyntacticAnalyzer::op_relacional(){ }
void SyntacticAnalyzer::op_aditivo(){ }
void SyntacticAnalyzer::op_multiplicativo(){}