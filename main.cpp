#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <cctype>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include "indiceInvertido.h"
using namespace std;

int main() {

	string h;
	BaseDados objetoGeral;
	cout << "pesquise uma palavra: " << endl;
	cin >> h;

	objetoGeral.ler_inserir_Arquivos();
	//objetoGeral.imprimirIndice();
	objetoGeral.frequencia(h);
	
	/*
	for (map<string, set<string> >::iterator it = mapa.begin(); it != mapa.end(); it++) {
		cout << "\n\nchave: " << it->first << endl;
	}

	for (set<string>::iterator o = docs.begin(); o != docs.end(); o++) {
		cout << "\n\nvalor: " << *o << endl;
	}
	*/
}
