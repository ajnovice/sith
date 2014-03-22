#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <QMap>
#include <QString>

class decryption
{
public:
    decryption();

    /**
     * @brief getMap
     * provide encrypted paragraph as QString input
     * @return
     * QMap of the mapping of the character to character
     */
    QMap <char,char> getMap(QString);

    QString getDecrypted(QString, QMap <char, char>);



};

#endif // DECRYPTION_H
