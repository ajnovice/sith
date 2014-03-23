#ifndef BASICDICTIONARY_H
#define BASICDICTIONARY_H

#include <QString>

class basicDictionary
{
public:
    basicDictionary();


    /**
     * @brief getAWord
     * Get a word returned (random)
     * WARNING: Two random words may be the same
     * @param originalText
     * The random word would be checked that it is not in the list of the originalText
     * @return
     * A QString for the random word
     */
    QString getRandomWord(int n, QList <QString> originalText);

    /**
     * @brief getAWord
     * Get the nth word from the dictionary
     * get a word not in the list of originalText
     * @param n
     * The index of the word in the dictionary
     * @return
     * A QString for the word
     */
    QString getAWord(int n);

    /**
     * @brief getWordList
     * @param originalText
     * originalText is originalMessage
     * @param n
     * n is the total number of messages needed, including originalText
     * @return
     */
    QList <QString> getWordList(QString originalText, int n);

private:
    QString dictionary[1000];
};

#endif // BASICDICTIONARY_H
