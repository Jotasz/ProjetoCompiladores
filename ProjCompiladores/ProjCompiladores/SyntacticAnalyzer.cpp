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

	/* Leitura de Cabe�alho */
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
		exit(0);
	}
	
	tokenLido  = getToken(index);
	classeLida = getClass(index); 
	index++;
	if(classeLida.compare("Identificador")){
		cout << "ERRO: "<< linhaLida << "     Depois da palavra-chave program, deve haver um identificador" << endl;
		exit(0);
	}

	tokenLido = getToken(index);
	index++;
	if(tokenLido.compare(";")){
		cout << "ERRO: " << linhaLida << "    Faltando o ;" << endl;
		exit(0);
	}

	index = declaracoes_variaveis(index);
	index = declaracoes_de_subprogramas(index);
	index = comando_composto(index);
	exit(0);
	
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
	
	string tokenLido, classeLida, linhaLida;
	index = lista_de_identificadores(index);

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index); 
	index++;
	if(tokenLido.compare(":")){
		cout <<"ERRO: " << linhaLida << "    Necessario ':' ap�s lista de declaracoes de variaveis" << endl;
		exit(0);
	}

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;

	if(classeLida.compare("Inteiro") && classeLida.compare("Real") && classeLida.compare("Booleano")){
		cout <<"ERRO: " << linhaLida << "   Necessario tipo ap�s lista de variaveis" << endl;
		exit(0);
	}

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;
	if(tokenLido.compare(";")){
		cout <<"ERRO: " << linhaLida << "     Esperado ';' " << endl;
		exit(0);
	}

	index = lista_declaracoes_variaveis_auxiliar(index);
	return index;


}

int SyntacticAnalyzer::lista_declaracoes_variaveis_auxiliar(int index){
	string tokenLido, classeLida, linhaLida;

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;

	if(!classeLida.compare("Inteiro") || !classeLida.compare("Real") || !classeLida.compare("Booleano")){
		linhaLida   = getLinha(index);
		tokenLido   = getToken(index);
		classeLida  = getClass(index);
		index++;
		if(!tokenLido.compare(";")){
			index = lista_declaracoes_variaveis_auxiliar(index);
			return index;
		}else {
			cout <<"ERRO: " << linhaLida << "     Esperado ';' " << endl;
			exit(0);
		}
	}
}

int SyntacticAnalyzer::lista_de_identificadores(int index){
	string tokenLido, classeLida, linhaLida;
	
	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;

	if(classeLida.compare("Identificador")){
		cout << "ERRO: "<< linhaLida << "     Esperado um identificador" << endl;
		exit(0);
	}

	index = lista_de_identificadores_auxiliar(index);
	return index;
}

int SyntacticAnalyzer::lista_de_identificadores_auxiliar(int index){
	string tokenLido, classeLida, linhaLida;
	
	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;
	
	if(!tokenLido.compare(",")){
		linhaLida   = getLinha(index);
		tokenLido   = getToken(index);
		classeLida  = getClass(index);
		index++;
		if(!classeLida.compare("Identificador")){
			index = lista_de_identificadores_auxiliar(index);
			return index;
		}else{
			cout << "ERRO: "<< linhaLida << "     Esperado um identificador" << endl;
			exit(0);
		}
	}
	return index;
}

int SyntacticAnalyzer::tipo(int index){
	string tokenLido, classeLida, linhaLida;

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;

	if(classeLida.compare("Inteiro") && classeLida.compare("Real") && classeLida.compare("Booleano")){
		cout <<"ERRO: " << linhaLida << "   Type expected" << endl;
		exit(0);
	}

	return index;

}

int SyntacticAnalyzer::declaracoes_de_subprogramas(int index){
	string tokenLido, classeLida, linhaLida;

	index = declaracoes_de_subprogramas_auxiliar(index);
	return index;
}

