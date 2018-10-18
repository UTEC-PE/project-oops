#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <iostream>

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

        Graph(){
            nodos = 0;
            aristas = 0;
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
            texto.close();
        }

        node *buscarNodo(E nombre){
            node *buscador = NULL;
            for (int i = 0; i < nodes.size(); ++i){
                if (nombre == nodes[i]->recibirData()){
                    buscador = nodes[i];
                    break;
                }
            }
            return buscador;
        }

        void insertarNodo(E nombre,float x, float y){
            node *buscador = buscarNodo(nombre);
            if(!buscador){
                node *nuevoNodo = new node(nombre,x,y); 
                nodes.push_back(nuevoNodo);
                nodos++;
            }else{
                cout << "El nodo ya existe" << endl;
            }
        }

        void removerNodo(E data){//falta
            node *buscador = buscarNodo(data);
            if (buscador){
                for (int i = 0; i < nodes.size(); i++){
                    /* code */
                }
            }
        }

        void insertarArista(E nodoInicial,E nodoFinal,E peso,bool direccion){
            node *buscador1 = buscarNodo(nodoInicial);
            node *buscador2 = buscarNodo(nodoFinal);
            if (buscador1 && buscador2){
                edge *nuevaArista = new edge(nodes[nodoInicial],nodes[nodoFinal],peso,direccion);
                nodes[nodoInicial]->edges.push_back(nuevaArista);
                if (direccion == 0){
                    edge *nuevaArista2 = new edge(nodes[nodoFinal],nodes[nodoInicial],peso,direccion);
                    nodes[nodoFinal]->edges.push_back(nuevaArista);
                }
                aristas++;                
            }else{
                cout << "Uno o más nodos no existentes" << endl;
            }
        }

        void removerArista(E inicio,E fin){
            node *nodo1 = buscarNodo(inicio);
            node *nodo2 = buscarNodo(fin);
            ei=nodo1->edges.begin();
            bool x = 1;
            for (ei;ei!=nodo1->edges.end();++ei){
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
                ei = nodo2->edges.begin();
                for (ei;ei!=nodo2->edges.end();++ei){
                //cout<<(*ei)->nodes[1]->recibirData()<<" "   <<nodo1->recibirData()<<endl;
                if ((*ei)->nodes[0]->recibirData() == nodo1->recibirData()){
                    //cout<<(*ei)->recibirData()<<endl;
                    nodo2->edges.erase(ei);
                    delete *ei;
                    break;
                }
            }    
            }
        }

        void print(){
            for (ni = nodes.begin(); ni != nodes.end(); ni++){
                cout << (*ni)->recibirData() << "-> ";
                for (auto i: (*ni)->edges){
                    if (i->nodes[0]->recibirData() == (*ni)->recibirData()){
                        cout << i->nodes[1]->recibirData() /*<< ":" << i->recibirPeso() */<< "  ";
                    }else{
                        cout << i->nodes[0]->recibirData() /*<< ":" << i->recibirPeso() */<< "  ";
                    }
                }
                cout << endl;
            }
        }

    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;
};

typedef Graph<Traits> graph;

#endif