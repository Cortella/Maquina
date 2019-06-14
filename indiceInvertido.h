#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H

const int NUMERO_DOCUMENTOS= 5;
#include <string>
#include <vector>
#include <map>
#include <set>
#include <math.h>

using namespace std;

class BaseDados {
public:
	// Cria um indice invertido vazio
	BaseDados();

	// Insere a palavra e o documento no map de acordo com o indice invertido
	void inserir(string palavra, string documento);

	// Imprime o indice invertido
	void imprimirIndice();

	// Le o documento e retorna o numero de vezes que a palavra ocorre nele
	int ocorrenciasArquivo(string palavra, string documento);

	// Le cada arquivo, trata as palavras e as insere no indice
	void ler_inserir_Arquivos();

	// Retorna se a palavra pertence a algum arquivo
	bool pertence(string palavra);

	// Recebe uma palavra e retorna um mapa com os documentos
	// onde ela aparece e o numero de vezes que ela se repete.
	// Pre-condicao: a palavra deve pertencer a algum arquivo
	map<string, int> frequencia(string palavra);

	//Calcula itf de varias palavras
	double importancia(string pesquisa);

	//Calcula tf de apenas uma palavra
	int calcularTf(string palavra );

	//calcula itf de apenas uma palavra
	double calcularIdf(string palavra);

	//Cria sistema de coordenada Para arquivos existentes
	map<int, double> hash();

	//Insere pesquisa no sistema de coordenadas
	void hash(string palavra);

	//funcao de entrada
	
	string entrada();

	//Ranking Cosseno
	map<int, double> rankingCoss(string busca);

	//Paçavra pertence a doc
	bool exite(string palavra, string documentos);
	
	//imprime ranking
	void imprimirRanking();
	
private:
	map<std::string, set<std::string>> mapa; // Mapa que representa o indice invertido
	std::string palavra; // Palavras dos arquivos
	vector<string> nomeDocumentos;
	map<int, double> coordenadas;
};


#endif  // INDICEINVERTIDO_H


