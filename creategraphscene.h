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





    /**
     * @brief SetGraph
     * sets the basic graph model
     * @param rows
     * @param columns
     * @param inputGraph
     */
    void SetGraph(int rows, int columns, QVector<QVector<int> > inputGraph);

    void drawGraph();
    QVector < QVector < int > > graph;

//private:




};

#endif // CREATEGRAPHSCENE_H
