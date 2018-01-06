#include "graph.h"

Graph::Graph(int V, int id[ROWS][COLS])
{
    this->V = V + 2;
    adjList = new list<int>[V + 2];
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            addEdge(i, j, id[i][j]);
        }
    }
    // entrance
    adjList[V].push_back(0);
    // exit
    adjList[V + 1].push_back(V - 1);
}

void Graph::addEdge(int row, int col, int id)
{
    int v = row * COLS + col;
    switch (id) {
    case 0:
        if (col != COLS - 1)
            adjList[v].push_back(v + 1);
        if (col != 0)
            adjList[v].push_back(v - 1);
        break;
    case 1:
        if (row != ROWS - 1)
            adjList[v].push_back(v + ROWS);
        if (row != 0)
            adjList[v].push_back(v - ROWS);
        break;
    case 2:
        if (row != ROWS - 1)
            adjList[v].push_back(v + ROWS);
        if (col != 0)
            adjList[v].push_back(v - 1);
        break;
    case 3:
        if (row != 0)
            adjList[v].push_back(v - ROWS);
        if (col != 0)
            adjList[v].push_back(v - 1);
        break;
    case 4:
        if (row != 0)
            adjList[v].push_back(v - ROWS);
        if (col != COLS - 1)
            adjList[v].push_back(v + 1);
        break;
    case 5:
        if (row != ROWS - 1)
            adjList[v].push_back(v + ROWS);
        if (col != COLS - 1)
            adjList[v].push_back(v + 1);
        break;
    case 6:
        if (row != ROWS - 1)
            adjList[v].push_back(v + ROWS);
        if (row != 0)
            adjList[v].push_back(v - ROWS);
        if (col != 0)
            adjList[v].push_back(v - 1);
        break;
    case 7:
        if (row != 0)
            adjList[v].push_back(v - ROWS);
        if (col != COLS - 1)
            adjList[v].push_back(v + 1);
        if (col != 0)
            adjList[v].push_back(v - 1);
        break;
    case 8:
        if (row != ROWS - 1)
            adjList[v].push_back(v + ROWS);
        if (row != 0)
            adjList[v].push_back(v - ROWS);
        if (col != COLS - 1)
            adjList[v].push_back(v + 1);
        break;
    case 9:
        if (row != ROWS - 1)
            adjList[v].push_back(v + ROWS);
        if (col != COLS - 1)
            adjList[v].push_back(v + 1);
        if (col != 0)
            adjList[v].push_back(v - 1);
        break;
    case 10:
        if (row != ROWS - 1)
            adjList[v].push_back(v + ROWS);
        if (row != 0)
            adjList[v].push_back(v - ROWS);
        if (col != COLS - 1)
            adjList[v].push_back(v + 1);
        if (col != 0)
            adjList[v].push_back(v - 1);
        break;
    default:
        break;
    }
}

void Graph::visit(int v, bool *visited)
{
    visited[v] = true;

    list<int>::iterator i;
    for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
        if (!visited[*i]) {
            visit(*i, visited);
        }
    }
}

bool Graph::DFS(int v)
{
    bool visited[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    visit(v, visited);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

void Graph::print()
{
    for (int v = 0; v < V; ++v) {
        cout << "v" << v << endl;
        list<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            cout << "->" << *i;
        }
        cout << endl;
    }
}
