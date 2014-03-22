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
