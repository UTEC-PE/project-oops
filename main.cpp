#include <iostream>
#include "graph.h"
using namespace std;

int main(int argc, char const *argv[]){
	graph grafo;
	grafo.leerArchivo("grafo1.txt");
	grafo.print();
	cout << endl;
	//grafo.grades(4);
	//grafo.removerArista(4,3);
	//grafo.removerNodo(3);
	//graph grafoprim = grafo.prim(1);
	//grafoprim.print();
	//graph gkruskal = grafo.kruskal();
	//gkruskal.print();
	//grafo.print();
	return 0;
}