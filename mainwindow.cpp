//local includes

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creategraphscene.h"
#include "graphcoloring.h"
#include "decryption.h"
#include "gcolor.h"
#include "fakemessages.h"
#include "basicdictionary.h"

//Qt Includes
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTextStream>
#include <QMap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    const QPixmap pix(":/dw_sith.jpg");
//    ui->label->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_released() //display file
{
    inFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&inFile);

    //extracting all text from input file
    QString mText = in.readAll();
    inFile.close();

    //test output of string
    qDebug() << "Test of QString:";
    qDebug() << mText;

    //using decryption class and decrypting the whole text
    decryption Dec;
    mText = Dec.getDecrypted(mText,this->decryptMap);

    //test output of decrypted string
    qDebug() << "Test output of decrypted String";
    qDebug() << mText;

    //adding new scene
    scene = new QGraphicsScene(this);

    //setting graphics view to view scene
    ui->graphicsView->setScene(scene);

    //adding text to scene
    text = scene->addText(mText);

    //showing graphicsView
    ui->graphicsView->show();
}

void MainWindow::on_pushButton_2_released() // show graph
{

//    int no_of_nodes=this->vertices.length();
//    int no_of_chhanel= this->edges.length();
//    for(int i=0;i<no_of_nodes;i++)
//    {
//        pair.append(qMakePair(vertices[i],i+1));
//    }

//    for(int i=0;i<no_of_chhanel;i++)
//    {
//        int index=pair.indexOf(' ');
//        string1=this->edges.left(index);
//        string2=this->edges.right(index+1);
//    }
    QMap<QString,int> map;
    int no_of_nodes=this->vertices.length();
    int no_of_chhanel= this->edges.length();
    for(int i=0;i<no_of_nodes;i++)
    {
        map.insert(vertices[i],i+1);
    }
    QMap<QString,int>::iterator p1,p2;
    for(int i=0;i<no_of_chhanel;i++)
    {
        int index=pair.indexOf(' ');
        string1=this->edges.left(index);
        string2=this->edges.right(index+1);
        p1=map.find(string1);
        p2=map.find(string2);
        graph[p1->second][p2->second]=1;
        graph[p2->second][p1->second]=1;

    }


}

void MainWindow::on_pushButton_3_released() //export file
{

}

void MainWindow::on_pushButton_4_released() //open file
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("*.txt"));

    if (fileName == "")
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open File"));
        return;
    }
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "could not open file for read";
        return;
    }
    qDebug() << "File opened successfully";
    this->inFile.setFileName(fileName);

    //display graph -- Remove
    //scene = new QGraphicsScene(this);
    //ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    //ellipse = scene->addEllipse(0,0,100,100,blackPen,redBrush);
    //ellipse = scene->addEllipse(100,200,50,50,blackPen,blueBrush);
    //ui->graphicsView->show();

    //--Remove till here

    //Divide the whole file into 3 strings
    QString newPara = getNewsParagraph();
    this->paragraph = newPara;

//    text = scene->addText(newPara);
//    scene->clear();
//    ui->graphicsView->show();
    //Get the decrypted file
    decryption Dec;
    QMap <char, char> dMap = Dec.getMap(newPara);
    this->decryptMap = dMap;
    qDebug() << dMap;

    //Work on dividing the file, into lists of vertices(rebel bases)
    QList <QString> vertices = getVerticesList();
    this->vertices = vertices;

    //decrypt Vertices
    for (int i = 0 ; i < this->vertices.length() ; i ++)
    {
        this->vertices[i] = Dec.getDecrypted(this->vertices[i],dMap);
    }

    //Get edges (communication channels)
    QList <QString> edges = getChannels();
    this->edges = edges;

    //decrypt Edges
    for (int i = 0 ; i < this->edges.length() ; i ++)
    {
        this->edges[i] = Dec.getDecrypted(this->edges[i],dMap);
    }

    //Get Messages
    QList <QString> messages = getMessages();
    this->messages = messages;

    //decrypt Messages
    for (int i = 0 ; i < this->messages.length() ; i ++)
    {
        this->messages[i] = Dec.getDecrypted(this->messages[i],dMap);
    }


    //Test Print
    qDebug() << "Vertices (Rebel Bases) : " << this->vertices;
    qDebug() << "Edges (Communication Channels) : " << this->edges;
    qDebug() << "Messages :" << this->messages;


    //Form Graph



}

