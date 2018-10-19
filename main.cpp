#include <iostream>
#include "graph.h"
using namespace std;

int main(int argc, char const *argv[]){
	graph grafo;
	grafo.leerArchivo("texto.txt");
	grafo.print();
	cout << endl;
	//grafo.removerArista(1,3);
	grafo.removerNodo(4);
	//grafo.prim();
	grafo.print();
	return 0;
}