#include <iostream>
#include "graph.h"
#include "aux.h"
using namespace std;

int main(int argc, char const *argv[]){
	graph grafo;

	grafo.leerArchivo("grafo3.txt");
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
	//	grafo.DFS(3);
	//	grafo.BFS(4);
	//	grafo.isBipartite();
	//	grafo.grados();
	//	cout<<grafo.isConnected();
	
	cout<<"******** Floyd Warshall ********"<<endl;
	imprimirMatriz(grafo.FloydWarshall());
	cout<<endl;
	cout<<"********    Dijkstra    ********"<<endl;
	imprimirVector(grafo.Dijkstra(0));
	cout<<endl;
	return 0;
}
