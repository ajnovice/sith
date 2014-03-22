#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QGraphicsScene>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QFile inFile;

    ~MainWindow();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_5_released();

protected:
    QString paragraph;
    QString string1;
    QString string2;
    QList <QString> vertices;
    QList <QString> edges;
    QList <QString> messages;
    QMap <char, char> decryptMap;

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsEllipseItem* ellipse;
    QGraphicsRectItem* rectangle;
    QGraphicsTextItem* text;



    /**
     * @brief getParagraph
     * Provide with the path of the file which is considered as input
     * @return
     * QString containing the News
     */
    QString getNewsParagraph();

    /**
     * @brief getVerticesList
     * Provide with the path of the file which is considered as input
     * @return
     * QList containing the list of the vertices (Bases)
     */
    QList <QString> getVerticesList();

    /**
     * @brief getChannels
     * Provide with the path of the file which is considered as input
     * @return
     * QList containing the list of edges (Channels)
     */
    QList <QString> getChannels();


    /**
     * @brief getMessages
     * Provide with the path of the file which is considered as input
     * @return
     * QString containing the list of messages(Messages)
     */
    QList <QString> getMessages();
};

#endif // MAINWINDOW_H
