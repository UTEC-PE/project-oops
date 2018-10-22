#include <iostream>
#include "graph.h"
using namespace std;

int main(int argc, char const *argv[]){
	graph grafo;
	grafo.leerArchivo("./texto.txt");
	// grafo.print();
	// cout << endl;
	// grafo.removerArista(0,1);
	// grafo.print();

	cout<<endl<<grafo.density()<<endl;
    grafo.dfs(1);
    cout<<endl;
    grafo.grados();

    return 0;
}