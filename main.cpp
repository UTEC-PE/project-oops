#include <iostream>
#include <thread>
#include <mutex>
#include "graph.h"
using namespace std;

#define NUM_THREADS 4

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

	grafo.leerArchivo("grafo5.txt");

	grafo.print();
	cout << endl;
	//graph gbfs = grafo.GreedyBFS(0,1);
	//gbfs.print();
	//graph as = grafo.A_Star(0,4);
	//as.print();

	
	/*graph* test = new graph();
	test->leerArchivo("grafo1.txt");
	graphs.push_back(test);

	threads[0] = thread(printA_star,0,0,3);
	threads[1] = thread(printA_star,0,0,1);
	threads[2] = thread(printA_star,0,0,2);
	threads[3] = thread(printA_star,0,0,5);
	for(int i = 0; i < NUM_THREADS;i++){
		threads[i].join();
	}*/

	graph a = grafo.A_Star(0,8);
	a.print();
	//grafo.BellmanFord(0);
	return 0;
}
