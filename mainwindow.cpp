//local includes

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creategraphscene.h"
#include "graphcoloring.h"

//Qt Includes
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>

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

void MainWindow::on_pushButton_released()
{

}

void MainWindow::on_pushButton_2_released()
{

}

void MainWindow::on_pushButton_3_released()
{

}

void MainWindow::on_pushButton_4_released()
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

    //display graph
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    ellipse = scene->addEllipse(0,0,100,100,blackPen,redBrush);
    ellipse = scene->addEllipse(100,200,50,50,blackPen,blueBrush);
    ui->graphicsView->show();

}
