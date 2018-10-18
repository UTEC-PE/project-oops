#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges;

        Node(N nombre,double x,double y){
            data = nombre;
            x = x;
            y = y;
        }

        N recibirData(){
            return data;
        }

    private:
        N data;
        double x;
        double y; 
};

#endif