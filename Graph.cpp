#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;


map<string,int> mp;
int graph [1000][1000];

int main()
{   string S1,S2;
    int n,k;
    cin>>n;
    for(int i=0;i<n;i++)
    {   cin>>S1;
        mp.insert(pair<string,int>(S1,i+1));

    }
    map<string,int>:: iterator p1,p2;

    for(int i=0;i<n/2;i++)
    {
        cin>>S1>>S2;
        p1=mp.find(S1);
        p2=mp.find(S2);
        graph[p1->second][p2->second]=i+1;

    }


    return 0;
}
