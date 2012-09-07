#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <QObject>

struct XMLParserData;

class XMLParser : public QObject
{
    Q_OBJECT

public :
    XMLParser(QObject* parent = 0);
    ~XMLParser();

    static XMLParser& instance();

    Q_INVOKABLE void parseTweets(QString twitterID);

private slots:
    void callDone();

private:
    XMLParserData* d;

};

#endif // XMLPARSER_H
