#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsView>
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
    /**
     * @brief on_pushButton_released
     * function which determines action when "Display File" button is pressed
     * the function displays the decrypted value of the file in the GraphicsView
     */
    void on_pushButton_released();

    /**
     * @brief on_pushButton_2_released
     * function which determines action when "Show Graph" button is pressed
     * the function displays the graph of the Bases and communication Channels
     */
    void on_pushButton_2_released();

    /**
     * @brief on_pushButton_3_released
     * function which determines action when "Export File" button is pressed
     * the function exports the file to output
     */
    void on_pushButton_3_released();

    /**
     * @brief on_pushButton_4_released
     * function which determines action when "Open File" button is pressed
     * the function displays file dialog to open the input file
     */
    void on_pushButton_4_released();

    /**
     * @brief on_pushButton_5_released
     * function which determines action when "Edit Messages" button is pressed
     * the function displays the changes messages and respective bases along with it
     */
    void on_pushButton_5_released();

protected:
    QString paragraph;
    QString string1;
    QString string2;
    QList <QString> vertices;
    QList <QString> edges;
    QList <QString> messages;
    QList <QString> editedMessages;
    QVector <int> graphColor;
    QMap <char, char> decryptMap;
    QMap <char, char> encryptMap;

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* graphView;
    QGraphicsEllipseItem* ellipse;
    QGraphicsRectItem* rectangle;
    QGraphicsTextItem* text;
    int messageCount;
    QString inputFileName;
    QMap <char, char> reverseMap(QMap <char, char>);



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

    QList <QString> editMessages();
};

#endif // MAINWINDOW_H
