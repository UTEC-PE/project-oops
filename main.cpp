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

	cout<<endl<<grafo.density()<<endl;
    grafo.dfs(0);
    cout<<endl;
    grafo.grados();

    return 0;
}
=======
	grafo.leerArchivo("grafo1.txt");
	grafo.print();
	cout << endl;
	// grafo.grado(3);
	//grafo.removerArista(4,3);
	//grafo.removerNodo(3);
	//graph grafoprim = grafo.prim(1);
	//grafoprim.print();
	//graph gkruskal = grafo.kruskal();
	//gkruskal.print();
	//grafo.print();
	return 0;
}
>>>>>>> develop
