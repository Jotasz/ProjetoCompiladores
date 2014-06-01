#include <cstring>
#include <iostream>
#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(){
	token = new vector<lexToken>();
	restricted_word = new vector<string>();
	restricted_word->push_back("program");
	restricted_word->push_back("var");
	restricted_word->push_back("integer");
	restricted_word->push_back("real");
	restricted_word->push_back("boolean");
	restricted_word->push_back("procedure");
	restricted_word->push_back("begin");
	restricted_word->push_back("end");
	restricted_word->push_back("if");
	restricted_word->push_back("then");
	restricted_word->push_back("else");
	restricted_word->push_back("while");
	restricted_word->push_back("do");
	restricted_word->push_back("not");
}

LexicalAnalyzer::~LexicalAnalyzer(){
	delete token;
	delete restricted_word;
}

void LexicalAnalyzer::analyze(ifstream *code){
	bool commentary = false;
	char reading[256], tk[256];
	unsigned int counter = 0;
	while (!code->eof()){
		code->getline(reading, 256);
		counter++;
		for (unsigned int i = 0; i < strlen(reading); /*Propositalmente Vazio*/){
			/* Comentário */
			if (reading[i] == '{'){
				commentary = true;
			}
			if (!commentary) {
				/* Símbolos Compostos */
				/* Comando de Atribuição */
				if (reading[i] == ':' && reading[i + 1] == '='){
					tk[0] = reading[i];	tk[1] = reading[i + 1];	tk[2] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Comando de Atribuicao");
					token->push_back(newTok);
					i += 2;
				}
				/* Operadores Relacionais */
				else if (reading[i] == '<' && reading[i + 1] == '='){
					tk[0] = reading[i];	tk[1] = reading[i + 1];	tk[2] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Operador Relacional");
					token->push_back(newTok);
					i += 2;
				}
				else if (reading[i] == '>' && reading[i + 1] == '='){
					tk[0] = reading[i];	tk[1] = reading[i + 1];	tk[2] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Operador Relacional");
					token->push_back(newTok);
					i += 2;
				}
				else if (reading[i] == '<' && reading[i + 1] == '>'){
					tk[0] = reading[i];	tk[1] = reading[i + 1];	tk[2] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Operador Relacional");
					token->push_back(newTok);
					i += 2;
				}
				/* Operadores Aditivos */
				else if (reading[i] == 'o' && reading[i + 1] == 'r'){
					tk[0] = reading[i];	tk[1] = reading[i + 1];	tk[2] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Operador Aditivo");
					token->push_back(newTok);
					i += 2;
				}
				/* Operadores Multiplicativo */
				else if (reading[i] == 'a' && reading[i + 1] == 'n' && reading[i + 2] == 'd' && reading[i + 3] != '_' && !isNumber(reading[i + 3])
					&& !isLetter(reading[i + 3])){
					tk[0] = reading[i];	tk[1] = reading[i + 1];	tk[2] = reading[i + 2]; tk[3] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Operador Multiplicativo");
					token->push_back(newTok);
					i += 3;
				}
				/********************/
				/* Símbolos Simples */
				/* Delimitadores */
				else if (reading[i] == ';' || reading[i] == '.' || reading[i] == ':' || reading[i] == '(' || reading[i] == ')' || reading[i] == ','){
					tk[0] = reading[i]; tk[1] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Delimitador");
					token->push_back(newTok);
					i++;
				}
				/* Operador Relacional */
				else if (reading[i] == '=' || reading[i] == '<' || reading[i] == '>'){
					tk[0] = reading[i]; tk[1] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Operador Relacional");
					token->push_back(newTok);
					i++;
				}
				/* Operador Aditivo */
				else if (reading[i] == '+' || reading[i] == '-'){
					tk[0] = reading[i]; tk[1] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Operador Aditivo");
					token->push_back(newTok);
					i++;
				}
				/* Operador Multiplicativo */
				else if (reading[i] == '*' || reading[i] == '/'){
					tk[0] = reading[i]; tk[1] = '\0';
					string word(tk);
					lexToken newTok(counter, word, "Operador Multiplicativo");
					token->push_back(newTok);
					i++;
				}
				/*************************/
				/* Conjuntos de Símbolos */
				/* Palavra Reservada ou Identificador */
				else if (isLetter(reading[i])){
					bool found = false;
					unsigned int j = 0;
					tk[j] = reading[i++];
					for (j++; isLetter(reading[i]) || isNumber(reading[i]) || reading[i] == '_'; j++){
						tk[j] = reading[i++];
					}
					tk[j] = '\0';
					for (j = 0; j < restricted_word->size(); j++){
						if (!strcmp(tk, restricted_word->at(j).c_str())){
							string word(tk);
							lexToken lex(counter, word, "Palavra reservada");
							token->push_back(lex);
							found = true;
							break;
						}
					}
					if (!found){
						string word(tk);
						lexToken lex(counter, word, "Identificador");
						token->push_back(lex);
					}
				}
				/* Números Inteiros ou Reais */
				else if (isNumber(reading[i])){
					int j = 0;
					tk[j] = reading[i++];
					for (j++; isNumber(reading[i]); j++){
						tk[j] = reading[i++];
					}
					if (reading[i] == '.'){
						tk[j] = reading[i];
						for (j++; isNumber(reading[i]); j++){
							tk[j] = reading[i++];
						}
						tk[j] = '\0';
						string word(tk);
						lexToken lex(counter, word, "Numero real");
						token->push_back(lex);
					}
					else {
						tk[j] = '\0';
						string word(tk);
						lexToken lex(counter, word, "Numero inteiro");
						token->push_back(lex);
					}
				}
				/* Espaço em Branco */
				else if (reading[i] == ' ' || reading[i] == '\t' || reading[i] == '\n'){
					i++;
				}
				else {
					cout << "Simbolo " << reading[i] << " nao reconhecido." << endl;
					i++;
				}
			}
			else {
				if (reading[i] == '}'){
					commentary = false;
				}
				i++;
			}
		}
	}
	if (commentary){
		cout << "Esperado } ao fim de um comentario." << endl;
	}
}

