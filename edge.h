#ifndef EDGE_H
#define EDGE_H

#include "node.h"

template <typename G>
class Edge {
    public:
        typedef typename G::E E;
        typedef typename G::node node;

        node* nodes[2];

        Edge(node *nodoInicial,node *nodoFinal,E peso,bool direccion){
        	nodes[0] = nodoInicial;
        	nodes[1] = nodoFinal;
        	data = peso;
        	dir = direccion;
        }

        E recibirData(){
        	return data;
        }

        bool recibirDir(){
            return dir;
        }

    private:
        E data;
        bool dir;
};

#endif