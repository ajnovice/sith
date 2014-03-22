#include "fakemessages.h"

#include <QFile>
#include <QTextStream>
FakeMessages::FakeMessages()
{
}

QList<QString> FakeMessages::generate(QString originalMessage, int n)
{
    QList<QString> fakeMsgs;
    int extra=0;
    int wordcount=100;
    int filecount=0;
    QTextStream textStream;
    if(n>12000)
    {
        //error and kill cannot handle more than 12000 bases.
    }
    else
    {
        for(int i=0;i<n+extra;i++)
        {
            if(wordcount==100)
            {
                QFile textFile("messages/msgfile"+QString::number(filecount)+".txt");
                textStream.setDevice(&textFile);
                filecount++;
            }
            QString line = textStream.readLine();
            if (line.isNull())
                wordcount=100;
            else
            {
                if (line==originalMessage)
                        extra+=1;
                else
                {
                    fakeMsgs.append(line);
                    wordcount++;
                }
            }

        }
    }
    return fakeMsgs;
}