void MainWindow::on_pushButton_5_released() //Edit Messages
{
    //Make QMap to index each rebel base to a number

    int rebelBaseCount = this->vertices.length();
    int spacePos;
    int i,temp;
    QString base1;
    QString base2;
    QMap <QString, int> baseIndex;
    for ( i = 0; i < rebelBaseCount; i++)
    {
        baseIndex [this->vertices[i]] = i;
    }

    int channelCount = this->edges.length();
    graphColoring g1(rebelBaseCount);
    for (i = 0; i < channelCount; i++)
    {
        spacePos = this->edges[i].indexOf(' ');
        base1=this->edges[i].left(spacePos);
        temp = this->edges[i].length() - spacePos -1;
        base2=this->edges[i].right(temp);
        qDebug() << "Test of Base Index";
        qDebug() << baseIndex[base1];
        qDebug() << baseIndex[base2];
        g1.addEdge(baseIndex[base1], baseIndex[base2]);

        //--- test printing----
        qDebug()<<"Base1:"<<base1<<"Base2:"<<base2;
    }


    qDebug() << "Coloring of graph";
    QVector <int> g1Color = g1.greedyColoring();
    qDebug() << "vector is: " << g1Color;
    //now making initial message the most used message
    g1Color = g1.sortMessages(rebelBaseCount,g1Color);
    qDebug() << "Sorted Vector is : " << g1Color;

    int messageCount = g1.messageCount(rebelBaseCount, g1Color);

    QString messageOutput;
    messageOutput = QString::number(messageCount);
    messageOutput = messageOutput + "\n";

    basicDictionary bd;

    QList <QString> fakeMsgs = bd.getWordList(this->messages[0], messageCount);

    qDebug() << "Fake messages generated: ";

    for ( i = 0 ; i < rebelBaseCount ; i++ )
    {
        messageOutput = messageOutput + this->vertices[i] + ": " + fakeMsgs[g1Color[i]] + "\n";
    }

    /*

    FakeMessages fm;

    QList <QString> fMsgs = fm.generate(this->messages[0],messageCount);

    qDebug() << "Fake messages generated";

    for ( i = 0 ; i < rebelBaseCount ; i++ )
    {
        messageOutput = messageOutput + this->vertices[i] + ": " + fMsgs[g1Color[i]] + "\n";
    }
    */

    //adding new scene
    scene = new QGraphicsScene(this);

    //setting graphics view to view scene
    ui->graphicsView->setScene(scene);

    //adding text to scene
    text = scene->addText(messageOutput);

    //showing graphicsView
    ui->graphicsView->show();

    qDebug() << "Trying out the 2nd program";


    /*
    gColor g;
    g.GetInput(vertices,edges);

    qDebug() << "Inserted Input";
    g.Init();

    qDebug() << "initialization done";
    g.Coloring();

    qDebug() << "coloring done";
    g.PrintOutput();
    */

    //Convert QList <QString> edges into two parts

    //Get colored Graph

    /*
    //test colored graph
    graphColoring g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    qDebug() << "Coloring of Graph 1 \n";
    QVector <int> g1Color = g1.greedyColoring();
    qDebug() << g1Color;

    */


    graphColoring g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 2);
    g2.addEdge(1, 4);
    g2.addEdge(2, 4);
    g2.addEdge(4, 3);
    qDebug() << "\nColoring of Graph 2 \n";
    QVector <int> g2Color = g2.greedyColoring();
    qDebug() << g2Color;


    //Show message count

    //Show messages


}

QString MainWindow::getNewsParagraph()
{
    inFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&inFile);

    QString mText = in.readLine();
    mText=in.readAll();
    qDebug() << mText;
    inFile.close();
    return mText;
}

QList<QString> MainWindow::getVerticesList()
{
    //Task is to traverse till the first blank line
    inFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&inFile);
    QString mText;
    QList <QString> list;

    //traverse till the first blank space
    int count = 0;
    while(true)
    {
        count ++;
        mText = in.readLine();
        if(mText.trimmed().length() == 0)
        {
            break;
        }
    }
    qDebug() << count;
    //reached first blank line
    mText = in.readLine();
    //now the list starts
    count ++;
    while(true)
    {
        count ++;
        mText = in.readLine();
        if (mText.trimmed().length() == 0)
        {
            break;
            //break at next blank line
        }
        list.append(mText);
    }
    inFile.close();
    return list;
}

QList<QString> MainWindow::getChannels()
{
    //Task is to traverse till the second blank line
    inFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&inFile);
    QString mText;
    QList <QString> list;

    //traverse till the second blank line
    int count = 0;
    int flag = 0;
    while(true)
    {
        count ++;
        mText = in.readLine();
        if(mText.trimmed().length() == 0)
        {
            flag++;
            if (flag == 2)
                break;
        }
    }
    qDebug() << count;
    //reached second blank line
    mText = in.readLine();
    //now the list starts
    count ++;
    while(true)
    {
        count ++;
        mText = in.readLine();
        if (mText.trimmed().length() == 0)
        {
            break;
            //break at next blank line
        }
        list.append(mText);
    }
    inFile.close();
    return list;
}

QList<QString> MainWindow::getMessages()
{

    //Task is to traverse till the third blank line
    inFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&inFile);
    QString mText;
    QList <QString> list;

    //traverse till the second blank line
    int count = 0;
    int flag = 0;
    while(true)
    {
        count ++;
        mText = in.readLine();
        if(mText.trimmed().length() == 0)
        {
            flag++;
            if (flag == 3)
                break;
        }
    }

    //reached third blank line
    mText = in.readLine();
    //now the list starts
    count ++;
    while(true)
    {
        count ++;
        mText = in.readLine();
        if (mText.trimmed().length() == 0)
        {
            break;
        }
        list.append(mText);
    }

    inFile.close();
    return list;
}
