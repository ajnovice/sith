#include "fakemessages.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

FakeMessages::FakeMessages()
{
}

QList<QString> FakeMessages::generate(QString originalMessage, int n)
{
    QList<QString> fakeMsgs;
    int extra=0;
    int wordcount=100;
    int filecount=0;
    QString filename;
    //    QTextStream textStream;
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
                filename = "messages/msgfile" + QString::number(filecount)+ ".txt";
                filecount++;
            }
            qDebug() << "the filename to be opened is: " << filename;
            QFile textFile(filename);
            if(!textFile.open(QFile::ReadOnly | QFile::Text))
            {
                qDebug() << "could not open file for read";
                return fakeMsgs;
            }
            QTextStream textStream(&textFile);


            QString line = textStream.readLine();
            if (line.isNull())
            {
                wordcount=100;
            }
            else
            {
                if (line==originalMessage)
                {
                    extra+=1;
                }
                else
                {
                    fakeMsgs.append(line);
                    wordcount++;
                }
            }

        }
    }
    qDebug() << "FakeMessages: Generated messages, returning";
    return fakeMsgs;
}
