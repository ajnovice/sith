#ifndef NODE_H
#define NODE_H

#include <QList>
#include <QPair>
#include <QMap>
#include <QPoint>

class Node
{
    public:
    Node();
    QMap < int, QPoint > nodemap;
    QList <QPoint> nodeList;

    /**
     * @brief setNNodes
     * sets the total number of nodes
     * @param n
     * the number of vertices/nodes
     */
    void setNNodes(int n);

    void setNodes(Node n);

    /**
     * @brief getNode
     * @return
     * Returns the QPoint of that particular Node
     */
    QPoint getNode(int nodeIndex);

  private:
    int nNodes;

    /**
     * @brief assignCoordinates
     * Assigns Locations for each of the nodes
     */
    void assignCoordinates();
};

#endif // NODE_H
