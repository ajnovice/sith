#include "creategraphscene.h"
#include <QGraphicsScene>
#include <QDebug>

CreateGraphScene::CreateGraphScene(QList<QString> base, QList<QString> channels)
{
    this->vertex = base;
    this->edge = channels;
    qDebug() << "Succesfully Copied Data";
}

QGraphicsScene *CreateGraphScene::getGraphicsScene()
{
    QList <Edge> edgeList;
    //get the node list
    this->nodes.setNNodes(vertex.length());

    qDebug() << "Node List Received";

    //get the edges
    this->eMap.setBasesString(this->vertex);
    this->eMap.setChannelsString(this->edge);
    this->eMap.setNodes(this->nodes);
    this->eMap.setNumberNodes(this->vertex.length());
    this->eMap.createList();

    //now we have all the QPoints necessary

    scene = new QGraphicsScene();
//    scene = new QGraphicsScene(this);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    int i;
    QLine e;
    for (i = 0 ; i < this->edge.length(); i++)
    {
        e = this->eMap.edgeList[i];
        QLine l(e.p1(), e.p2());
        line = scene->addLine(l,blackPen);
    }
    QPoint v;
    QFont f("Calibri",7,-1,true);

    for ( i = 0; i < this->vertex.length(); i++)
    {
        v = this->eMap.n.getNode(i);
        ellipse = scene->addEllipse(v.x() - 16,v.y() - 16,32,32,blackPen,redBrush);
    }
    return scene;
}

