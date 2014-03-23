/*
 * Code based on Leighton, F. T., A graph coloring algorithm for large
 * scheduling problems, Journal of Research of the National Bureau of
 * Standards 84 (1979).
 */

#include "gcolor.h"
#include <QDebug>

gColor::gColor()
{
}

void gColor::GetInput(QList<QString> vertices, QList<QString> edges)
{
    int nVertices = vertices.length();
    this->n = nVertices;

    //adjacency list to adjacency matrix
    int spacePos;
    int i,j;
    int temp;
    QString base1;
    QString base2;
    int baseIndex1;
    int baseIndex2;
    QMap <QString, int> baseIndex;
    for ( i = 0; i < nVertices; i++)
    {
        baseIndex [vertices[i]] = i;
    }
    qDebug() << baseIndex;

    //initialize adjacency matrix to zeros
    for ( i = 0 ; i < nVertices; i++)
    {
        for (j = 0 ; j < nVertices ; j++)
        {
            a[i][j] = 0;
        }
    }
    int channelCount = edges.length();
    for (i = 0; i < channelCount; i++)
    {
        spacePos   = edges[i].indexOf(' ');
        base1      = edges[i].left(spacePos);
        temp = edges[i].length() - spacePos -1;
        base2      = edges[i].right(temp);
        baseIndex1 = baseIndex[base1];
        baseIndex2 = baseIndex[base2];
        a[baseIndex1][baseIndex2]++;
        a[baseIndex2][baseIndex1]++;
        //Test Printing
        qDebug() << "Test of Base Index:" << baseIndex[base1] << baseIndex[base2] << "Base1:" << base1 << "Base2:" << base2;
    }
    //Test Printing of the graph adjacency matrix
    for (i = 0; i < n; i++)
    {
        for (j = 0 ; j < n ; j ++)
        {
            qDebug() << "a[" << i << "] [" << j << "]: " << a[i][j];
        }
    }
    qDebug() << "Adjacency Matrix over";

}

void gColor::Init()
{
    for (int i=0; i<n; i++)
    {
        color[i] = 0;
        degree[i] = 0;
        for (int j = 0; j<n; j++)
            if (a[i][j] == 1)
                degree[i] ++;
    }
    NNCount = 0;
    unprocessed = n;
}

int gColor::MaxDegreeVertex()
{
    int max = -1;
    int max_i;
    for (int i =0; i<n; i++)
        if (color[i] == 0)
            if (degree[i]>max)
            {
                max = degree[i];
                max_i = i;
            }
    return max_i;
}

void gColor::scannedInit(int scanned[])
{
    for (int i=0; i<n; i++)
    {
        scanned[i] = 0;
    }
}

void gColor::UpdateNN(int ColorNumber)
{
    NNCount = 0;
    for (int i=0; i<n; i++)
    {
        if (color[i] == 0)
        {
            NN[NNCount] = i;
            NNCount ++;
        }
    }
    for (int i=0; i<n; i++)
    {
        if (color[i] == ColorNumber)
        {
            for (int j=0; j<NNCount; j++)
            {
                while (a[i][NN[j]] == 1)
                {
                    NN[j] = NN[NNCount - 1];
                    NNCount --;
                }
            }
        }
    }
}

int gColor::FindSuitableY(int ColorNumber, int &VerticesInCommon)
{
    int temp,tmp_y,y;
    int scanned[MAX];
    VerticesInCommon = 0;
    for (int i=0; i<NNCount; i++)
    {
        tmp_y = NN[i];
        temp = 0;
        scannedInit(scanned);
        for (int x=0; x<n; x++)
        {
            if (color[x] == ColorNumber)
            {
                for (int k=0; k<n; k++)
                {
                    if (color[k] == 0 && scanned[k] == 0)
                    {
                        if (a[x][k] == 1 && a[tmp_y][k] == 1)
                        {
                            temp ++;
                            scanned[k] = 1;
                        }
                    }
                }
            }
        }
        if (temp > VerticesInCommon)
        {
            VerticesInCommon = temp;
            y = tmp_y;
        }
    }
    return y;
}

int gColor::MaxDegreeInNN()
{
    int tmp_y;
    int temp, max = 0;
    for (int i=0; i<NNCount; i++)
    {
        temp = 0;
        for (int j=0; j<n; j++)
        {
            if (color[NN[j]] == 0 && a[i][NN[j]] == 1)
            {
                temp ++;
            }
        }
        if (temp>max)
        {
            max = temp;
            tmp_y = NN[i];
        }
    }
    return tmp_y;
}

void gColor::Coloring()
{
    int x,y;
    int ColorNumber = 0;
    int VerticesInCommon = 0;
    while (unprocessed>0)
    {
        x = MaxDegreeVertex();
        ColorNumber ++;
        color[x] = ColorNumber;
        unprocessed --;
        UpdateNN(ColorNumber);
        while (NNCount>0)
        {
            y = FindSuitableY(ColorNumber, VerticesInCommon);
            if (VerticesInCommon == 0)
                y = MaxDegreeInNN();
            color[y] = ColorNumber;
            unprocessed --;
            UpdateNN(ColorNumber);
        }
    }
}

void gColor::PrintOutput()
{
    for (int i=0; i<n; i++)
        qDebug() << "Vertex " << i+1 << " is colored " << color[i] << endl;
}