bool LexicalAnalyzer::isLetter(char symbol){
	bool letter = symbol == 'a' || symbol == 'A';
	letter = letter || symbol == 'b' || symbol == 'B';
	letter = letter || symbol == 'c' || symbol == 'C';
	letter = letter || symbol == 'd' || symbol == 'D';
	letter = letter || symbol == 'e' || symbol == 'E';
	letter = letter || symbol == 'f' || symbol == 'F';
	letter = letter || symbol == 'g' || symbol == 'G';
	letter = letter || symbol == 'h' || symbol == 'H';
	letter = letter || symbol == 'i' || symbol == 'I';
	letter = letter || symbol == 'j' || symbol == 'J';
	letter = letter || symbol == 'k' || symbol == 'K';
	letter = letter || symbol == 'l' || symbol == 'L';
	letter = letter || symbol == 'm' || symbol == 'M';
	letter = letter || symbol == 'n' || symbol == 'N';
	letter = letter || symbol == 'o' || symbol == 'O';
	letter = letter || symbol == 'p' || symbol == 'P';
	letter = letter || symbol == 'q' || symbol == 'Q';
	letter = letter || symbol == 'r' || symbol == 'R';
	letter = letter || symbol == 's' || symbol == 'S';
	letter = letter || symbol == 't' || symbol == 'T';
	letter = letter || symbol == 'u' || symbol == 'U';
	letter = letter || symbol == 'v' || symbol == 'V';
	letter = letter || symbol == 'w' || symbol == 'W';
	letter = letter || symbol == 'x' || symbol == 'X';
	letter = letter || symbol == 'y' || symbol == 'Y';
	letter = letter || symbol == 'z' || symbol == 'Z';
	return letter;
}

void LexicalAnalyzer::writeOutput(ofstream *output){
	*output << "Token                         Classificacao";
	*output << "                 Linha" << endl;
	*output << "----------------------------------------------------------------------------------------------------" << endl;
	vector<lexToken>::iterator it;
	for(it = token->begin(); it != token->end(); ++it){
		//*output << it->getName().c_str() << "\t\t\t\t" << it->getClassif().c_str() << "\t\t\t\t" << it->getLine() << endl;
		*output << it->getName().c_str();
		//Aqui tenho que imprimir os espaços
		for(unsigned int i = 0; i < 30 - it->getName().length(); i++){
			*output << " ";
		}
		*output << it->getClassif().c_str();
		for(unsigned int i = 0; i < 30 - it->getClassif().length(); i++){
			*output << " ";
		}
		*output << it->getLine() << endl;
	}
}

bool LexicalAnalyzer::isNumber(char symbol){
	switch (symbol){
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;
	default:
		return false;
	}
}