#include <iostream>
#include "graph.h"
using namespace std;

int main(int argc, char const *argv[]){
	graph grafo;

	grafo.leerArchivo("grafo2.txt");
	grafo.print();
	cout << endl;
	//grafo.removerArista(4,3);
	//grafo.print();
	//grafo.removerNodo(3);
	//grafo.print();
	//graph grafoprim = grafo.prim(1);
	//grafoprim.print();
	//graph gkruskal = grafo.kruskal();
	//gkruskal.print();
	//grafo.print();
<<<<<<< HEAD
	//grafo.DFS(4);
	//grafo.BFS(4);
	//grafo.isBipartite();
	//grafo.grados();
	//cout<<grafo.isConnected()<<endl;
=======
//	grafo.DFS(3);
//	grafo.BFS(4);
//	grafo.isBipartite();
//	grafo.grados();
//	cout<<grafo.isConnected();
//	grafo.FloydWarshall();
>>>>>>> fsocualaya
	return 0;
}