int SyntacticAnalyzer::declaracoes_de_subprogramas_auxiliar(int index){
	string tokenLido, classeLida, linhaLida;
	
	//Tenho que verificar se comeca com procedure
	tokenLido  = getToken(index);
	if(!tokenLido.compare("procedure")){
		index = declaracao_de_subprograma(index);
		tokenLido  = getToken(index);
		classeLida = getClass(index); 
		index++;

		if(tokenLido.compare(";")){
			cout <<"ERRO: " << linhaLida << "     Esperado ';' " << endl;
			exit(0);
		}
		index = declaracoes_de_subprogramas_auxiliar(index);

	}
	return index;
	
}

int SyntacticAnalyzer::declaracao_de_subprograma(int index){
	string tokenLido, classeLida, linhaLida;
	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;
	
	if(tokenLido.compare("procedure")){
		cout <<"ERRO: " << linhaLida << "     Esperado 'procedure' " << endl;
		exit(0);
	}

	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;

	if(classeLida.compare("Identificador")){
		cout <<"ERRO: " << linhaLida << "     Esperado identificador " << endl;
		exit(0);
	}

	index = argumentos(index);
	tokenLido = getToken(index);
	if(tokenLido.compare(";")){
		cout <<"ERRO: " << linhaLida << "     Esperado ';' " << endl;
		exit(0);
	}

	index = declaracoes_variaveis(index);
	index = declaracoes_de_subprogramas(index);
	index = comando_composto(index);

}

int SyntacticAnalyzer::argumentos(int index){
	string tokenLido, classeLida, linhaLida;
	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;
	
	if(!tokenLido.compare("(")){
		index = lista_de_parametros(index);
		linhaLida   = getLinha(index);
		tokenLido   = getToken(index);
		classeLida  = getClass(index);
		index++;

		if(tokenLido.compare(")")){
			cout <<"ERRO: " << linhaLida << "     Esperado ')' " << endl;
			exit(0);
		}
	}else{
		return index;
	}

}

int SyntacticAnalyzer::lista_de_parametros(int index){
	string tokenLido, classeLida, linhaLida;
	index = lista_de_identificadores(index);
	tokenLido = getToken(index);
	if(tokenLido.compare(":")){
		cout <<"ERRO: " << linhaLida << "     Esperado ':' " << endl;
		exit(0);
	}
	index = tipo(index);
	index = lista_de_parametros_auxiliar(index);
	return index;
}

int SyntacticAnalyzer::lista_de_parametros_auxiliar(int index){
	string tokenLido, classeLida, linhaLida;
	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;
	
	if(!tokenLido.compare(";")){
		index = lista_de_identificadores(index);
		
		tokenLido = getToken(index);
		if(tokenLido.compare(":")){
			cout <<"ERRO: " << linhaLida << "     Esperado ':' " << endl;
			exit(0);
		}

		index = tipo(index);
		index = lista_de_parametros_auxiliar(index);
		return index;

	}else{
		return index;
	}
}

int SyntacticAnalyzer::comando_composto(int index){
	string tokenLido, classeLida, linhaLida;
	linhaLida   = getLinha(index);
	tokenLido   = getToken(index);
	classeLida  = getClass(index);
	index++;
	if(tokenLido.compare("begin")){
		cout <<"ERRO: " << linhaLida << "     Esperado 'begin' " << endl;
		exit(0);
	}
	index = comandos_opcionais(index);
	tokenLido = getToken(index);

	if(tokenLido.compare("begin")){
		cout <<"ERRO: " << linhaLida << "     Esperado 'end' " << endl;
		exit(0);
	}
	return index;
}

int SyntacticAnalyzer::comandos_opcionais(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (classeLida.compare("Identificador") && tokenLido.compare("begin") && tokenLido.compare("if") && tokenLido.compare("while")){
		/* Significa que � vazio */
	}

	index = lista_de_comandos(index);
	return index;
}

int SyntacticAnalyzer::lista_de_comandos(int index){
	index = comando(index);
	index = lista_de_comandos_auxiliar(index);
	return index;
}
int SyntacticAnalyzer::lista_de_comandos_auxiliar(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare(";")){
		/* Significa que � vazio */
		return index;
	}

	index++;
	index = comando(index);
	index = lista_de_comandos_auxiliar(index);
	return index;
}

