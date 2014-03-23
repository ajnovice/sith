#ifndef EDGEMAP_H
#define EDGEMAP_H

#include "node.h"
#include "edge.h"

#include <QPoint>
#include <QList>
#include <QString>

class EdgeMap
{
public:
    EdgeMap(Node nodes, QList <QString> ch, QList <QString> bases, int nn);
    Node n;
    QList <QString> channels;
    QList <QString> bases;
    QMap < QString, int > baseMap;
    QList <Edge> edgeList;
    int nnodes;


    QList <Edge> returnList();

private:
    void CreateEdgeList();

    void CreateBaseMap();

};

#endif // EDGEMAP_H
