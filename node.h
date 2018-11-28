#ifndef NODE_H
#define NODE_H

#include <cmath>

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges;
        Node<G> *padre;

        Node(N nombre,double x,double y){
            data = nombre;
            this->x = x;
            this->y = y;
        }

        N recibirData(){
            return data;
        }

        Node *buscarPadre(){
            if (this != this->padre)
                this->padre = this->padre->buscarPadre();
            return this->padre;
        }

        void asignarPadre(Node<G> *nodo){
            this->padre = nodo;
        }

        double recibirX(){
            return x;
        }

        double recibirY(){
            return y;
        }

        double distanciaEuclideana(Node<G> *goal){
            return (double)sqrt(pow(this->recibirX() - goal->recibirX(),2) + pow(this->recibirY() - goal->recibirY(),2));
        }

    private:
        N data;
        double x;
        double y;
        bool visitado;
};

#endif