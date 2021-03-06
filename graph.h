#ifndef GRAPH_H
#define GRAPH_H

#define inf 99999
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <set>
#include <limits>

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
                    if(direccion == 1){
                        directed = 1;
                        //cout << directed << endl;
                    }
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

            if (buscador1 == buscador2){
                cout<<"No se permite loops"<<endl;
                throw "Error";
            }
            if (buscador1 && buscador2){
                if (direccion == 0){
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
                    directed = true;
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
                    cout << i->nodes[1]->recibirData()<<":"<<i->recibirData()<<" ";
                }
                cout << endl;
            }
        }

        void countBFSnodes(N nombre,int* cantNodes){
            map<node*, bool> visited;
            //  Set all nodes to non visited
            for(auto &i:nodes)
                visited[i] = false;

            queue<node*> theQueue;
            visited[buscarNodo(nombre)] = true;
            theQueue.push(buscarNodo(nombre));

            while(!theQueue.empty()){
                node* tmp = theQueue.front();
                theQueue.pop();
                for(auto&i:tmp->edges){
                    if(!visited[i->nodes[1]]){
                        visited[i->nodes[1]] = true;
                        ++(*cantNodes);
                        theQueue.push(i->nodes[1]);
                    }
                }
            }
        }

        void BFS(N nombre){
            cout<<"BFS desde "<<nombre<<":"<<endl;
            map<node*, bool> visited;
            //  Set all nodes to non visited
            for(auto &i:nodes)
                visited[i] = false;

            queue<node*> theQueue;
            visited[buscarNodo(nombre)] = true;
            theQueue.push(buscarNodo(nombre));

            while(!theQueue.empty()){
                node* tmp = theQueue.front();
                theQueue.pop();
                for(auto&i:tmp->edges){
                    if(!visited[i->nodes[1]]){
                        visited[i->nodes[1]] = true;
                        cout<<tmp->recibirData()<<" -> "<<i->nodes[1]->recibirData()<<endl;
                        theQueue.push(i->nodes[1]);
                    }
                }
            }
        }

        void DFS(N nombre){
            cout<<"DFS desde "<<nombre<<":"<<endl;
            map <node*, bool> visited;
            for(auto &i:nodes)
                visited[i] = false;

            node* nm = buscarNodo(nombre);

            realDFS(nm,&visited);
            cout<<endl;
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

        void grados(){
            if(this->isDirected()){
                map<node*,unsigned int> gradoEntrada;
                for(auto&i:nodes)
                    gradoEntrada[i]=0;
                for(auto&i:nodes){
                    for(auto&j:i->edges){
                        gradoEntrada[j->nodes[1]]++;
                        }
                    }
				cout<<"El grafo es dirigido; los grados de entrada son:"<<endl;
                for(auto&k:gradoEntrada){
					cout<<k.first->recibirData()<<" -> "<<k.second<<endl;
				}
                cout<<"Los grados de salida son:"<<endl;
                for(auto&i:nodes){
                    cout<<i->recibirData()<<" -> "<<i->edges.size()<<endl;
                }
			}
			else{
				cout<<"El grafo no es dirigido; los grados son:"<<endl;
				for(auto &i:nodes){
					cout<<i->recibirData()<<" -> "<<i->edges.size()<<endl;
				}
			}
        }

        bool isConnected(){
            for(auto&i:nodes){
                int count=1;
                countBFSnodes(i->recibirData(),&count);
                if(count!=nodes.size()){
                    //cout<<count<<endl;
                    return false;
                }
            }
            return true;
        }

        bool isStronglyConnected(){

        }

        bool isBipartite(){
            map<node*, int> colorMap;

            for(auto &i: nodes)
                colorMap[i] = 0;

            colorMap[nodes[0]] = 1;

            for(auto &i:nodes)
                if(!colorNeighbors(i,&colorMap)){
                    cout<<"El grafo no es bipartito. El nodo "<<i->recibirData()<<" da error"<<endl;
                    return false;
            }

//            for(auto &i: colorMap)
//                cout<<i.first->recibirData()<<" "<<i.second<<endl;
            cout<<"El grafo es bipartito :)"<<endl;
            return true;
        }

    	bool colorNeighbors(node* clrNode,map<node*, int>* clrMap){
                if((*clrMap)[clrNode]==1){
                    for(auto i: clrNode->edges){
                        if((*clrMap)[i->nodes[1]]!=1)
                            (*clrMap)[i->nodes[1]]=-1;
                        else
                            return false;
                    }
                }
                if((*clrMap)[clrNode]==-1){
                    for(auto i: clrNode->edges){
                        if((*clrMap)[i->nodes[1]]!=-1)
                            (*clrMap)[i->nodes[1]]=1;
                        else
                            return false;
                    }
                }
                return true;
        }

        self GreedyBFS(N inicio, N fin){
            node *nodoinicio = buscarNodo(inicio);
            node *nodofin = buscarNodo(fin);
            multimap<E,edge*> aristas;
            map<node*,bool> pintados;
            self nuevo_grafo;

            for (int i = 0; i < nodes.size(); ++i){
                pintados.insert(pair<node*,bool> (nodes[i],false));
            }

            for (auto i: nodoinicio->edges){
                aristas.insert(pair<E,edge*> (i->recibirData(),i));
            }

            cout<<"GreedyBFS:"<<endl;
            pintados[nodoinicio] = true;

            auto it = aristas.begin();
            while (it != aristas.end()){
                if (/*it->second->nodes[1] != nodoinicio &&*/ pintados[it->second->nodes[1]] == false){
                    nuevo_grafo.insertarNodo(it->second->nodes[0]->recibirData(),it->second->nodes[0]->recibirX(),it->second->nodes[0]->recibirY());
                    nuevo_grafo.insertarNodo(it->second->nodes[1]->recibirData(),it->second->nodes[1]->recibirX(),it->second->nodes[1]->recibirY());
                    nuevo_grafo.insertarArista(it->second->nodes[0]->recibirData(),it->second->nodes[1]->recibirData(),it->first,0);
                    cout<<"{"<<it->second->nodes[0]->recibirData()<<","<<it->second->nodes[1]->recibirData()<<" :"<<it->first<<"}"<<" ";
                    nodoinicio = it->second->nodes[1];
                    pintados[nodoinicio] = true;
                    aristas.erase(it);
                    if (it->second->nodes[1] == nodofin){
                        break;
                    }
                    for (auto i: nodoinicio->edges){
                        aristas.insert(pair<E,edge*> (i->recibirData(),i));
                    }
                    it = aristas.begin();
                }else{
                    aristas.erase(it);
                    it = aristas.begin();
                }
            }
            cout<<endl;

            return nuevo_grafo;
        }

        E recibirPeso(N nodo1,N nodo2){
            for (ni = nodes.begin(); ni != nodes.end(); ++ni){
                if ((*ni)->recibirData() == nodo1){
                    for (ei = (*ni)->edges.begin(); ei != (*ni)->edges.end(); ++ei){
                        if ((*ei)->nodes[1]->recibirData() == nodo2){
                            return (*ei)->recibirData();
                        }
                    }
                }
            }
        }
        
        node *encontrarMenor(map<node*,double> m, set<node*> s){
            auto it = m.begin();
            double menor = numeric_limits<double>::max();
            node *nodo;
            for (; it != m.end(); ++it){
                if (it->second < menor && s.count(it->first)){
                    menor = it->second;
                    nodo = it->first;
                }
            }
            return nodo;
        }

        self path(map<node*,node*> vinoDe,node* current){
            self nuevo_grafo;
            while(vinoDe.count(current)){
                nuevo_grafo.insertarNodo(current->recibirData(),current->recibirX(),current->recibirY());
                nuevo_grafo.insertarNodo(vinoDe[current]->recibirData(),vinoDe[current]->recibirX(),vinoDe[current]->recibirY());
                nuevo_grafo.insertarArista(vinoDe[current]->recibirData(),current->recibirData(),recibirPeso(vinoDe[current]->recibirData(),current->recibirData()),directed);
                current = vinoDe[current];
            }
            return nuevo_grafo;
        }
    
        self A_Star(N partida, N destino){//paralelo multiples busquedas
            node *start = buscarNodo(partida);
            node *goal = buscarNodo(destino);
            double infinity = numeric_limits<double>::max();
            
            set<node*> openSet;
            set<node*> closedSet;
            map<node*,node*> vinoDe;
            map<node*,double> gValor;
            map<node*,double> costo;

            openSet.insert(start);

            for (int i = 0; i < nodes.size(); ++i){
                gValor.insert(pair<node*,double> (nodes[i],infinity));
            }
            gValor[start] = 0;

            for (int i = 0; i < nodes.size(); ++i){
                costo.insert(pair<node*,double> (nodes[i],infinity));
            }
            costo[start] = start->distanciaEuclideana(goal);

            while (!openSet.empty()){
                node *current = encontrarMenor(costo,openSet);
                if (current == goal){
                    return path(vinoDe,current);
                }

                openSet.erase(current);
                closedSet.insert(current);
                
                for (auto it: current->edges){
                    if (closedSet.count(it->nodes[1]))
                        continue;

                    double tentative_gValor = gValor[current] + it->recibirData();
                    
                    if (!closedSet.count(it->nodes[1]))
                        openSet.insert(it->nodes[1]);
                    else if(tentative_gValor >= gValor[it->nodes[1]])
                        continue;

                    vinoDe[it->nodes[1]] = current;
                    gValor[it->nodes[1]] = tentative_gValor;
                    costo[it->nodes[1]] = gValor[it->nodes[1]] + it->nodes[1]->distanciaEuclideana(goal);
                }
            }
        }

        map<node*,N> BellmanFord(N nodo){
            node* inicio = buscarNodo(nodo);
            map<node*,int> distancia;
            map<node*,N> predecesor;
            cout<<"BellmanFord "<<endl;

            int infinito = numeric_limits<int>::max();

            for (int i = 0; i < nodes.size(); ++i){
                distancia[nodes[i]] = infinito;
                predecesor[nodes[i]] = -1;
            }
            distancia[inicio] = 0;
            predecesor[inicio] = inicio->recibirData();

            for (int it = 0; it < nodes.size()-1; ++it){
                for (ni = nodes.begin(); ni != nodes.end(); ni++){
                    for (auto i: (*ni)->edges){
                        if (distancia[i->nodes[0]] + i->recibirData() < distancia[i->nodes[1]]){
                            distancia[i->nodes[1]] = distancia[i->nodes[0]] + i->recibirData();
                            predecesor[i->nodes[1]] = i->nodes[0]->recibirData();
                        }
                    }
                }
            }
            

            for (int i = 0; i < nodes.size(); ++i){
                for (auto j: nodes[i]->edges){
                    if (distancia[j->nodes[0]] + j->recibirData() < distancia[j->nodes[1]]){
                        cout<<"Error, ciclos negativos"<<endl;
                    }
                }
            }
            
            cout<<"Matriz pesos:"<<endl;
            for (int i = 0; i < distancia.size(); ++i){
                cout<<distancia[nodes[i]]<<" ";
            }cout<<endl;

            cout<<endl<<"Matriz caminos:"<<endl;
            for (int i = 0; i < nodes.size(); ++i){
                cout<<predecesor[nodes[i]]<<" ";
            }cout<<endl;

            return distancia,predecesor;
        }
        ~Graph(){
            for (ni = nodes.begin(); ni != nodes.end(); ++ni){
                for (auto i: (*ni)->edges){
                    delete i;
                    }
                delete *ni;
                }
        }

        vector<vector<int>> FloydWarshall(){
            vector<vector<int>> shortDistances(nodos, vector<int> (nodos, 0));

            for(int i=0;i<nodos;i++){
                for(int j=0;j<nodos;j++){
                    if(i!=j)
                    shortDistances[i][j] = inf;
                }
            }

            for(auto i: nodes){
                for(auto j:i->edges){
                    shortDistances[i->recibirData()][j->nodes[1]->recibirData()] = j->recibirData();
                }
            }


            for(int k=0;k<nodos;k++){
                for(int i=0;i<nodos;i++){
                    for(int j=0;j<nodos;j++){
                        int ds= shortDistances[i][k] + shortDistances[k][j];
                        if(shortDistances[i][j]>ds and ds != 0)
                            shortDistances[i][j] = ds;
                    }
                }
            }

            return shortDistances;
        }

        vector<int> Dijkstra(N nombre){
            node* source = buscarNodo(nombre);
            vector<int> djkstr;
            vector<bool> aux(nodos);
            
            for(int i=0;i<nodos;i++)
                djkstr.push_back(inf);   

            djkstr[nombre] = 0;

            for(int i=0;i<nodos-1;i++){
                int u = minDst(djkstr,aux);
                aux[u] = true;


                for(auto nds:nodes){
                    if(!aux[nds->recibirData()] and hasPath(u,nds->recibirData()) and 
                        djkstr[u]!=inf and djkstr[u] + buscarArista(u,nds->recibirData())->recibirData() <djkstr[nds->recibirData()])
                        
                        djkstr[nds->recibirData()] = djkstr[u] + buscarArista(u,nds->recibirData())->recibirData();

                }
            }

            return djkstr;
        }

        bool hasPath(N n1, N n2){
            node* u=buscarNodo(n1);
            node* v=buscarNodo(n2);
            for(auto i:u->edges){
                if(i->nodes[1]->recibirData()==n2)
                    return true;
            }
        }

        N minDst(vector<N> dj, vector<bool> aux){
            int min = inf, min_index; 
           
            for (int i = 0; i < nodos; i++) 
                if (aux[i] == false && dj[i] <= min) 
                    min = dj[i], min_index = i; 
           
            return min_index; 
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

        void realDFS(node* nombre, map<node*,bool>* visited){
            (*visited)[nombre]= true;
            for(auto& i:nombre->edges) {
                if(!((*visited)[i->nodes[1]])) {
                    cout<<nombre->recibirData()<<" -> "<<i->nodes[1]->recibirData()<<endl;
                    realDFS(i->nodes[1],visited);
                }
            }
        }
};

typedef Graph<Traits> graph;

#endif