int SyntacticAnalyzer::comando(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (!classeLida.compare("Identificador")){
		/* Significa que � um identificador */
		index++;

		tokenLido = getToken(index);
		classeLida = getClass(index);
		linhaLida = getLinha(index);

		if (tokenLido.compare(":=")){
			/* Significa que � ativa��o de procedimento */
			index = ativacao_de_procedimentos(index);
			return index;
		}

		index++;
		index = expressao(index);
		return index;
	}

	if (!tokenLido.compare("begin")){
		/* Significa que � comando composto */
		index = comando_composto(index);
		return index;
	}

	if (!tokenLido.compare("if")){
		index++;

		index = expressao(index);

		tokenLido = getToken(index);
		classeLida = getClass(index);
		linhaLida = getLinha(index);

		if (tokenLido.compare("then")){
			/* Significa que est� faltando then */
			cout << "ERRO: " << linhaLida << " Comando if exige then ap�s express�o" << endl;
			exit(0);
		}

		index++;
		index = comando(index);
		index = parte_else(index);
		return index;
	}

	if (!tokenLido.compare("else")){
		index++;

		index = expressao(index);

		tokenLido = getToken(index);
		classeLida = getClass(index);
		linhaLida = getLinha(index);

		if (tokenLido.compare("do")){
			/* Significa que est� faltando do */
			cout << "ERRO: " << linhaLida << " Comando while exige do ap�s express�o" << endl;
			exit(0);
		}

		index++;
		index = comando(index);
		return index;
	}

	/* Significa que n�o � um comando */
	cout << "ERRO: " << linhaLida << " Esperado um comando" << endl;
	exit(0);
}

int SyntacticAnalyzer::parte_else(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("else")){
		/* Significa que � vazio */
		return index;
	}

	index++;
	index = comando(index);
	return index;
}

int SyntacticAnalyzer::variavel(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);
	index++;

	if (classeLida.compare("Identificador")){
		/* Significa que N�O � um identificador */
		cout << "ERRO: " << linhaLida << " Esperado um identificador" << endl;
		exit(0);
	}

	return index;
}

int SyntacticAnalyzer::ativacao_de_procedimentos(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);
	index++;

	if (classeLida.compare("Identificador")){
		/* Significa que N�O come�ou com identificador */
		cout << "ERRO: " << linhaLida << " Esperado um identificador" << endl;
		exit(0);
	}

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("(")){
		/* Significa que � um identificador isolado */;
		return index;
	}

	index++;
	index = lista_de_expressoes(index);

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);
	index++;

	if (tokenLido.compare(")")){
		/* Significa que N�O foi fechado */
		cout << "ERRO: " << linhaLida << " Par�ntese aberto e n�o fechado" << endl;
		exit(0);
	}

	return index;
}

int SyntacticAnalyzer::lista_de_expressoes(int index){
	index = expressao(index);
	index = lista_declaracoes_variaveis_auxiliar(index);
	return index;
}

int SyntacticAnalyzer::lista_de_expressoes_auxiliar(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare(",")){
		/* Significa que � vazio */
		return index;
	}

	index++;
	index = expressao(index);
	index = lista_de_expressoes_auxiliar(index);
	return index;
}

int SyntacticAnalyzer::expressao(int index){
	string tokenLido, classeLida, linhaLida;

	index = expressao_simples(index);

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("+") && tokenLido.compare("-") && tokenLido.compare("or")) {
		/* Significa que � uma express�o simples isolada */
		return index;
	}

	index = op_relacional(index);
	index = expressao_simples(index);

	return index;
}

int SyntacticAnalyzer::expressao_simples(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("+") && tokenLido.compare("-")){
		/* Significa que come�a com sinal */
		index = sinal(index);
	}

	index = termo(index);
	index = expressao_simples_auxiliar(index);
	return index;


}

