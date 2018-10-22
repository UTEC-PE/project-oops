#include <iostream>
#include "graph.h"
using namespace std;

int main(int argc, char const *argv[]){
	graph grafo;
<<<<<<< HEAD
	grafo.leerArchivo("./texto.txt");
	// grafo.print();
	// cout << endl;
	// grafo.removerArista(0,1);
	// grafo.print();
=======
	grafo.leerArchivo("texto.txt");
	grafo.print();
	cout << endl;
	grafo.removerArista(0,1);
	grafo.print();
>>>>>>> b45ba5fec604dbf341df2a0a6b04d03c208582bc

	cout<<endl<<grafo.density()<<endl;
    grafo.dfs(0);
    cout<<endl;
    grafo.grados();

    return 0;
}
