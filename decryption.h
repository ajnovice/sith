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

    /**
     * @brief getDecrypted
     * get decrypted string of the encrypted string provided as input
     * @return
     * QString of the decrypted string
     */
    QString getDecrypted(QString, QMap <char, char>);



};

#endif // DECRYPTION_H
