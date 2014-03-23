//local includes

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creategraphscene.h"
#include "graphcoloring.h"
#include "decryption.h"
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
#include <QPair>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("SITH - Join the Dark Side");
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
    qDebug() << "In pushButton_2_released function";
    CreateGraphScene cgs(this->vertices, this->edges);
    qDebug() << "Object Created";
    scene = cgs.getGraphicsScene();
    qDebug() << "Scene Received";
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::on_pushButton_3_released() //export file
{
    //While exporting the file, the file should be the same as in the initial
    //file till the last paragraph. In the last paragraph, we would have the
    //edited messages instead of the original messages

    //Step 1. Create output file name
    QString outputFileName;
    int index;
    outputFileName = "";
    index = this->inputFileName.lastIndexOf('.');
    outputFileName = inputFileName.left(index);
    outputFileName = outputFileName + "-edited" + ".txt";
    qDebug() << "Output File Name: " << outputFileName;

    //Step 2. Create output file stream
    if (!inFile.open((QFile::ReadOnly | QFile::Text)))
    {
        qDebug() << "Could not read from file";
        return;
    }
    QFile oFile(outputFileName);
    if (!oFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Could not open file to write";
        return;
    }
    qDebug() << "File opened successfully";

    //Step 3. Copy from input file to output file till the 3rd paragraph
    QTextStream in(&inFile);
    QTextStream out(&oFile);
    QString mText;

    //traverse till the third blank line
    int flag = 0;
    int count = 0;
    while(true)
    {
        count ++;
        mText = in.readLine();
        qDebug() << mText;
        out << mText << "\n";
        if(mText.trimmed().length() == 0)
        {
            flag++;
            qDebug() << count;
            if (flag == 3)
                break;
        }
    }
    out << in.readLine();
    out << "\n";
    //Step 5. Encrypt these set of Messages
    //Step 5a. Make reverse Map
    this->encryptMap = reverseMap(this->decryptMap);

    //Step 5b. Pass QStrings through reverseMap, and get corresponding encrypted string
    QString messageOutput;
    int rebelBaseCount = this->vertices.length();
    int i;
    decryption Dec;

    for ( i = 0 ; i < rebelBaseCount ; i++ )
    {
        messageOutput = this->editedMessages[this->graphColor[i]];
        qDebug() << "got messageOutput" << messageOutput;
        messageOutput = Dec.getDecrypted(messageOutput,this->encryptMap);
        qDebug() << "got encrypted Output" << messageOutput;
        out << messageOutput << "\n";

    }

    //Step 7. Save and Exit
    oFile.flush();
    oFile.close();
    inFile.close();

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
    this->inputFileName = fileName;
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

    //Edit Messages
    QList <QString> eMsgs = editMessages();
    this->editedMessages = eMsgs;

    //Test Print
    qDebug() << "Vertices (Rebel Bases) : " << this->vertices;
    qDebug() << "Edges (Communication Channels) : " << this->edges;
    qDebug() << "Messages :" << this->messages;
    qDebug() << "Edited Messages: " << this->editedMessages;


    //Form Graph



}

void MainWindow::on_pushButton_5_released() //Edit Messages
{
    //Make QMap to index each rebel base to a number

    int rebelBaseCount = this->vertices.length();
    int i;

    /*
    int spacePos;
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

    */

    QString messageOutput;
    messageOutput = "Total Messages Used: " + QString::number(messageCount);
    messageOutput = messageOutput + "\n";

    for ( i = 0 ; i < rebelBaseCount ; i++ )
    {
        messageOutput = messageOutput + this->vertices[i] + ": " + this->editedMessages[this->graphColor[i]] + "\n";
    }

    //adding new scene
    scene = new QGraphicsScene(this);

    //setting graphics view to view scene
    ui->graphicsView->setScene(scene);

    //adding text to scene
    text = scene->addText(messageOutput);

    //showing graphicsView
    ui->graphicsView->show();
}

QMap<char, char> MainWindow::reverseMap(QMap<char, char> input)
{
    QMap <char, char> output;
    qDebug() << "in reverse map";
    output.insert('.','.');
    output.insert(' ', ' ');
    char allChar[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',\
                    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',\
                    'y', 'z'};
    int i;
    char temp;
    for  ( i = 0 ; i < 26; i ++ )
    {
        temp = input[allChar[i]];
        output.insert(temp, allChar[i]);
    }
    qDebug() << output;
    qDebug() << "returning from reverse Map";
    return output;
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

QList<QString> MainWindow::editMessages()
{

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

    this->messageCount = g1.messageCount(rebelBaseCount, g1Color);

    basicDictionary bd;

    QList <QString> fakeMsgs = bd.getWordList(this->messages[0], messageCount);

    qDebug() << "Fake messages generated: ";

    this->graphColor = g1Color;

    return fakeMsgs;
}
