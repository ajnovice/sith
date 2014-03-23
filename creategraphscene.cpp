#include "creategraphscene.h"
#include <QVector>
#include <QVector2D>

CreateGraphScene::CreateGraphScene()
{
}

void CreateGraphScene::SetGraph(int rows, int columns, QVector<QVector<int> > inputGraph)
{
    graph = inputGraph;
}

void CreateGraphScene::drawGraph()
{


}
