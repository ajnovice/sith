#ifndef CREATEGRAPHSCENE_H
#define CREATEGRAPHSCENE_H


#include <QGraphicsScene>
#include <QVector>
#include <QVector2D>
#include <QList>
#include <QPair>

class CreateGraphScene
{
public:
    CreateGraphScene();
    QGraphicsScene* scene;
    QGraphicsEllipseItem* ellipse;
    QGraphicsRectItem* rectangle;

    QList<QPair<QString,int> > pair;
    void SetGraph(int, int, QVector2D);
    void drawGraph();

private:
    QVector2D graph;



};

#endif // CREATEGRAPHSCENE_H
