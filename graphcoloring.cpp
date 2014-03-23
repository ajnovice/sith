#include "graphcoloring.h"
#include <QDebug>
#include <QVector>

void graphColoring::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

QVector <int> graphColoring::greedyColoring()
{

    // Assign the first color to first vertex
    color.push_back(0);

    qDebug() << "Reached till here!";
    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        color.push_back(-1);  // no color is assigned to u


    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[V];
    for (int cr = 0; cr < V; cr++)
        available[cr] = false;

    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        QList<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            if (color[*i] != -1)
            {
                available[color[*i]] = true;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++)
        {
            if (available[cr] == false)
            {
                break;
            }
        }

        color[u] = cr; // Assign the found color

        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            if (color[*i] != -1)
            {
                available[color[*i]] = false;
            }
        }
    }

    // print the color
    for (int u = 0; u < V; u++)
    {
        qDebug() << "Vertex " << u << " --->  Color " << color[u] << endl;
    }
    return color;
}

QVector<int> graphColoring::sortMessages(int nVertices, QVector<int> input)
{
    int repitition[nVertices];
    int temp, pos, i;
    //initialize repitition to 0
    for (i = 0 ; i < nVertices ; i++ )
    {
        repitition[i] = 0;
    }

    //filling repitition with data from QVector input
    for (i = 0 ; i < nVertices ; i ++ )
    {
        temp = input[i];
        repitition[temp] = repitition[temp] + 1;
    }

    //finding max in repitition
    temp = repitition[0];
    pos = 0;
    for (i = 0 ; i < nVertices ; i++)
    {
        if (repitition[i] > temp)
        {
            temp = repitition[i];
            pos = i;
        }
    }

    //now swapping 0 with the number having highest value
    //Step 1. Swap "pos" in QVector with "nVertices"
    for (i = 0 ; i < nVertices ; i ++)
    {
        if (input[i] == pos)
        {
            input[i] = nVertices;
        }
    }
    //Step 2. Swap "0" in QVector with pos
    for (i = 0 ; i < nVertices ; i ++ )
    {
        if (input[i] == 0)
        {
            input[i] = pos;
        }
    }
    //Step 3. Swap "nVertices" in QVector with "0"
    for (i = 0 ; i < nVertices ; i ++ )
    {
        if (input[i] == nVertices)
        {
            input[i] = 0;
        }
    }
    return input;

}

int graphColoring::messageCount(int nVertices, QVector<int> input)
{
    int i;
    int max = 0;
    for (i = 0; i < nVertices; i++ )
    {
        if (input[i] > max)
        {
            max = input[i];
        }
    }
    max += 1;
    return max;
}
