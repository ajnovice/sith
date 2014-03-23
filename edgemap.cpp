#include "edgemap.h"
#include "node.h"

#include <QDebug>

EdgeMap::EdgeMap(Node nodes, QList<QString> ch, QList<QString> bases, int nn)
{
    this->n = nodes;
    this->nnodes = nn;
    this->channels = ch;
    this->bases = bases;
}

QList<Edge> EdgeMap::returnList()
{
    CreateBaseMap();
    CreateEdgeList();
    return edgeList;
}

void EdgeMap::CreateEdgeList()
{
    QString base1;
    QString base2;
    QPoint pos1;
    QPoint pos2;
    int i, spacePos, temp;

    int channelCount = this->channels.length();
    for (i = 0; i < channelCount; i++)
    {
        spacePos = this->channels[i].indexOf(' ');
        base1=this->channels[i].left(spacePos);
        temp = this->channels[i].length() - spacePos -1;
        base2=this->channels[i].right(temp);
        qDebug() << "Test of Base Index";
        qDebug() << baseMap[base1];
        qDebug() << baseMap[base2];
        pos1 = n.nodemap[baseMap[base1]];
        pos2 = n.nodemap[baseMap[base2]];
        Edge e;
        e.p1 = pos1;
        e.p2 = pos2;
        edgeList.push_back(e);

        //--- test printing----
        qDebug()<<"Base1:"<<base1<<"Base2:"<<base2;
    }
}

void EdgeMap::CreateBaseMap()
{
    int i;
    for (i = 0; i < nnodes; i++ )
    {
        this->baseMap[this->bases[i]] = i;
    }
}
