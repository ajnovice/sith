// Graph_coloring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "conio.h"
#include "fstream"
#include "iostream"

using namespace std;
// this program will work with graphs of which number of vertices is smaller or equal to 100
const int MAX = 100;
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
/*=========================================================
===========================================================
					WORKING FUNCTION
===========================================================
=========================================================*/

// function that reads input from file named "input.txt" in the same folder
void GetInput()
{
	ifstream in("input.txt");
	in >> n;
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			in >> a[i][j];
	in.close();
}

// initializing function
void Init()
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
// this function finds the unprocessed vertex of which degree is maximum
int MaxDegreeVertex()
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
// this function is for UpdateNN function
// it reset the value of scanned array
void scannedInit(int scanned[MAX])
{
	for (int i=0; i<n; i++)
		scanned[i] = 0;
}
// this function updates NN array
void UpdateNN(int ColorNumber)
{
	NNCount = 0;
	for (int i=0; i<n; i++)
		if (color[i] == 0)
		{
			NN[NNCount] = i;
			NNCount ++;
		}
	for (int i=0; i<n; i++)
		if (color[i] == ColorNumber)
			for (int j=0; j<NNCount; j++)
				while (a[i][NN[j]] == 1)
				{
					NN[j] = NN[NNCount - 1];
					NNCount --;
				}
}
// this function will find suitable y from NN
int FindSuitableY(int ColorNumber, int& VerticesInCommon)
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
			if (color[x] == ColorNumber)
				for (int k=0; k<n; k++)
					if (color[k] == 0 && scanned[k] == 0)
						if (a[x][k] == 1 && a[tmp_y][k] == 1)
						{
							temp ++;
							scanned[k] = 1;
						}
		if (temp > VerticesInCommon)
		{
			VerticesInCommon = temp;
			y = tmp_y;
		}
	}
	return y;
}
// find the vertex in NN of which degree is maximum
int MaxDegreeInNN()
{
	int tmp_y;
	int temp, max = 0;
	for (int i=0; i<NNCount; i++)
	{
		temp = 0;
		for (int j=0; j<n; j++)
			if (color[NN[j]] == 0 && a[i][NN[j]] == 1)
				temp ++;
		if (temp>max)
		{
			max = temp;
			tmp_y = NN[i];
		}
	}
	return tmp_y;
}
// processing function
void Coloring()
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
// print out the output
void PrintOutput()
{
	for (int i=0; i<n; i++)
		cout << "Vertex " << i+1 << " is colored " << color[i] << endl;
}
// main function
int main()
{
	GetInput();
	Init();
	Coloring();
	PrintOutput();
//	getch();
}
