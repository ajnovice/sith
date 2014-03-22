#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
main()
{
    vector < vector <int> > judge;
    string sample=". abcdefghijklmnopqrstuvwxyz";
    string teststr="the quick brown fox jumps over the lazy dog.";
    int testlen=teststr.length();
    vector <int> ans;
    //creating our judge
    for (int i=0;i<sample.length();i++)
    {
	ans.clear();
	for (int j=0;j<teststr.length();j++)
	{
	    if (teststr[j]==sample[i])
		ans.push_back(j);
	}
	judge.push_back(ans);
    }
    
    //printing the judge to ensure its correct
    /*
    for(int i=0;i<judge.size();i++)
    {	
	printf("%c ",sample[i]);
	for(int j=0;j<judge[i].size();j++)
	{
	    printf("%d ",judge[i][j]);
	}
	printf("\n");
    }
    */
    
    //a vector of characters which have already been matched.
    vector <char> matchedchars;
    //si is the startindex
    string para="the quick brown fox jumps over the lazy dog.";
    for(int si=0;si<=para.length()-testlen;si++)
    {
	int condition=1;
	//ji is the judge index
	int ji=0;
	matchedchars.clear();
	
	//we run aour entire judge, and stop if any unwanted condition:
	//a character mismatch in position
	//or an unwanted repitition 
	while(condition and ji<judge.size())
	{
	    int match=0;
	    for(int i=0;i<judge[ji].size();i++)
	    {
		//tolower used to eliminate case sensitivity issues.
		printf("%c ",tolower(para[si+judge[ji][i]]));
		if(tolower(para[si+judge[ji][i]])==tolower(para[si+judge[ji][0]]))
		    match++;
	    }
	    printf("\n");
	    if(match!=judge[ji].size() or find(matchedchars.begin(), matchedchars.end(), para[si+judge[ji][0]])!=matchedchars.end())
	    {
		condition=0;
		printf("%d %d",judge[ji].size(),match);
		break;		
	    }
	    //printf("%c=",para[si]);
	    matchedchars.push_back(para[si+judge[ji][0]]);
	    ji++;
	}
	
	if(condition and ji==judge.size())//we have found the key.
	{
	    //construct the qmap and break
	    printf("%d-",si);
	    break;
	}
    }
}