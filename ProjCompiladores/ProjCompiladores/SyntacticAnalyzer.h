#include <fstream>

using namespace std;

class SyntacticAnalyzer {
public:
	/* Funcoes de Classe */
	SyntacticAnalyzer(string filename);
	~SyntacticAnalyzer();
	/* Funcoes de Leitura */
	string getClass(string line);
	string getToken(string line);
	string getLinha(string line);
	string readLine();
	/* Funcoes de Sintaxe */
	void programa();
	void declaracoes_variaveis();
	void lista_declaracoes_variaveis();
	void lista_declaracoes_variaveis_auxiliar();
	void lista_de_identificadores();
	void lista_de_identificadores_auxiliar();
	void tipo();
	void declaracoes_de_subprogramas();
	void declaracoes_de_subprogramas_auxiliar();
	void declaracao_de_subprograma();
	void argumentos();
	void lista_de_parametros();
	void lista_de_parametros_auxiliar();
	void comando_composto();
	void comandos_opcionais();
	void lista_de_comandos();
	void lista_de_comandos_auxiliar();
	void comando();
	void parte_else();
	void variavel();
	void ativacao_de_procedimentos();
	void lista_de_expressoes();
	void lista_de_expressoes_auxiliar();
	void expressao();
	void expressao_simples();
	void expressao_simples_auxiliar();
	void termo();
	void termo_auxiliar();
	void fator();
	void sinal();
	void op_relacional();
	void op_aditivo();
	void op_multiplicativo();
private:
	ifstream *file;
};