#ifndef CREATEGRAPHSCENE_H
#define CREATEGRAPHSCENE_H


#include <QGraphicsScene>
#include <QVector>
#include <QVector2D>

class CreateGraphScene
{
public:
    CreateGraphScene();
    QGraphicsScene* scene;
    QGraphicsEllipseItem* ellipse;
    QGraphicsRectItem* rectangle;

    void SetGraph(int, int, QVector2D);
    void drawGraph();

private:
    QVector2D graph;


};

#endif // CREATEGRAPHSCENE_H
