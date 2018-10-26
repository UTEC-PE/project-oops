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
        
        N nodos;
        E aristas;
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
            if(texto.is_open()){
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
            else{
                cout<<"Error opening file";
                return;
            }
        }
        
        bool isDirected(){
            return directed;
        }


        void insertarNodo(N nombre,float x, float y){
            node *buscador = buscarNodo(nombre);
            if(!buscador){
                node *nuevoNodo = new node(nombre,x,y); 
                nodes.push_back(nuevoNodo);
                nodos++;
            }else{
                return;
            }
        }

        void removerNodo(N data){
            node *nodo = buscarNodo(data);
            if (nodo){
                ei = nodo->edges.begin();
                while (ei != nodo->edges.end()){
                    removerArista(nodo->recibirData(),(*ei)->nodes[1]->recibirData());
                    ei = nodo->edges.begin();    
                }
                if (isDirected() == 1){
                    for (ni = nodes.begin(); ni != nodes.end(); ni++){
                        for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ei++){
                            if ((*ei)->nodes[1]->recibirData() == data){
                                (*ni)->edges.remove(*ei);
                                break;
                            }
                        }
                    }
                }

                for (int i = 0; i < nodes.size(); ++i){
                    if (nodes[i]->recibirData() == data){
                        nodes.erase(nodes.begin()+data);
                    }
                }
                nodos--;
            }else{
                cout << "No existe el nodo" << endl;
            }
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
                        // cout<<(*ei)->nodes[0]->recibirData()<<"->"<<nodo1->recibirData()<<endl;
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
                    cout << i->nodes[1]->recibirData()<</*":"<<i->recibirData()<<*/" ";
                }
                cout << endl;
            }
        }

        void bfs(N nombre){

        }
        
        void dfsSupp(E nombre, map<node*,bool> visited){
            node* tmp = buscarNodo(nombre);
            visited[tmp] = true;
            cout<<tmp->recibirData()<<" - ";

           for(auto &i:tmp->edges) {
               if(!visited[i->nodes[1]])
                   dfsSupp(i->nodes[1]->recibirData(), visited);
           }
        }


        void dfs(E nombre){
            map <node*, bool> visited;
            for(auto &i:nodes)
                visited[i] = false;

            for(auto &i:visited)
                cout<<i.first<<" "<<i.second<<endl;

            dfsSupp(nombre, visited);
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

        self prim(N dato){
            if (isDirected() == 1){
                cout << "Grafo dirigido no se puede usar Prim" << endl;
                throw "Error";
            }
            node *nodo = buscarNodo(dato);
            multimap<E,edge*> mapaAristas;
            map<node*,bool> nodosVisitados;
            self nuevo_grafo;
            cout<<"Prim: ";
            for (int i = 0; i < nodes.size(); i++){
                nodosVisitados.insert(pair<node*,bool> (nodes[i],false));
            }
            for (auto i: nodo->edges){
                mapaAristas.insert(pair<E,edge*> (i->recibirData(),i));
            }
            nodosVisitados[nodo] = true;
            auto it = mapaAristas.begin();
            while (it != mapaAristas.end()){
                if (it->second->nodes[1] != nodo && nodosVisitados[it->second->nodes[1]] == false){
                    nuevo_grafo.insertarNodo(it->second->nodes[0]->recibirData(),it->second->nodes[0]->recibirX(),it->second->nodes[0]->recibirY());
                    nuevo_grafo.insertarNodo(it->second->nodes[1]->recibirData(),it->second->nodes[1]->recibirX(),it->second->nodes[1]->recibirY());
                    nuevo_grafo.insertarArista(it->second->nodes[0]->recibirData(),it->second->nodes[1]->recibirData(),it->first,0);
                    cout<<"{"<<it->second->nodes[0]->recibirData()<<","<<it->second->nodes[1]->recibirData()<<" :"<<it->first<<"}"<<" ";
                    nodo = it->second->nodes[1];
                    nodosVisitados[nodo] = true;
                    mapaAristas.erase(it);
                    for (auto i: nodo->edges){
                        mapaAristas.insert(pair<E,edge*> (i->recibirData(),i));
                    }
                    it = mapaAristas.begin();
                }else{
                    mapaAristas.erase(it);
                    it = mapaAristas.begin();
                }                
            }
            cout<<endl;
            return nuevo_grafo;          
        }

        bool Union(node *nodo1,node *nodo2){       
            nodo1->asignarPadre(nodo1);
            nodo2->asignarPadre(nodo2);
            if (nodo1->padre != nodo2->padre){
                nodo1->padre->asignarPadre(nodo2);
                return true;
            }else{
                return false;
            }                
        }

        self kruskal(){
            if (isDirected() == 1){
                cout << "Grafo dirigido no se puede usar Kruskal" << endl;
                throw "Error";
            }
            multimap<E,edge*> mapaAristas;
            self nuevo_grafo;
            for (int i = 0; i < nodes.size(); i++){
                for (auto it: nodes[i]->edges){
                    mapaAristas.insert(pair<E,edge*> (it->recibirData(),it));
                }
            }
            for (int i = 0; i < nodes.size(); i++){
                nodes[i]->asignarPadre(nodes[i]);
            }
            cout<<"Kruskal: ";
            while (mapaAristas.size()>0){
                auto it = mapaAristas.begin();
                auto u = it->second->nodes[0];
                auto v = it->second->nodes[1];
                auto set_u = u->buscarPadre();
                auto set_v = v->buscarPadre();

                if (set_u != set_v){
                    nuevo_grafo.insertarNodo(u->recibirData(),u->recibirX(),u->recibirY());
                    nuevo_grafo.insertarNodo(v->recibirData(),v->recibirX(),v->recibirY());
                    nuevo_grafo.insertarArista(u->recibirData(),v->recibirData(),it->first,0);
                    cout<<"{"<<u->recibirData()<<","<<v->recibirData()<<" :"<<it->first<<"}"<<" ";
                    Union(set_u,set_v);
                    mapaAristas.erase(mapaAristas.begin());
                }
                else{
                    mapaAristas.erase(mapaAristas.begin());
                }
            }
            cout<<endl;
            return nuevo_grafo;
        }

        void grado(N nodo){
            node *bNodo = buscarNodo(nodo);
            int grado = 0;
            for (auto i: bNodo->edges){
                grado++;
            }
            cout<<grado<<endl;
        }

        bool isConnect(){

        }

        bool isStronglyConnected(){

        }

        bool isBipartite(){

        }

    private:
        NodeSeq nodes;
        NodeIte ni;
        EdgeIte ei;

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
};

typedef Graph<Traits> graph;

#endif
