#include <iostream>
#include <fstream>
#include <algorithm>
#include<math.h>
#include "indiceInvertido.h"

using namespace std;

BaseDados::BaseDados() {

	this->coordenadas = hash();
}

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
		nomeDocumentos.push_back(to_string(p));
		inFile.close();
	}
}

bool BaseDados::pertence(string palavra) {
	return (mapa.find(palavra) != mapa.end());
}


map<string, int> BaseDados::frequencia(string palavra) { //calculo do tf
	set<string> arquivos;

	if (this->pertence(palavra));
	{
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




double BaseDados::calcularIdf(string palavra) {
	return log(NUMERO_DOCUMENTOS / numeroArquivo(palavra));;
}

map<int, double> BaseDados::hash() {
	int numeroPalavra = mapa.size();
	map<int, double>aux;
	map<int, double>::iterator iAux = aux.begin();
	vector<string>::iterator i;//iterator referente ao vector com nome dos documentos

	for (auto it = mapa.begin(), int x=1; it != mapa.end(); it++, x++) { // Avanca o map<string,set<string> 
		string palavra = it->first;
		map<string, int> resultado = frequencia(palavra);
		auto passaFrequencia = resultado.begin();
		auto docFrequencia = resultado.begin(); //Mapa (doc,frequencia)
		for (i = nomeDocumentos.begin(); i != nomeDocumentos.end(); i++) {
			int valorVetor = atoi(i->c_str());
			int valorMap = atoi(x->first->c_str());
			if (valorVetor == valorMap) {
				iAux->first = x * numeroPalavra + valorVetor;
				int tf = ocorrenciasArquivo(palavra, *i);
				iAux->second = calcularIdf(palavra) * ((double)* tf);//pegar valor frequencia e botar idf
				passaFrequencia++;
			} else {
				iAux->first = x * numeroPalavra + valorVetor;
				iAux->second = 0;
			}
		}
	}

	return aux;
}

void BaseDados::hash(string pesquisa) {
	int numeroPalavra = mapa.size();
	vector<string> divido;
	vector<string>::iterator vectorI = divido.begin(); //iterator referente ao vector com nome dos documentos
	map<int, double>::iterator coordenadasI;
	string inserir;
	for (int i = 0; pesquisa[i] != '\0'; i++) {
		char aux = pesquisa[i];
		int teste = aux;
		inserir[i] = pesquisa[i];
		if (teste == 32 || aux == '\0') {
			divido.push_back(inserir);
			inserir = "";
		}
	}

	for (map<string,set<string>>::iterator iAux = mapa.begin(), int x=1; iAux != mapa.end(); iAux++, x++) { // Avanca o map<string,set<string> 
		int contem = 0;
		string palavra = iAux->first;
		for (vectorI; vectorI != divido.end(); vectorI++) {
			
			
			if (palavra == *vectorI) {
				contem++;
			}
		}
		if (contem > 0) {
			coordenadas.insert(x * numeroPalavra + 1, calcularIdf(palavra) * ((double)contem));
			coordenadasI->first = x * numeroPalavra + 1;
			coordenadasI->second = calcularIdf(palavra) * ((double)contem);//pegar valor frequencia e botar idf
			
		}

		else {
			coordenadasI->first = x * numeroPalavra + 1;
			coordenadasI->second = 0;
		}

	}
}
string BaseDados::entrada() {
	string aux;
	cout << "Consulta: ";
	cin >> aux;
	return aux;
}

map<double, int> BaseDados::rankingCoss() {
	map<double, int> SIM;
		int numero_palavras = mapa.size() ;
		double Somatorio1, Somatorio2, Somatorio3 = 0;
		vector<string>::iterator i;
		map<int, double>::iterator j;
		for (i = nomeDocumentos.begin(); i != nomeDocumentos.end(); i++) {
			for (int x = 1; x <= numero_palavras; x++) {
				j = coordenadas.find(x * numero_palavras + atoi(i->c_str()));
				double A = j->second;
				j = coordenadas.find(x * numero_palavras + 1);
				double B = j->second;
				Somatorio1 += (A * B);
				Somatorio2 += (A * A);
				Somatorio3 += (B * B);
			}
			double SimDQ = Somatorio1 / (sqrt(Somatorio2) * sqrt(Somatorio3));
			pair<int, double> p(SimDQ,atoi(i->c_str()));
			SIM.insert(p);
		}  
	return SIM;
	}




bool BaseDados::exite(string palavra, string documentos) {
	for (auto it = mapa.find(palavra); *it <= numeroDocumentos; it++) {
		if (documentos == *it)
			return true;
		else
			return false;
	}

}

void BaseDados::imprimirRanking() {
	map<double, int> aux = this->rankingCoss();
	map<double, int>::reverse_iterator it = aux.rbegin();
	cout << "__________________________________________";
	for (int i = 0; i < 20; i++) {
		cout << " | "  << (it->second) << " | " <<endl;
	}
	cout << "___________________________________________";
}