int SyntacticAnalyzer::expressao_simples_auxiliar(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("+") && tokenLido.compare("-") && tokenLido.compare("or")) {
		/* Significa que � vazio */
		return index;
	}

	index = op_aditivo(index);
	index = termo(index);
	index = expressao_simples_auxiliar(index);

	return index;
}

int SyntacticAnalyzer::termo(int index){
	index = fator(index);
	index = termo_auxiliar(index);
	return index;
}

int SyntacticAnalyzer::termo_auxiliar(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);

	if (tokenLido.compare("*") && tokenLido.compare("/") && tokenLido.compare("and")) {
		/* Significa que � vazio */
		return index;
	}

	/* Significa que n�o � vazio. N�o precisa incrementar j� que op_multiplicativo ler� essa mesma linha */
	index = op_multiplicativo(index);
	index = fator(index);
	index = termo_auxiliar(index);
	return index;
}

int SyntacticAnalyzer::fator(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);
	index++;

	if (!classeLida.compare("Identificador")){
		/* Significa que inicia com Identificador */

		tokenLido = getToken(index);
		classeLida = getClass(index);
		linhaLida = getLinha(index);

		if (!tokenLido.compare("(")){
			/* Significa que o par�ntese foi aberto */
			index++;

			index = lista_de_expressoes(index);

			tokenLido = getToken(index);
			classeLida = getClass(index);
			linhaLida = getLinha(index);
			index++;
			if (tokenLido.compare(")")){
				/* Significa que N�O fechou corretamente */
				cout << "ERRO: " << linhaLida << " Par�ntese aberto e n�o fechado" << endl;
				exit(0);
			}

			return index;

		}
		else {
			/* Significa que � um identificador isolado */
			return index;
		}
	}

	if (!classeLida.compare("Inteiro")){
		return index;
	}

	if (!classeLida.compare("Real")){
		return index;
	}

	if (!tokenLido.compare("true")){
		return index;
	}

	if (!tokenLido.compare("false")){
		return index;
	}

	if (!tokenLido.compare("(")){
		index = expressao(index);

		tokenLido = getToken(index);
		classeLida = getClass(index);
		linhaLida = getLinha(index);
		index++;

		if (tokenLido.compare(")")){
			/* Significa que N�O fechou corretamente */
			cout << "ERRO: " << linhaLida << " Par�ntese aberto e n�o fechado" << endl;
			exit(0);
		}

		return index;
	}

	cout << "ERRO: " << linhaLida << " Esperado um fator" << endl;
	exit(0);
}

int SyntacticAnalyzer::sinal(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);
	index++;

	if (tokenLido.compare("+") && tokenLido.compare("-")) {
		/* Significa que n�o � sinal */
		cout << "ERRO: " << linhaLida << " Esperado um sinal + -" << endl;
		exit(0);
	}

	return index;
}

int SyntacticAnalyzer::op_relacional(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);
	index++;

	if (tokenLido.compare("=") && tokenLido.compare("<") && tokenLido.compare(">")
		&& tokenLido.compare("<=") && tokenLido.compare(">=") && tokenLido.compare("<>")) {
		/* Significa que n�o � relacional */
		cout << "ERRO: " << linhaLida << " Esperado um operador relacional = < > <= >= <>" << endl;
		exit(0);
	}

	return index;
}

int SyntacticAnalyzer::op_aditivo(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);
	index++;

	if (tokenLido.compare("+") && tokenLido.compare("-") && tokenLido.compare("or")) {
		/* Significa que n�o � aditivo */
		cout << "ERRO: " << linhaLida << " Esperado um operador aditivo + - or" << endl;
		exit(0);
	}

	return index;
}

int SyntacticAnalyzer::op_multiplicativo(int index){
	string tokenLido, classeLida, linhaLida;

	tokenLido = getToken(index);
	classeLida = getClass(index);
	linhaLida = getLinha(index);
	index++;

	if (tokenLido.compare("*") && tokenLido.compare("/") && tokenLido.compare("and")) {
		/* Significa que n�o � multiplicativo */
		cout << "ERRO: " << linhaLida << " Esperado um operador multiplicativo + - and" << endl;
		exit(0);
	}

	return index;
}