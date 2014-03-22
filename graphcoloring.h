#ifndef GRAPHCOLORING_H
#define GRAPHCOLORING_H
#include <QList>
#include <QVector>

class graphColoring
{
public:
    int V;
    QList <int> *adj;
    QVector <int> color;

    graphColoring(int V)
    {
        this->V = V;
        adj = new QList<int>[V];
    }

    ~graphColoring()
    {
        delete []adj;
    }

    void addEdge(int v, int w);

    void greedyColoring(int v, int w);
};

#endif // GRAPHCOLORING_H
