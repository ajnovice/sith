#ifndef FAKEMESSAGES_H
#define FAKEMESSAGES_H

#include <QString>
#include <QList>

class FakeMessages
{
public:
    FakeMessages();
    QList<QString> generate(QString originalMessage, int n);

};

#endif // FAKEMESSAGES_H
