#include "SyntacticAnalyzer.h"
#include <iostream>
#include <string>

using namespace std;

void SyntacticAnalyzer::programa(){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;
	
	tokenLido = getToken();
	linhaLida = getLinha();
	if(!tokenLido.compare("program") == 0){
		cout << "ERRO: " << linhaLida << "O programa precisa iniciar com a palavra-chave program " << endl;
	}
	
	linha = readLn();
	tokenLido  = getToken();
	classeLida = getClasse(); 

	if(!classeLida.compare("Identificador") == 0){
		cout << "ERRO: "<< linhaLida << "Depois da palavra-chave program, deve haver um identificador" << endl;
	}

	linha = readLn();
	tokenLido = getToken();

	if(!tokenLido.compare(";") == 0){
		cout << "ERRO: " << linhaLida << "Faltando o ;" << endl;
	}

	declaracoes_variaveis();
	declaracoes_de_subprogramas();
	comando_composto();
	
}
void SyntacticAnalyzer::declaracoes_variaveis(){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;

	linhaLida = readLn();
	tokenLido = getToken();

	if(tokenLido.compare("var") == 0){
		lista_declaracoes_variaveis();
	}
}
void SyntacticAnalyzer::lista_declaracoes_variaveis(){
	
	string tokenLido, classeLida, linhaLida, linhaBuffer;

	lista_de_identificadores();

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