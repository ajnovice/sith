#include "decryption.h"
#include <QVector>
#include <QMap>
#include <QString>

decryption::decryption()
{
}

QMap <char, char> decryption::getMap(QString para)
{
    QMap <char, char> map;
    QVector< QVector <int> > judge;
    QString sample=". abcdefghijklmnopqrstuvwxyz";
    QString teststr="the quick brown fox jumps over the lazy dog.";
    int testlen=teststr.length();
    QVector <int> ans;
    //a vector of characters which have already been matched.
    QVector <char> matchedchars;

    //creating our judge
    for (int i=0; i<sample.length(); i++)
    {
        ans.clear();
        for (int j=0; j<teststr.length(); j++)
        {
            if (teststr[j]==sample[i])
            {
                ans.push_back(j);
            }
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

    //Here para is the string where the paragraph is kept.
    //string para="the quick brown fox jumps over the lazy dog.";

    //si is the startindex of the string variable with the entire paragraph
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
                if (para[si+judge[ji][i]].toLower() == para[si + judge[ji][0]].toLower())
                    match++;
            }
            //controversy here (solved)
            if(match!=judge[ji].size() || matchedchars.contains(para[si+judge[ji][0]].toAscii()))
            {
                condition=0;
                break;
            }
            matchedchars.push_back(para[si+judge[ji][0]].toAscii());
            ji++;
        }

        if(condition and ji==judge.size())//we have found the key.
        {
            //constructing the QMap and break
            for(int i=0;i<teststr.length();i++)
            {
                // character para[si+i] is mapped to character teststr[i]
                map[para[si+i].toAscii()] = teststr[i].toAscii();
            }
            break;
        }
    }
    return map;
}

QString decryption::getDecrypted(QString input, QMap<char, char> decryptionKey)
{
    //does the decryption
    for(int i=0;i<input.length();i++)
    {
	if(input[i].isLetter())
	    input[i]=decryptionKey[input[i]];
    }
    return input;
}
