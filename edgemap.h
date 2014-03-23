#ifndef EDGEMAP_H
#define EDGEMAP_H

#include "node.h"
#include "edge.h"

#include <QPoint>
#include <QList>
#include <QString>
#include <QLine>

class EdgeMap
{
public:
    EdgeMap();
    EdgeMap(Node nodes, QList <QString> ch, QList <QString> bases, int nn);
    Node n;
    QList <QString> channels;
    QList <QString> bases;
    QMap < QString, int > baseMap;
    QList <QLine> edgeList;
    int nnodes;

    void setNodes(Node nodes)
    {
        n.setNodes(nodes);
    }

    void setChannelsString(QList <QString> ch)
    {
        this->channels = ch;
    }

    void setBasesString (QList <QString> bases)
    {
        this->bases = bases;
    }

    void setNumberNodes(int nn)
    {
        this->nnodes = nn;
    }

    void createList();

    QList <QLine> returnList();

private:
    void CreateEdgeList();

    void CreateBaseMap();

};

#endif // EDGEMAP_H
