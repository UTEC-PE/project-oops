#include <iostream>
#include <thread>
#include <mutex>
#include "graph.h"
#include "aux.h"
using namespace std;

#define NUM_THREADS 2

vector<graph*> graphs;
mutex mtx;

void printA_star(int graph, int inicio,int fin){
	//(grafo.A_Star(inicio,fin)).print();
	//cout<<endl;
	mtx.lock();
	graphs[graph]->A_Star(inicio, fin).print();
	cout<<endl;
	mtx.unlock();
}

int main(int argc, char const *argv[]){
	graph grafo;
	thread threads[NUM_THREADS];

	grafo.leerArchivo("grafo2.txt");
	
	grafo.print();
	cout << endl;
	//graph gbfs = grafo.GreedyBFS(0,1);
	//gbfs.print();
	//graph as = grafo.A_Star(0,4);
	//as.print();

	/*
	graph* test = new graph();
	test->leerArchivo("grafo1.txt");
	graphs.push_back(test);

	threads[0] = thread(printA_star,0,0,8);
	threads[1] = thread(printA_star,0,0,5);
	for(int i = 0; i < NUM_THREADS;i++){
		threads[i].join();
	}*/

	// (grafo.A_Star(8,2)).print();
	// grafo.BellmanFord(0);
	cout<<"******** Floyd Warshall ********"<<endl;
	imprimirMatriz(grafo.FloydWarshall());
	cout<<endl;
	cout<<"********    Dijkstra    ********"<<endl;
	imprimirVector(grafo.Dijkstra(0));
	cout<<endl;
	return 0;
}
