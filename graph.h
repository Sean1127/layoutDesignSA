#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <QDebug>

#define ROWS 2
#define COLS 3

using namespace std;

typedef struct _plate {
    bool L = false;
    bool R = false;
    bool U = false;
    bool D = false;
    int space = 16;
    int id = 10;
} plate;

class Graph
{
public:
    Graph(int V, plate plates[ROWS][COLS]);
    bool DFS(int v);
    void print();

private:
    int V;
    list<int> *adjList;
    void visit(int v, bool *visited);
};

#endif // GRAPH_H
