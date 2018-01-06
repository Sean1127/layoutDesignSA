#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <QDebug>

#define ROWS 2
#define COLS 3

using namespace std;

class Graph
{
public:
    Graph(int V, int id[ROWS][COLS]);
    void addEdge(int row, int col, int id);
    void visit(int v, bool *visited);
    bool DFS(int v);
    void print();

private:
    int V;
    list<int> *adjList;
    void DFSUtil(int v, bool visited[]);
};

#endif // GRAPH_H
