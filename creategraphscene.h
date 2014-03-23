#ifndef CREATEGRAPHSCENE_H
#define CREATEGRAPHSCENE_H

//Local Includes

#include "node.h"
#include "edgemap.h"
#include "edge.h"

//Qt Includes

#include <QGraphicsScene>
#include <QList>
#include <QString>

class CreateGraphScene
{
public:
//    CreateGraphScene();
    CreateGraphScene(QList <QString> base, QList <QString> channels);


    /**
     * @brief getGraphicsScene
     * Gives back a GraphicsScene with the edges and nodes in it.
     * @return
     */
    QGraphicsScene *getGraphicsScene();

private:
    EdgeMap eMap;
    Node nodes;
    QList <QString> vertex;
    QList <QString> edge;

    QGraphicsScene* scene;
    QGraphicsEllipseItem* ellipse;
    QGraphicsTextItem* text;
    QGraphicsRectItem* rectangle;
    QGraphicsLineItem* line;

};

#endif // CREATEGRAPHSCENE_H
