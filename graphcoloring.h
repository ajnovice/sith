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

    QVector<int> greedyColoring();

    /**
     * @brief sortMessages
     * To make sure that the initial message is used the most
     * @param Output of greedyColoring
     * @return
     */
    QVector<int> sortMessages(int nVertices, QVector<int> input);

    int messageCount (int nVertices, QVector <int> input);
};

#endif // GRAPHCOLORING_H
