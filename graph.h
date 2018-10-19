#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include <map>

#include "node.h"
#include "edge.h"

using namespace std;

class Traits {
	public:
		typedef int N;
		typedef int E;
};

template <typename Tr>
class Graph {
    public:
        typedef Graph<Tr> self;
        typedef Node<self> node;
        typedef Edge<self> edge;
        typedef vector<node*> NodeSeq;
        typedef list<edge*> EdgeSeq;
        typedef typename Tr::N N;
        typedef typename Tr::E E;
        typedef typename NodeSeq::iterator NodeIte;
        typedef typename EdgeSeq::iterator EdgeIte;
        
        E nodos,aristas;
        bool directed;

        Graph(){
            nodos = 0;
            aristas = 0;
            directed = 0;
        }

        ~Graph(){
            for (ni = nodes.begin(); ni != nodes.end(); ++ni){
                for (auto i: (*ni)->edges){
                    delete i;
                }
                delete *ni;
            }
        }

        void leerArchivo(string archivo){
            ifstream texto(archivo);
            int numeroNodos,inicio,fin,peso;
            bool direccion;
            float x,y;
            texto >> numeroNodos;
            for (int i = 0; i < numeroNodos; i++){
                texto >> x >> y;
                insertarNodo(i,x,y);
            }
            while (texto >> inicio >> fin >> peso >> direccion){
                insertarArista(inicio,fin,peso,direccion);
            }
                //cout << directed << endl;
            if(direccion == 1){
                directed = 1;
                //cout << directed << endl;
            }
            texto.close();
        }

        node *buscarNodo(N nombre){
            node *buscador = NULL;
            for (int i = 0; i < nodes.size(); ++i){
                if (nombre == nodes[i]->recibirData()){
                    buscador = nodes[i];
                    break;
                }
            }
            return buscador;
        }

        void insertarNodo(N nombre,float x, float y){
            node *buscador = buscarNodo(nombre);
            if(!buscador){
                node *nuevoNodo = new node(nombre,x,y); 
                nodes.push_back(nuevoNodo);
                nodos++;
            }else{
                cout << "El nodo ya existe" << endl;
            }
        }

        void removerNodo(N data){//falta
            node *nodo = buscarNodo(data);
            /*for (ei = nodo->edges.begin(); ei != nodo->edges.end(); ++ei){
                
                removerArista(nodo->recibirData(),(*ei)->nodes[1]->recibirData());
            }*/
        }

        edge *buscarArista(N inicio, N fin){
            node *nodo = buscarNodo(inicio);
            edge *arista = NULL;
            for (auto i: nodo->edges){
                if (isDirected() == 1 && i->nodes[1]->recibirData() == fin){
                    arista = i;
                    break;
                }else if (isDirected() == 0 && (i->nodes[0]->recibirData() == fin || i->nodes[1]->recibirData() == fin)){
                    arista = i;
                    break;
                }
            }
            return arista;
        }

        void insertarArista(N nodoInicial,N nodoFinal,N peso,bool direccion){
            node *buscador1 = buscarNodo(nodoInicial);
            node *buscador2 = buscarNodo(nodoFinal);
            if (buscador1 && buscador2){
                if (isDirected() == 0){
                    if (buscarArista(buscador1->recibirData(),buscador2->recibirData()) || buscarArista(buscador2->recibirData(),buscador1->recibirData())){
                        throw "Arista existente";
                    }
                    edge *nuevaArista = new edge(buscador1,buscador2,peso,direccion);
                    buscador1->edges.push_back(nuevaArista);
                    edge *nuevaArista2 = new edge(buscador2,buscador1,peso,direccion);
                    buscador2->edges.push_back(nuevaArista2);
                }else{
                    if (buscarArista(buscador1->recibirData(),buscador2->recibirData())){
                        throw "Arista existente";
                    }
                    edge *nuevaArista = new edge(buscador1,buscador2,peso,direccion);
                    buscador1->edges.push_back(nuevaArista);
                }
                aristas++;                
            }else{
                cout << "Uno o más nodos no existentes" << endl;
            }
        }

        void removerArista(N inicio,N fin){
            node *nodo1 = buscarNodo(inicio);
            node *nodo2 = buscarNodo(fin);
            bool x = 1;
            for (ei = nodo1->edges.begin();ei!=nodo1->edges.end();ei++){
                //cout<<"for"<<endl;
                if ((*ei)->nodes[1]->recibirData() == nodo2->recibirData()){
                    //cout<<(*ei)->recibirData()<<endl;
                    if ((*ei)->recibirDir() == 0){
                        x = 0;
                    }
                    nodo1->edges.erase(ei);
                    //delete *ei;
                    break;
                }
            }
            if (x == 0){
                for (ei=nodo2->edges.begin();ei!=nodo2->edges.end();ei++){
                    //cout<<(*ei)->nodes[0]->recibirData()<<" "   <<nodo1->recibirData()<<endl;
                    if ((*ei)->nodes[1]->recibirData() == nodo1->recibirData()){
                        //cout<<(*ei)->recibirData()<<endl;
                        nodo2->edges.erase(ei);
                        //delete *ei;
                        break;
                    }
                }    
            }
            aristas--;
        }

        void print(){
            for (ni = nodes.begin(); ni != nodes.end(); ni++){
                cout << (*ni)->recibirData() << "-> ";
                for (auto i: (*ni)->edges){
                    if (i->nodes[0]->recibirData() == (*ni)->recibirData()){
                        cout << i->nodes[1]->recibirData() /*<< ":" << i->recibirData()*/ << "  ";
                    }else{
                        cout << i->nodes[0]->recibirData() /*<< ":" << i->recibirData()*/ << "  ";
                    }
                }
                cout << endl;
            }
        }

        void bfs(N nombre){

        }
        void dfs(N nombre){

        }

        float density(float cota){
            float densidad = (float)aristas/((float)nodos*((float)nodos-1));
            if (isDirected() == 0)
                densidad *= 2;
            if (cota > densidad){
                cout << "Grafo disperso" << endl;
            }else{
                cout << "Grafo denso" << endl;
            }
            return densidad;
        }

        E prim(N nodo){
            node *primerNodo = buscarNodo(nodo);
            multimap<E,edge*> mapaArista;

            if (isDirected() == 1){
                cout << "Grafo dirigido no se puede usar Prim" << endl;
            }
        }

        E kruskal(){

            if (isDirected() == 1){
                cout << "Grafo dirigido no se puede usar Kruskal" << endl;
            }
        }

        void grades(){

        }

        bool isConnect(){

        }

        bool isDirected(){
            return directed;
        }

        bool isStronglyConnected(){

        }

        bool isBipartite(){

        }
        //tipo y gradfio vertices

    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;
};

typedef Graph<Traits> graph;

#endif