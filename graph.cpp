#include "graph.h"

Graph::Graph(int V, plate plates[ROWS][COLS])
{
    this->V = V + 2;
    adjList = new list<int>[V + 2];
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            switch (plates[i][j].id) {
            case 0:
                plates[i][j].space = 24;
                plates[i][j].R = true;
                plates[i][j].L = true;
                plates[i][j].U = false;
                plates[i][j].D = false;
                break;
            case 1:
                plates[i][j].space = 24;
                plates[i][j].U = true;
                plates[i][j].D = true;
                plates[i][j].R = false;
                plates[i][j].L = false;
                break;
            case 2:
                plates[i][j].space = 20;
                plates[i][j].L = true;
                plates[i][j].D = true;
                plates[i][j].R = false;
                plates[i][j].U = false;
                break;
            case 3:
                plates[i][j].space = 20;
                plates[i][j].L = true;
                plates[i][j].U = true;
                plates[i][j].R = false;
                plates[i][j].D = false;
                break;
            case 4:
                plates[i][j].space = 20;
                plates[i][j].R = true;
                plates[i][j].U = true;
                plates[i][j].L = false;
                plates[i][j].D = false;
                break;
            case 5:
                plates[i][j].space = 20;
                plates[i][j].R = true;
                plates[i][j].D = true;
                plates[i][j].L = false;
                plates[i][j].U = false;
                break;
            case 6:
                plates[i][j].space = 20;
                plates[i][j].L = true;
                plates[i][j].U = true;
                plates[i][j].D = true;
                plates[i][j].R = false;
                break;
            case 7:
                plates[i][j].space = 20;
                plates[i][j].R = true;
                plates[i][j].L = true;
                plates[i][j].U = true;
                plates[i][j].D = false;
                break;
            case 8:
                plates[i][j].space = 20;
                plates[i][j].R = true;
                plates[i][j].U = true;
                plates[i][j].D = true;
                plates[i][j].L = false;
                break;
            case 9:
                plates[i][j].space = 20;
                plates[i][j].R = true;
                plates[i][j].L = true;
                plates[i][j].D = true;
                plates[i][j].U = false;
                break;
            case 10:
                plates[i][j].space = 16;
                plates[i][j].R = true;
                plates[i][j].L = true;
                plates[i][j].U = true;
                plates[i][j].D = true;
                break;
            default:
                break;
            }
        }
    }
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int v = i * COLS + j;
            if (j != COLS - 1 && plates[i][j].R && plates[i][j + 1].L) {
                adjList[v].push_back(v + 1);
            }
            if (j != 0 && plates[i][j].L && plates[i][j - 1].R) {
                adjList[v].push_back(v - 1);
            }
            if (i != ROWS - 1 && plates[i][j].D && plates[i + 1][j].U) {
                adjList[v].push_back(v + COLS);
            }
            if (i != 0 && plates[i][j].U && plates[i - 1][j].D) {
                adjList[v].push_back(v - COLS);
            }
        }
    }
    // entrance
    if (plates[0][0].L) {
        adjList[V].push_back(0);
    }
    // exit
    if (plates[ROWS - 1][COLS - 1].R) {
        adjList[V - 1].push_back(V + 1);
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
