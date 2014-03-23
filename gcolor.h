#ifndef GCOLOR_H
#define GCOLOR_H

//Qt dependencies
#include <QList>
#include <QString>


//Local Constants
const int MAX=100;

class gColor
{
public:
    gColor();

    // this program will work with graphs of which number of vertices is
    //smaller or equal to 100

    // necessary variables
    // n is the number of vertices of the graph
    int n;
    // a[n][n] is the adjacency matrix of the graph
    // a[i][j] = 1 if i-th and j-th vertices are adjacent
    int a[MAX][MAX];
    // array color[n] stores the colors of the vertices
    // color[i] = 0 if we 've not colored it yet
    int color[MAX];
    // array degree[n] stores the degrees of the vertices
    int degree[MAX];
    // array NN[] stores all the vertices that is not adjacent to current vertex
    int NN[MAX];
    // NNCount is the number of that set
    int NNCount;
    // unprocessed is the number of vertices with which we 've not worked
    int unprocessed;

    /**
     * @brief GetInput
     * function that reads input from file named "input.txt" in the same folder
     */
    void GetInput(QList <QString> vertices, QList <QString> edges);

    /**
     * @brief Init
     * initializing function
     */
    void Init();

    /**
     * @brief MaxDegreeVertex
     * this function finds the unprocessed vertex of which degree is maximum
     * @return
     * returns integer of max degree
     */
    int MaxDegreeVertex();

    /**
     * @brief scannedInit
     * this function is for UpdateNN function
     * it reset the value of scanned array
     * @param scanned
     */
    void scannedInit(int scanned[MAX]);

    /**
     * @brief UpdateNN
     * this function updates NN array
     * @param ColorNumber
     */
    void UpdateNN(int ColorNumber);

    /**
     * @brief FindSuitableY
     * this function will find suitable y from NN
     * @param ColorNumber
     * @param VerticesInCommon
     * @return
     */
    int FindSuitableY(int ColorNumber, int& VerticesInCommon);

    /**
     * @brief MaxDegreeInNN
     * find the vertex in NN of which degree is maximum
     * @return
     */
    int MaxDegreeInNN();

    /**
     * @brief Coloring
     * Processing Function
     */
    void Coloring();

    /**
     * @brief PrintOutput
     * print out the output
     */
    void PrintOutput();

private:

};

#endif // GCOLOR_H
