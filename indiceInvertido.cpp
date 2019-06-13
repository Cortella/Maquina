#include <iostream>
#include <fstream>
#include <algorithm>
#include<math.h>
#include "indiceInvertido.h"

using namespace std;

BaseDados::BaseDados() {}

void BaseDados::inserir(string palavra, string documento) {
	set<string> docs = { documento };
	pair<map<string, set<string>>::iterator, bool> par;
	par = mapa.insert(pair<string, set<string>>(palavra, docs));
	if (!par.second) {
		mapa[palavra].insert(documento);
	}
}

void BaseDados::imprimirIndice() {
	for (auto it1 = mapa.begin(); it1 != mapa.end(); ++it1) {
		cout << "\nPalavra: " << it1->first;
		cout << "\nValores:";
		for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
			cout << *it2 << endl;
		}
	}
}

int BaseDados::ocorrenciasArquivo(string palavra, string documento) {
	ifstream inFile;
	string palavra_no_arq;
	int contador = 0;

	inFile.open("C:\\Users\\André\\Documents\\UFMG\\PDS II\\" + documento + ".txt");
	if (!inFile) {
		cerr << "O arquivo" + documento + "nao foi aberto";
		exit(1);
	}

	while (inFile >> palavra_no_arq) {
		for (int i = 0; palavra_no_arq[i] != '\0'; i++) { // Loop para eliminar simbolos e letras maiusculas das palavras do arquivo
			palavra_no_arq[i] = tolower(palavra_no_arq[i]);
			palavra_no_arq.erase(remove_if(palavra_no_arq.begin(), palavra_no_arq.end(), [](char c) { return !isalpha(c) && !isdigit(c); }), palavra_no_arq.end());
			
		}
		if (palavra == palavra_no_arq) {
			contador++;
		}
	}
	inFile.close();
	return contador;
}

void BaseDados::ler_inserir_Arquivos() {
	ifstream inFile;
	string palavra;

	for (int p = 1; p <= 5; p++) {
		inFile.open("C:\\Users\\André\\Documents\\UFMG\\PDS II\\" + to_string(p) + ".txt");
		if (!inFile) {
			cerr << "O arquivo" + to_string(p) + "nao foi aberto";
			exit(1);
		}

		while (inFile >> palavra) { 
			for (int i = 0; palavra[i] != '\0'; i++) { // Loop para eliminar simbolos e letras maiusculas das palavras do arquivo
				palavra[i] = tolower(palavra[i]);
				palavra.erase(remove_if(palavra.begin(), palavra.end(), [](char c) { return !isalpha(c) && !isdigit(c); }), palavra.end());
			}
	        inserir(palavra, to_string(p));
		}
		inFile.close();
	}
}

bool BaseDados::pertence(string palavra) {
	return (mapa.find(palavra) != mapa.end());
}

map<string, int> BaseDados::frequencia(string palavra) { //calculo do tf
	set<string> arquivos;
	
	if (this->pertence(palavra)); {
		arquivos = mapa[palavra];
	}

	map<string, int> tf;
	set<string>::iterator it_arqs;
	map<string, int>::iterator it_tf;

	for (it_arqs = arquivos.begin(); it_arqs != arquivos.end(); it_arqs++) {
		tf[*it_arqs] = this->ocorrenciasArquivo(palavra, *it_arqs);
	}

	return tf;
}


double BaseDados::importancia(string palavra) {
	double idf;
	idf= log(NUMERO_DOCUMENTOS / numeroArquivo(palavra));	
	return idf;
}

double BaseDados::calcularIdf(string palavra) {
	return log(NUMERO_DOCUMENTOS / numeroArquivo(palavra));;
}

map<int, double> BaseDados::hash() {
	int numeroPalavra=50000;
	vector<string> = nomeDocumentos;
	map<int, double>aux;
	auto iAux = aux.begin();
	vector<string>::iterator i;//iterator referente ao vector com nome dos documentos

	for (auto it = mapa.begin(), int x ; it != mapa.end();it++,x++){ // Avanca o map<string,set<string> 
		string palavra = it->first;
		map<string, int> resultado = frequencia(it->first);
		auto docFrequencia = resultado.begin(); //Mapa (doc,frequencia)
		for(i = nomeDocumentos.begin(); != nomeDocumentos.end();i++){
			int valorVetor = atoi(i->c_str());
			int valorMap = atoi(x->first->c_str());
		if((valorVetor == valorMap ) {
			iAux->fist = x*numeroPalavra + valorVetor;
			int tf = ocorrenciasArquivo(palavra,*i);
			iAux->second = importancia(palavra)*tf;//pegar valor frequencia e botar idf
		}
		else { 
			iAux->fist = x*numeroPalavra + valorVetor;
				iAux->second = 0;
		}
	}
	
	
	return aux;
}





