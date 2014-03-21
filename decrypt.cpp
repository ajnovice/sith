#include <vector>
#include <string>
#include <cstdio>
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
    //si is the startindex
    string para="the quick brown fox jumps over the lazy dog.";
    for(int si=0;si<=para.length()-testlen;si++)
    {
	int condition=1;
	//ji is the judge index
	printf("d\n");
	int ji=0;
	while(condition and ji<judge.size())
	{
	    int match=0;
	    for(int i=0;i<judge[ji].size();i++)
	    {
		if(para[si+judge[ji][i]]==para[si+judge[ji][0]])
		    match++;
	    }
	    if(match!=judge[ji].size())
		condition=0;
	    ji++;
	}
	if(condition and ji==judge.size())//we have found the key.
	{
	    //construct the qmap and break
	    printf("%d",si);
	    break;
	}
    }
}