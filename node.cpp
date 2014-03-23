#include "node.h"

#include <QtCore/qmath.h>
#include <QPoint>
Node::Node()
{
    assignCoordinates();
}

void Node::setNNodes(int n)
{
    this->nNodes = n;
}

void Node::assignCoordinates()
{
    //get radius of bounding circle
    double radius;
    int r;
    radius = (2*32*nNodes)/(2*3.14159);
    if (radius >= 100)
    {
        r = (int)radius;
    }
    else
    {
        r = 100;
    }

    //calculate angle at which the nodes lie
    double angle;
    angle = 360 / nNodes;

    //Center QPoint
    QPoint center(0,0);

    int xCod, yCod;
    double theta;
    for (int i = 0, theta = 0.0; i < nNodes; i++, theta += angle)
    {
        xCod = qSin(0.0174532925 * theta);
        yCod = qCos(0.0174532925 * theta);
        this->nodeList.push_back(QPoint(xCod, yCod));
        this->nodemap.insert(i,QPoint(xCod, yCod));
    }
}

